/*
 * MovingAverage.h
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
#ifndef MOVINGAVERAGE_H_
#define MOVINGAVERAGE_H_

/// An exponential moving average class.
class MovingAverage {
public:
#ifdef MOVINGAVERAGE_USE_DOUBLE
typedef double real;
#else
typedef float real;
#endif

  // The alpha (mixing) variable (in [0,1]).
  float _alpha;

  // The current value of the exponential moving average.
  real _value;

  /**
   * Constructs the moving average, starting with #startValue# as its value. The #alphaOrN# argument
   * has two options:
   * - if <= 1 then it's used directly as the alpha value
   * - if > 1 then it's used as the "number of items that are considered from the past" (*)
   * (*) Of course this is an approximation. It actually sets the alpha value to 2 / (n - 1)
   */
  MovingAverage(float alphaOrN=0.1, real startValue=0);
  virtual ~MovingAverage() {}

  /**
   * Resets the moving average to #startValue#.
   */
  void reset(real startValue);

  /**
   * This function will reset the moving average with an appropriate value, waiting for convergence.
   * It is especially useful for small alpha values. Call it with a pointer to a function that returns
   * the value that you want.
   */
  void reset(real (*valueFunc)(void));
 
  /**
   * Updates the moving average with new value #v# (also returns the current value).
   */
  real update(real v);

  /**
   * Returns the value of the moving average.
   */
  real get() const { return _value; }

};

#endif /* MOVINGAVERAGE_H_ */
