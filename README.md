# MovingAverage
MovingAverage library for Arduino or Wiring   
by Sofian Audry  
Inspired by code by [Karsten Kutza](http://www.ip-atlas.com/pub/nap/nn-src/bpn.txt)

A memory-efficient [exponential moving average](https://en.wikipedia.org/wiki/Moving_average#Exponential_moving_average) library.

## Repository

http://github.com/sofian/MovingAverage

Download the latest version here : https://github.com/sofian/MovingAverage/archive/master.zip

## Installation
Copy the MovingAverage folder to your Arduino libraries folder.


## Basic Example
```arduino
// Include the library.
#include <MovingAverage.h>

// Create a moving average with alpha = 0.1 (default).
MovingAverage average;

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

```

## Usage

### Include the library

```arduino
// Include the MovingAverage library.
#include <MovingAverage.h> 

```

### Create an instance
A MovingAverage instance can be created in a number of ways.
A moving average works using a weighting decrease coefficient (α), a value between 0 and 1 that is used to mix the current value with the trace of all preceding values. A higher α discounts older observations faster.

To create an instance with default α (0.1): 
```arduino
MovingAverage average;
```

To create an instance with a specific α value (here 0.01):
```arduino
MovingAverage average(0.01);
```

It is also possible to specify a window size N instead of α by sending an argument > 1 as the first parameter of the constructor. In this case, the α coefficient will be approximated to match the window size using the formula α = 2 / (N+1). This is of course not exact but more like a rule of thumb for setting α.

For example, to create an instance corresponding to the moving average over a window size of approximatively 100 samples:
```arduino
MovingAverage average(100); // will set the alpha value to approx. 0.0198
```

The second parameter allows to set the starting value of the moving average (default is 0). It is however recommended to initialize it using the reset(value) using an unbiased value representative of the distribution, such as a single sample.

### update(value)

Updates the moving average with new value.
```arduino
average.update( analogRead(0) );
```

The function also returns the current value (optional):
```arduino
float value = average.update( analogRead(0) );
Serial.println(value);
```

### get()

Returns the value of the moving average.

```arduino
// In this example the two variables (value1 and value2) are equal.
float value1 = average.update( analogRead(0) );
float value2 = average.get();
Serial.println(value1);
Serial.println(value2);
```

### reset(value)

Resets the moving average to given value.

```arduino
reset( 0.5 );
Serial.println( average.get() ); // will print "0.5"
```

It is generally recommended to initialize the moving average with an unbiased sample from the distribution in the setup() method. Example:

```arduino
reset( analogRead(0) );
```

### reset(function) (ADVANCED)

For small alpha values, initializing the moving average with a single value from the distribution might be tricky because the chain will not have the time to converge. The library provides a simple solution to that in the form of an "auto-reset" method. Calling it with pointer to the function that returns elements from the distribution you want to compute the average on, it will first perform a certain number of readings from the distribution and compute the average in order to set the initial value. The function will be called M times where M = ceil(1/alpha - 1).

Source: http://www.had2know.com/finance/exponential-moving-average-ema-calculator.html

```arduino
MovingAverage average(0.01);

float readInput() {
  return analogRead(0);
}
...
// Will perform the initialization, calling readInput() 99 times (1/0.01 - 1) 
// and taking he average to set the initial value.
reset( readInput );
```

