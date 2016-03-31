#include "TToABV.h"

//public:
TToABV::TToABV() {

  TToABV(false);
  
}

TToABV::TToABV(bool isLiquid) {

  _pressure = 1013.25;
  _isVapor = !isLiquid;

}

void TToABV::Liquid() {

  _isVapor = false;

}

void TToABV::Vapor() {

  _isVapor = true;

}

void TToABV::Pressure(float pressure) {

  _pressure = pressure;

}

void TToABV::Temperature(float temperature) {

  _temperature = temperature;

}

float TToABV::Pressure() {

  return _pressure;

}

float TToABV::Temperature() {
  
  return _temperature;

}

float TToABV::ABV(void) {
  
  if (_isVapor) {
    return TtoVaporABV(correctedAzeo(_temperature, _pressure));
  }
  else {
    return TtoLiquidABV(correctedH2O(_temperature, _pressure));
  }

}

//private:
bool _isVapor = true;
float _pressure = 1013.25;
float _temperature = 0;


// calculate the the boiling temperature of water for the measured pressure in Celsius
float TToABV::h2oBoilingPoint(float p) {

  float H2OInKelvin = -20330000 * 373.15 / (4157 * log(p / 1013.25) * 373.15 - 20330000);
  return H2OInKelvin - 273.15;

}

// Calculate the the azeotrope for the measured pressure in Celsius
float TToABV::azeotrope(float p) {

  float AzeotropeInKelvin = -19280000 * 351.324 / (4157 * log(p / 1013.25) * 351.324 - 19280000);
  return AzeotropeInKelvin - 273.15;

}

float TToABV::correctedH2O(float T, float P) {

  return T + 100 - h2oBoilingPoint(P);

}

float TToABV::correctedAzeo(float T, float P) {

  return T + 78.174 - azeotrope(P);

}

float TToABV::TtoLiquidABV(float T) {

  return 0;

};

float TToABV::TtoVaporABV(float T) {


  return 0;

}

