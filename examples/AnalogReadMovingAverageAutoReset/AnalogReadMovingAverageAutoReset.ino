/*
 * Example of MovingAverage's auto-reset feature.
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

// Create moving average with window size of 100.
MovingAverage average(100);

// A function that computes and returns the value that we want (in this case
// the value of the analog pin 0 remapped to [0, 1].
float readInput() {
  return analogRead(0) / 1023.0f;
}

void setup() {
  // Begin serial.
  Serial.begin(57600);
  // Initialize the average using "smart" auto reset. Notice that this will call
  // the readInput() function ceil( (100-1) / 2) = 50 times.
  average.reset( readInput );
}

void loop() {
  // Update the value moving average with new analog reading and print the 
  // moving average's current value.
  Serial.println( average.update( readInput() ) );
}
