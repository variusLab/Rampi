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

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>
#include <QString>

enum AUnit {Deg, Percent, Rad};

enum field {A, H, L, R};

const QString fieldName[4] = {"angle", "H", "L", "R"};

namespace style {

const QString LightBlue = "border: 1px solid rgb(85, 170, 255);"
              "border-radius: 5px;"
              "padding: 0 2 px;"
              "background: rgbrgb(248, 248, 248);";

const QString Default = "border: 1px solid rgb(212, 220, 236);"
              "border-radius: 5px;"
              "padding: 0 2 px;"
              "background: rgb(255, 255, 255);";

}

const double cPERCENT_MAX = 5729.;
const double cDEG_MAX = 89.;

const double tPERCENT_MAX = 5729.;
const double tDEG_MAX = 89.;


const double H_MAX = 5729.;
const double L_MAX = 5729.;
const double R_MAX = 8102.0;

const double epsilon = 0.005;


double rounded2Dec(const double &x);

double convertAngle(double x, int fromUnit, int toUnit);

bool difference(const double & x, const double & y);


#endif // CONSTANTS_H
