/*
 * MovingAverage.cpp
 *
 * An exponential moving average class for Arduino/Wiring.
 *
 * (c) 2011-2015 Sofian Audry -- info(@)sofianaudry(.)com
 * Adapted from the Qualia library: https://github.com/sofian/qualia
 * Inspired by code by Karsten Kutza
 * http://www.ip-atlas.com/pub/nap/nn-src/bpn.txt
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

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "MovingAverage.h"

MovingAverage::MovingAverage(float alphaOrN, real startValue) : _value(startValue) {
  alphaOrN = max(alphaOrN, 0); // make sure alphaOrN >= 0
  _alpha = (alphaOrN > 1 ?
      2 / (alphaOrN + 1) :
      alphaOrN);
}

void MovingAverage::reset(real startValue) {
  _value = startValue;
}

MovingAverage::real MovingAverage::update(real v) {
  return (_value -= _alpha * (_value - v));
}
