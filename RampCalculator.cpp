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

#include "RampCalculator.h"
#include "ui_RampCalculator.h"

#include "TriangleR.h"
#include "constants.h"

#include <cmath> //pour abs

#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QDoubleSpinBox>


RampCalculator::RampCalculator(QWidget *parent) : QWidget(parent), ui(new Ui::RampCalculator)
{
    ui->setupUi(this);

    QChar alpha = QChar(0xb1, 0x03);
    ui->tlblAngle->setText(QString("Angle ").append(alpha)+ " :");

    /* valeurs min et max des QDoubleSpinBox */
    ui->cdSpBxAngleP->setRange(0, cPERCENT_MAX);
    ui->cdSpBxAngleD->setRange(0, cDEG_MAX);

    /* plage de valeurs de tdSpBxAngle est contrôlée par l'état des radioBtns "%" et "Deg" : */
    connect(ui->radioBtnP, &QRadioButton::toggled, this, &RampCalculator::changeSpBxAngleRange);
    ui->radioBtnP->setChecked(true);
    /* initialement, les radioBtns ne doivent pas être cochés (ds Qt Designer) */

    ui->tdSpBxH->setRange(0, H_MAX);
    ui->tdSpBxL->setRange(0, L_MAX);
    ui->tdSpBxR->setRange(0, R_MAX);

    // ToolTips des QDoubleSpinBoxes
    ui->cdSpBxAngleP->setToolTip(QString("min : 0.01 %, max : %1 %").arg(cPERCENT_MAX));
    ui->cdSpBxAngleD->setToolTip(QString("min : 0.01°, max : %1°").arg(cDEG_MAX));

    ui->tdSpBxH->setToolTip(QString("min : 0.01, max : %1").arg(H_MAX));
    ui->tdSpBxL->setToolTip(QString("min : 0.01, max : %1").arg(L_MAX));
    ui->tdSpBxR->setToolTip(QString("min : 0.01, max : %1").arg(R_MAX));


    /* Convertisseur d'angle */
    connect(ui->cbtnConvertir, &QPushButton::clicked, this, &RampCalculator::convert);
    connect(ui->cbtnEffacer, &QPushButton::clicked, this, &RampCalculator::cReset);

    /* Calculatrice trigonométrique */
    connect(ui->tbtnCalculer, &QPushButton::clicked, this, &RampCalculator::calculate);
    connect(ui->tbtnEffacer, &QPushButton::clicked, this, &RampCalculator::tReset);

}


RampCalculator::~RampCalculator()
{
    delete ui;
}

void RampCalculator::applySSTransition(QDoubleSpinBox *s)
{
    s->setStyleSheet(style::LightBlue);
    QTimer::singleShot(300, this, [s]() { s->setStyleSheet(style::Default); } );
}


void RampCalculator::changeSpBxAngleRange(bool checked)
{
    if(checked)
    {
        //qDebug() << "radioBtnP checked" << ui->radioBtnP->isChecked();
        ui->tdSpBxAngle->setRange(0, tPERCENT_MAX);
        ui->tdSpBxAngle->setToolTip(QString("min : 0.01 %, max : %1 %").arg(tPERCENT_MAX));

    }
        else
    {
        //qDebug() << "radioBtnDeg checked" << ui->radioBtnDeg->isChecked();
        ui->tdSpBxAngle->setRange(0, tDEG_MAX);
        ui->tdSpBxAngle->setToolTip(QString("min : 0.01°, max : %1°").arg(tDEG_MAX));

    }

}


void RampCalculator::convert()
{
    double angleP = ui->cdSpBxAngleP->value();
    double angleD = ui->cdSpBxAngleD->value();

    if (angleP and !angleD)
    {
        angleD = convertAngle(angleP, AUnit::Percent, AUnit::Deg);
        ui->cdSpBxAngleD->setValue(angleD);
        applySSTransition(ui->cdSpBxAngleD);
    }
    else if (!angleP and angleD)
    {
        angleP = convertAngle(angleD, AUnit::Deg, AUnit::Percent);
        ui->cdSpBxAngleP->setValue(angleP);
        applySSTransition(ui->cdSpBxAngleP);
    }
    else if(angleP and angleD)
    {
        double angleDfromP = convertAngle(angleP, AUnit::Percent, AUnit::Deg);
        qDebug() << "angleD - angleDfromP : " << angleD - angleDfromP;
        if ( abs(angleD-angleDfromP) >= epsilon )
        {

            QMessageBox::warning(this,
                                 "Erreur : données invalides",
                                 "Les valeurs indiquées ne correspondent pas au même angle."
                                 );
        }
        else
            QMessageBox::about(this,
                                 "Vérification",
                                 "Rien à calculer : tout est correct."
                                 );
    }
}



void RampCalculator::calculate()
{
    qDebug() << "Calculate...";
    QDoubleSpinBox * tdSpBx[4] = {ui->tdSpBxAngle, ui->tdSpBxH, ui->tdSpBxL, ui->tdSpBxR};
    double input[4];
    for (int i=0; i<4; ++i) input[i] = tdSpBx[i]->value();

    int aUnit = static_cast<int>(ui->radioBtnP->isChecked());

    TriangleRectangle u(input[0], input[1], input[2], input[3], aUnit);


    if (u.exists())
        for(int i=0; i<4; ++i)
        {
            if (!input[i])
            {
                double val = u.getOutput(i);
                double valDisplay = rounded2Dec(val);
                qDebug() << "u.getOutput(" << fieldName[i] << ") : " << val;
                if (valDisplay >= 0.01 and valDisplay <= tdSpBx[i]->maximum())
                {
                    tdSpBx[i]->setValue(val);
                    applySSTransition(tdSpBx[i]);
                }
                else
                    QMessageBox::warning(this,
                         "Erreur : impossible d'afficher une valeur",
                         QString("La valeur du champ %1 (%2) est en dehors de la plage autorisée "
                                 "(min : %3, max : %4).").arg(fieldName[i]).arg(val).arg(0.01).arg(tdSpBx[i]->maximum())
                                         );
            }
        }


    QString msg = u.msg();

    if (!msg.isEmpty())
    {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(u.msgTitle());
        msgBox.setText(msg);
        msgBox.setIcon(u.msgIcon());
        msgBox.exec();
    }

}

void RampCalculator::cReset()
{
    ui->cdSpBxAngleP->setValue(0);
    ui->cdSpBxAngleD->setValue(0);
}


void RampCalculator::tReset()
{
    ui->tdSpBxAngle->setValue(0);
    ui->tdSpBxH->setValue(0);
    ui->tdSpBxL->setValue(0);
    ui->tdSpBxR->setValue(0);
}
