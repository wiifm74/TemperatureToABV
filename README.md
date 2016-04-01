# TemperatureToABV

Vistion Stills Arduino library for converting temperature of liquid or vapor to alcohol by volume

## Explanation

## Install

## Usage
```c++
#include <TToABV.h>

// delcare instance
TToABV tToABV;

void loop() {
	
	float pressure = 1013.25;
	float temperature = 92.1;
	float abv = 0;
	
	// set pressure
	tToABV.Pressure(pressure);
	
	// get stored pressure
	pressure = tToABV.Pressure();
	
	// set temperature in degrees C
	tToABV.Temperature(temperature);
	
	// get stored temperature
	temperature = tToABV.Temperature();
	
	// set to vapor abv calculations
	tToABV.Vapor()
	// get alcohol by volume for vapor
	abv = tToABV.ABV();
	
	// set to liquid abv calculations
	tToABV.Liquid()	
	// get alcohol by volume for liquid
	abv = tToABV.ABV();	
	
}
```

## License
See license [here](../blob/master/LICENSE)
