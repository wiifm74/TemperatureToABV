/*
Needs math.h.
The Dallas DS18B20 sensor resolution (°DC) is 1/16 °C and starts at 0 °C.
DCtoLiquidABV converts °DC to the liquid ABV in percent.
DCtoVaporABV converts °DC to the vapor ABV in percent.
If the corrected temperature is lower then the azeotrope the negative index is returned
If the corrected temperature is higher than  100 °C  0 is returned

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
Code by Edwin Croissant date 03dec15.
Removed FLASH library dependency and reduced size of array. 04mar15 */

#ifndef T2ABV
#define T2ABV
#include <avr/pgmspace.h>

float h2oBoilingPoint(float p) {
	// calculate the the boiling temperature of water for the measured pressure in Celsius
	float H2OInKelvin = -20330000 * 373.15
			/ (4157 * log(p / 1013.25) * 373.15 - 20330000);
	return H2OInKelvin - 273.15;
}

float azeotrope(float p) {
	// Calculate the the azeotrope for the measured pressure in Celsius
	float AzeotropeInKelvin = -19280000 * 351.324
			/ (4157 * log(p / 1013.25) * 351.324 - 19280000);
	return AzeotropeInKelvin - 273.15;
}

int16_t Raw2DCatP(int16_t DallasRaw, float P, bool Azeo) {
	// Converts and pressure adjust the Dallas raw sensor output to °DC
	// DallasRaw is in 1/128 °C but the sensor resolution °DC is in 1/16 °C
	int16_t TinDC = DallasRaw / 8;
	if (Azeo) {
		// 1251 is the the azeotrope at 1013.25 hPa in °DC
		return TinDC + 1251 - int16_t(azeotrope(P) * 16 + 0.5);
	} else {
		// 1600 is the boilingpoint of H2O at 1013.25 hPa in °DC
		return TinDC + 1600 - int16_t(h2oBoilingPoint(P) * 16 + 0.5);
	}
}
//float TtoLiquidABV(float T) {
//	const static uint8_t ABV[] PROGMEM = {
//      /* by using PROGMEM the array stays in the program memory and is not copied to precious sram. */


float DCtoLiquidABV(int16_t TinDC) {
	const static uint8_t ABV[] PROGMEM = {
			  /* by using PROGMEM the array stays in the program memory and is not copied to precious sram. */
			 196, 181, 166, 158, 151, 145, 136, 129, 123, 117, 110, 104,  98,  92,  86,  79,  74,  68,  62,  56,
			  50,  45,  39,  33,  27,  21,  15,   9,   3, 253, 247, 241, 235, 229, 224, 218, 212, 207, 201, 195,
			 191, 188, 183, 178, 172, 165, 158, 151, 145, 139, 133, 127, 122, 116, 111, 105,  98,  93,  87,  80,
			  74,  69,  63,  57,  52,  46,  40,  36,  29,  24,  18,  13,   8,   2, 252, 246, 241, 235, 229, 224,
			 217, 212, 206, 201, 196, 191, 187, 182, 177, 172, 167, 163, 159, 155, 150, 146, 141, 137, 133, 129,
			 125, 121, 116, 112, 107, 103,  99,  94,  90,  86,  82,  78,  74,  70,  67,  63,  59,  55,  50,  46,
			  42,  38,  33,  29,  25,  21,  16,  13,  11,   9,   8,   7,   7,   5,   4,   3,   2,   1, 255, 254,
			 253, 252, 251, 250, 249, 247, 246, 243, 241, 238, 236, 233, 231, 228, 226, 223, 221, 219, 217, 215,
			 213, 211, 210, 208, 206, 204, 202, 200, 198, 197, 195, 193, 191, 190, 188, 186, 185, 183, 181, 179,
			 177, 175, 173, 171, 170, 168, 166, 165, 163, 162, 160, 159, 157, 156, 155, 153, 151, 150, 148, 147,
			 146, 145, 143, 142, 141, 139, 138, 137, 135, 134, 133, 132, 131, 130, 129, 128, 126, 125, 124, 123,
			 122, 120, 119, 118, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 105, 104, 103, 102, 101,  99,
			  98,  97,  95,  94,  93,  92,  91,  89,  88,  87,  86,  85,  84,  83,  82,  81,  80,  79,  79,  78,
			  77,  76,  75,  74,  72,  71,  70,  68,  67,  66,  65,  64,  63,  62,  61,  60,  59,  58,  58,  57,
			  55,  54,  53,  52,  51,  50,  49,  49,  48,  47,  46,  46,  45,  45,  44,  43,  43,  42,  41,  41,
			  40,  39,  38,  38,  37,  36,  35,  34,  33,  32,  31,  30,  29,  28,  28,  27,  26,  26,  25,  24,
			  24,  23,  22,  21,  20,  20,  19,  18,  17,  16,  15,  14,  13,  12,  11,  10,  10,   9,   9,   8,
			   8,   7,   7,   7,   6,   6,   5,   4,   2,   0}; // 350 values

	// Calculate the index for the table (1251 is the the azeotrope at 1013.25 hPa and the
	// starting point of the table) in °DC
	int16_t IndexABV = TinDC - 1251;

	if (IndexABV < 0) return IndexABV; // Below azeotope
	if (IndexABV >= int16_t(sizeof ABV / sizeof *ABV)) return 0; // Above 100 °C
	if (IndexABV < 29) return float(pgm_read_byte(ABV + IndexABV) + 768) / 10;
	if (IndexABV < 74) return float(pgm_read_byte(ABV + IndexABV) + 512) / 10;
	if (IndexABV < 138) return float(pgm_read_byte(ABV + IndexABV) + 256) / 10;
	return float(pgm_read_byte(ABV + IndexABV)) / 10;
};

