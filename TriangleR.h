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

#ifndef TRIANGLER_H
#define TRIANGLER_H

#include <QString>
#include <QMessageBox>


class TriangleRectangle
{
public:
    TriangleRectangle(double angle, double opposite, double adjacent, double hypotenuse, int angleUnit);

    bool exists();
    QString msg();
    QString msgTitle();
    QMessageBox::Icon msgIcon();

    double getAngle();
    double getH();
    double getL();
    double getR();
    double getOutput(int i);


private:
    void calculateA(double h, double l, double r);
    void calculateH(double aRad, double l, double r);
    void calculateL(double aRad, double h, double r);
    void calculateR(double aRad, double h, double l);

    double m_A, m_ARad, m_H, m_L, m_R;
    bool m_aunit; // false : DEG, true : Percent
    bool m_exists; // existence du triangle rectangle avec les côtés m_H, m_L, m_R et l'angle m_A
    QString m_msg; // message : cause de non existence ou vérification réussie
    QString m_msgTitle; // titre du QMessageBox
    QMessageBox::Icon m_msgStatus; // QMessageBox::Icon approprié au message

};

#endif // TRIANGLER_H
