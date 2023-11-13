/*
 * This file is part of RAMPi.
 * Copyright (C) 2023 Varvara Petrova
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "TriangleR.h"
#include "constants.h"

#include <cmath>
#include <QDebug>
#include <QMessageBox>


TriangleRectangle::TriangleRectangle(double angle, double opposite, double adjacent, double hypotenuse, int angleUnit):
    m_A(angle), m_H(opposite), m_L(adjacent), m_R(hypotenuse), m_aunit(angleUnit),
    m_exists(true), m_msg(QString()), m_msgTitle(QString()), m_msgStatus(QMessageBox::Warning)
{
    /*        |   input   | output
     * -------+----------+--------
     * % ou ° |   angle  | m_A
     * -------+----------+--------
     *  Rad  | angleRAD | m_ARad  */

    double angleRAD = convertAngle(angle, angleUnit, AUnit::Rad);
    m_ARad = angleRAD;

    double input [4] = {angle, opposite, adjacent, hypotenuse};

    int inputCount = 0;
    for (int i=0; i<4; ++i)
        if (input[i]) ++inputCount;    

    switch (inputCount)
    {
    case 0:
        m_exists = false;
        m_msg = QString();
    break;

    case 1:
        m_exists = false;
        m_msg = QString("Données incomplètes.");
        m_msgTitle = "Erreur";
    break;    

    default:
        if (!angle)      calculateA(opposite, adjacent, hypotenuse);
        if (!opposite)   calculateH(angleRAD, adjacent, hypotenuse);
        if (!adjacent)   calculateL(angleRAD, opposite, hypotenuse);
        if (!hypotenuse) calculateR(angleRAD, opposite, adjacent);
        // cas inputCount=4 n'est pas concerné par les calculs plus haut

        if (difference(m_L, m_R*cos(m_ARad)) or difference(m_H, m_R*sin(m_ARad)))
        {
            m_exists = false;
            m_msg = "Données incompatibles.";
            m_msgTitle = "Erreur";
            qDebug() << " m_L - m_R*cos(m_ARad) : " << abs(m_L - m_R*cos(m_ARad));
            qDebug() <<" m_H - m_R*sin(m_ARad) : " << abs(m_H - m_R*sin(m_ARad));
        }
        else // i.e. m_exists = true
            if (inputCount == 4)
            {
                m_msg = "Rien à calculer : tout est correct.";
                m_msgTitle = "Vérification";
                m_msgStatus = QMessageBox::NoIcon;
            }

        break;
    }

    if (!m_exists)
        m_A = m_ARad = m_H = m_L = m_R = 0.;


}

bool TriangleRectangle::exists()
{

    return m_exists;
}

QString TriangleRectangle::msg()
{
    return m_msg;
}

QString TriangleRectangle::msgTitle()
{
    return m_msgTitle;
}

QMessageBox::Icon TriangleRectangle::msgIcon()
{
    return m_msgStatus;
}

void TriangleRectangle::calculateA(double h, double l, double r)
{
    if (h and l) // sélection faite si h, l et r non nuls
        m_A = atan(h/l);
    else if (h and r and h<r)
        m_A = asin(h/r);
    else if (l and r and l<r)
        m_A = acos(l/r);
    else
        m_A = 0;

    if (m_A)
    {
        m_ARad = m_A;
        m_A = convertAngle(m_A, AUnit::Rad, m_aunit);
    }
}

void TriangleRectangle::calculateH(double aRad, double l, double r)
{
    if (aRad and l)
        m_H = l*tan(aRad);
    else if (aRad and r)
        m_H = r*sin(aRad);
    else if (l and r and l<r)
        m_H = sqrt(r*r - l*l);
    else
        m_H = 0;
}

void TriangleRectangle::calculateL(double aRad, double h, double r)
{
    if (aRad and h)
        m_L = h/tan(aRad);
    else if (aRad and r)
        m_L = r*cos(aRad);
    else if (h and r and h<r)
        m_L = sqrt(r*r - h*h);
    else
        m_L = 0;
}


void TriangleRectangle::calculateR(double aRad, double h, double l)
{
    if (aRad and h)
        m_R = h/sin(aRad);
    else if (aRad and l)
        m_R = l/cos(aRad);
    else if (h and l)
        m_R = sqrt(h*h + l*l);
    else
        m_R = 0;    
}


double TriangleRectangle::getAngle()
{
    return m_A;
}

double TriangleRectangle::getH()
{
    return m_H;
}

double TriangleRectangle::getL()
{
    return m_L;
}

double TriangleRectangle::getR()
{
    return m_R;
}

double TriangleRectangle::getOutput(int i)
{
    switch (i) {
    case 0:
        return m_A;
        break;
    case 1:
        return m_H;
        break;
    case 2:
        return m_L;
        break;
    case 3:
        return m_R;
        break;
    default:
        return 0;
        break;
    }
}