float DCtoVaporABV(int16_t TinDC) {
	const static uint8_t ABV[] PROGMEM = {
			  /* by using PROGMEM the array stays in the program memory and is not copied to precious sram. */

			 197, 185, 174, 170, 165, 162, 156, 153, 150, 147, 143, 141, 138, 136, 133, 130, 128, 127, 125, 122,
			 120, 119, 117, 114, 113, 111, 109, 107, 105, 104, 102, 101,  99,  98,  96,  95,  93,  92,  91,  90,
			  89,  87,  86,  85,  84,  82,  81,  79,  78,  77,  76,  74,  73,  72,  71,  70,  69,  68,  66,  65,
			  64,  63,  62,  61,  60,  59,  58,  57,  55,  54,  53,  52,  50,  50,  49,  47,  46,  45,  43,  42,
			  42,  40,  39,  38,  36,  35,  34,  33,  32,  30,  29,  29,  27,  26,  26,  25,  23,  21,  20,  19,
			  18,  17,  16,  14,  13,  12,  11,   9,   8,   6,   5,   3,   2,   1, 255, 253, 252, 250, 248, 247,
			 245, 244, 242, 240, 238, 236, 234, 232, 231, 230, 229, 229, 228, 228, 227, 226, 225, 225, 224, 223,
			 222, 222, 221, 220, 220, 219, 218, 216, 215, 213, 212, 210, 208, 206, 205, 203, 202, 200, 199, 197,
			 196, 194, 193, 192, 190, 189, 187, 186, 184, 183, 181, 179, 178, 176, 175, 173, 171, 169, 168, 166,
			 164, 162, 161, 159, 157, 155, 153, 151, 150, 148, 146, 144, 143, 141, 139, 137, 135, 133, 131, 129,
			 127, 125, 124, 122, 119, 117, 115, 113, 111, 109, 107, 105, 104, 102, 100,  99,  97,  95,  94,  91,
			  89,  87,  84,  82,  80,  78,  76,  73,  71,  69,  67,  65,  63,  61,  59,  56,  54,  51,  49,  46,
			  43,  40,  37,  34,  31,  28,  26,  23,  20,  17,  15,  12,   9,   6,   3,   1, 254, 252, 250, 247,
			 244, 241, 238, 234, 229, 225, 220, 215, 211, 206, 202, 197, 193, 189, 186, 182, 179, 175, 172, 168,
			 162, 157, 151, 146, 140, 135, 131, 128, 124, 121, 118, 115, 111, 108, 105, 101,  97,  93,  88,  83,
			  78,  73,  68,  62,  56,  50,  43,  37,  30,  24,  19,  14,   9,   4, 255, 250, 245, 240, 235, 228,
			 221, 214, 207, 200, 192, 184, 176, 168, 160, 153, 145, 137, 130, 123, 116, 110, 104,  98,  92,  87,
			  82,  77,  72,  68,  64,  60,  50,  40,  20,   0};  // 350 values

	// Calculate the index for the table (1251 is the the azeotrope at 1013.25 hPa and the
	// starting point of the table) in °DC
	int16_t IndexABV = TinDC - 1251;

	if (IndexABV < 0) return IndexABV; // Below azeotope
	if (IndexABV >= int16_t(sizeof ABV / sizeof *ABV)) return 0; // Above 100 °C
	if (IndexABV < 114) return float(pgm_read_byte(ABV + IndexABV) + 768) / 10;
	if (IndexABV < 256) return float(pgm_read_byte(ABV + IndexABV) + 512) / 10;
	if (IndexABV < 314) return float(pgm_read_byte(ABV + IndexABV) + 256) / 10;
	return float(pgm_read_byte(ABV + IndexABV)) / 10;
};

#endif /* T2ABV.h */
