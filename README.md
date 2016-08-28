# TemperatureToABV
Vistion Stills Arduino library for converting temperature of liquid or vapor to alcohol by volume, encapsulating functions created
by Edwin Croissant.  The file TtoABV_SMT172.h from [https://github.com/EdwinCroissantArduinoLibraries/T2ABV](https://github.com/EdwinCroissantArduinoLibraries/T2ABV) is copied here.

## Explanation
This library receives temperature (°C) and pressure (millibars) to calculate alcohol by volume (ABV) of liquid or vapor.

The arrays of these functions are based on the Technical Paper 19 by Herminio M. Brau dated April 1957.

Pressure influence is calculated using the [Clausius-Clapeyron relation](https://en.wikipedia.org/wiki/Clausius%E2%80%93Clapeyron_relation).

For the liquid ABV, the temperature is corrected with the change in boiling point of water. At higher altitudes there will be some error for the high ABV values.

For the vapor ABV the temperature is corrected with the change in boiling point of the azeotrope. At higher altitudes there will be some error for the low ABV values.

If the corrected temperature is lower than the azeotrope the negative index of the array is returned.

If the corrected temperature is higher than 100°C  0 is returned.

## Install
Download and install this library in your Arduino library folder.
The instructions for installing an Arduino library can be found [here](https://www.arduino.cc/en/Guide/Libraries).

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
See license [here](../master/LICENSE).
