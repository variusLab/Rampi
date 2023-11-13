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

#ifndef RAMPCALCULATOR_H
#define RAMPCALCULATOR_H

#include <QWidget>
#include <cmath>
class QDoubleSpinBox;

QT_BEGIN_NAMESPACE
namespace Ui { class RampCalculator; }
QT_END_NAMESPACE


class RampCalculator : public QWidget
{
    Q_OBJECT

public:
    RampCalculator(QWidget *parent = nullptr);
    ~RampCalculator();

    void applySSTransition(QDoubleSpinBox * s);


public slots:
    void changeSpBxAngleRange(bool checked);
    void convert();
    void calculate();
    void cReset();
    void tReset();

private:
    Ui::RampCalculator *ui;    

    /* ds QtDesigner, tous les QDoubleSpinBox ont étés configurés à avoir :
     * QAbstractSpinBox::setSpecialValueText("-") (équivalent à la valeur 0)
     * QAbstractSpinBox::correctionMode = correctToNearestValue (et non correctToPreviousValue mise par défaut)
     * cette dernière ppté assure que qd l'utilisateur efface le champ, le symbole "-" apparait et non la valeur précédente
     * Observations: même si le champ a une valeur non nulle, sa propriété specialValueText() vaut tjs "-".
     * En ravanche: si "-" est affiché, la propriété value() vaut bien 0.
     * */
};
#endif // RAMPCALCULATOR_H
