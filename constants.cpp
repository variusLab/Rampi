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

#include "constants.h"
#include <QDebug>

double rounded2Dec(const double & x)
{
    return floor(x*100. + 0.5)/100.;
}

double convertAngle(double x, int fromUnit, int toUnit)
{
    double res;

    if (fromUnit==AUnit::Deg and toUnit==AUnit::Percent)
        res = 100.*tan(x*M_PI/180.);
    else if (fromUnit==AUnit::Deg and toUnit==AUnit::Rad)
        res = x*M_PI/180.;

    else if (fromUnit==AUnit::Percent and toUnit==AUnit::Deg)
        res = atan(x/100.)*180./M_PI;
    else if (fromUnit==AUnit::Percent and toUnit==AUnit::Rad)
        res = atan(x/100.);

    else if (fromUnit==AUnit::Rad and toUnit==AUnit::Deg)
        res = x*180./M_PI;
    else if (fromUnit==AUnit::Rad and toUnit==AUnit::Percent)
        res = tan(x)*100.;

    else if (fromUnit==toUnit)
        res = x;

    else
        res = 0.;

    return res;
}


bool difference(const double & x, const double & y)
{
    return (abs(x-y) >= 0.01); // epsilon = 0.005
}

