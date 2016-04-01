/*
  Needs math.h.
  TtoLiquidABV converts �C to the liquid ABV in percent.
  TCtoVaporABV converts �C to the vapor ABV in percent.
  If the corrected temperature is lower then the azeotrope the negative index is returned
  If the corrected temperature is higher than  100 �C  0 is returned

  The array's of these functions are based on the Technical Paper 19 by
  Herminio M. Brau dated April 1957.

  Pressure influence is calculated with the Clausius Clapeyron relation.
  For the liquid ABV the temperature is corrected with the change in boiling
  point of water. At higher altitudes there will be some error for the high ABV values.
  For the vapor ABV the temperature is corrected with the change in boiling
  point of the azeotrope. At higher altitudes there will be some error
  for the low ABV values.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the version 3 GNU General Public License as
  published by the Free Software Foundation.
  Code by Edwin Croissant date 03dec15. */

#ifndef T2ABV
#define T2ABV

#include <math.h>
#include <stdint.h>
#include <avr/pgmspace.h>

class TToABV {
  public:
    TToABV();
    TToABV(bool isLiquid);
    void Liquid();
    void Vapor();
    void Pressure(float pressure);
    void Temperature(float temperature);
    float Pressure();
    float Temperature();
    float ABV(void);

  private:
    bool _isVapor = true;
float _pressure = 1013.25;
float _temperature = 0;

    float h2oBoilingPoint(float p);
    float azeotrope(float p);
    float correctedH2O(float T, float P);
    float correctedAzeo(float T, float P);
    float TtoLiquidABV(float T);
    float TtoVaporABV(float T);

};

#endif
