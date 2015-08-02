/*
 * Simple example of using MovingAverage with analog inputs.
 *
 * (c) 2015 Sofian Audry -- info(@)sofianaudry(.)com
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

#include <MovingAverage.h>

// Create moving average with alpha = 0.1f.
MovingAverage average(0.1f);

void setup() {
  // Begin serial.
  Serial.begin(57600);
  // Initialize the average with the first value from analogRead().
  average.reset( analogRead(0) );
}

void loop() {
  // Update the value moving average with new analog reading and print the 
  // moving average's current value.
  Serial.println( average.update( analogRead(0) ) );
}
