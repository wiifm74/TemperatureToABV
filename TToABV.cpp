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

  const static uint8_t ABV[] PROGMEM = {
      /* by using PROGMEM the array stays in the program memory and is not copied to precious sram. */
      198, 195, 192, 190, 188, 185, 183, 181, 179, 172, 169, 168, 168, 166, 165, 164, 162, 161, 160, 159,
      158, 157, 155, 154, 153, 151, 150, 149, 148, 147, 146, 146, 145, 144, 143, 142, 139, 137, 136, 135,
      134, 133, 132, 131, 130, 129, 127, 126, 125, 124, 124, 123, 122, 120, 119, 118, 117, 117, 116, 115,
      114, 113, 112, 111, 110, 109, 108, 106, 105, 104, 103, 102, 101, 100,  99,  99,  98,  97,  96,  95,
       94,  93,  92,  91,  90,  89,  88,  87,  86,  85,  84,  83,  82,  81,  80,  79,  78,  77,  76,  76,
       75,  74,  73,  72,  71,  70,  69,  68,  67,  66,  65,  64,  63,  62,  62,  61,  60,  59,  58,  57,
       56,  55,  54,  53,  52,  51,  50,  49,  49,  48,  47,  46,  45,  44,  43,  42,  41,  40,  39,  38,
       37,  36,  35,  34,  33,  32,  31,  31,  30,  29,  28,  27,  26,  25,  24,  23,  22,  21,  20,  19,
       18,  17,  16,  15,  14,  13,  12,  11,  10,   9,   8,   7,   6,   6,   5,   4,   3,   2,   1,   0,
      255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 243, 242, 241, 240, 239, 238, 237,
      236, 235, 234, 233, 232, 231, 230, 229, 229, 228, 227, 226, 225, 224, 223, 222, 221, 220, 220, 219,
      218, 217, 216, 215, 214, 213, 212, 211, 210, 209, 209, 208, 207, 206, 205, 204, 203, 202, 201, 200,
      199, 198, 198, 197, 196, 195, 194, 193, 193, 192, 192, 191, 191, 190, 190, 189, 189, 188, 188, 187,
      186, 185, 184, 184, 183, 182, 181, 180, 180, 179, 178, 177, 176, 175, 174, 173, 172, 171, 170, 169,
      168, 167, 165, 164, 163, 162, 161, 159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147,
      146, 145, 144, 143, 142, 141, 140, 139, 138, 137, 137, 136, 135, 134, 133, 132, 131, 130, 129, 128,
      127, 126, 125, 124, 123, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 114, 113, 112, 111, 110,
      109, 108, 107, 106, 105, 104, 103, 102, 101, 100,  99,  98,  97,  96,  95,  95,  94,  93,  92,  91,
       90,  89,  88,  87,  86,  85,  84,  83,  82,  81,  80,  79,  78,  77,  76,  75,  74,  73,  72,  71,
       70,  69,  69,  68,  67,  66,  65,  64,  63,  62,  61,  60,  59,  58,  58,  57,  56,  55,  54,  53,
       52,  52,  51,  50,  49,  48,  47,  46,  45,  44,  43,  42,  41,  40,  40,  39,  38,  38,  37,  36,
       35,  34,  33,  32,  31,  30,  29,  28,  27,  27,  26,  25,  24,  23,  22,  21,  20,  20,  19,  18,
       17,  16,  15,  14,  13,  13,  12,  11,  10,   9,   8,   7,   6,   6,   5,   4,   3,   2,   1,   0,
      255, 254, 253, 252, 251, 250, 249, 248, 247, 247, 246, 245, 244, 243, 242, 241, 240, 239, 239, 238,
      237, 236, 235, 234, 233, 232, 231, 231, 230, 229, 228, 227, 226, 225, 224, 223, 222, 221, 220, 219,
      218, 217, 216, 215, 214, 213, 213, 212, 211, 210, 209, 208, 207, 206, 205, 205, 204, 203, 202, 202,
      201, 200, 199, 198, 198, 197, 196, 195, 195, 194, 193, 192, 191, 191, 190, 189, 188, 188, 187, 186,
      185, 184, 184, 183, 182, 181, 180, 180, 179, 178, 177, 177, 176, 175, 174, 173, 172, 172, 171, 170,
      169, 169, 168, 167, 166, 166, 165, 164, 164, 163, 162, 162, 161, 161, 160, 159, 159, 158, 158, 157,
      156, 155, 155, 154, 153, 153, 152, 151, 150, 150, 149, 148, 148, 147, 146, 146, 145, 144, 143, 143,
      142, 141, 141, 140, 139, 138, 138, 137, 136, 136, 135, 134, 134, 133, 132, 132, 131, 131, 130, 129,
      129, 128, 128, 127, 126, 126, 125, 124, 124, 123, 122, 121, 121, 120, 119, 119, 118, 117, 116, 116,
      115, 114, 114, 113, 112, 111, 111, 110, 109, 109, 108, 107, 107, 106, 105, 105, 104, 103, 103, 102,
      101, 101, 100,  99,  98,  97,  97,  96,  95,  94,  94,  93,  92,  92,  91,  90,  90,  89,  89,  88,
       87,  87,  86,  85,  85,  84,  84,  83,  82,  82,  81,  80,  80,  79,  78,  78,  77,  76,  76,  75,
       74,  74,  73,  73,  72,  71,  71,  70,  70,  69,  68,  68,  67,  67,  66,  65,  65,  64,  64,  63,
       62,  62,  61,  60,  60,  59,  58,  58,  57,  56,  56,  55,  55,  54,  53,  52,  52,  51,  50,  49,
       49,  48,  47,  47,  46,  45,  45,  44,  43,  43,  42,  41,  41,  40,  40,  39,  38,  38,  37,  36,
       36,  35,  34,  34,  33,  32,  32,  31,  30,  30,  29,  28,  28,  27,  26,  26,  25,  24,  24,  23,
       22,  21,  21,  20,  19,  18,  18,  17,  16,  16,  15,  14,  14,  13,  13,  12,  12,  12,  11,  11,
       11,  11,  10,  10,  10,  10,   9,   9,   9,   9,   8,   8,   8,   8,   8,   8,   8,   8,   7,   7,
        7,   7,   7,   7,   7,   7,   7,   6,   6,   6,   6,   6,   5,   5,   5,   5,   5,   4,   4,   4,
        4,   4,   4,   3,   3,   3,   3,   3,   2,   2,   2,   2,   2,   1,   1,   1,   1,   1,   0,   0,
        0,   0,   0, 255, 255, 255, 255, 255, 255, 254, 254, 254, 254, 254, 253, 253, 253, 253, 253, 252,
      252, 252, 252, 252, 251, 251, 251, 251, 251, 251, 251, 250, 250, 250, 250, 250, 250, 249, 249, 249,
      249, 249, 248, 248, 248, 248, 247, 247, 247, 247, 247, 246, 246, 246, 246, 245, 245, 244, 244, 244,
      243, 243, 242, 242, 242, 241, 241, 240, 240, 240, 239, 239, 238, 238, 238, 237, 237, 236, 236, 236,
      235, 235, 234, 234, 234, 233, 233, 232, 232, 232, 231, 231, 230, 230, 230, 229, 229, 228, 228, 228,
      227, 227, 226, 226, 225, 225, 225, 224, 224, 223, 223, 223, 222, 222, 222, 221, 221, 220, 220, 220,
      219, 219, 219, 219, 218, 218, 218, 217, 217, 217, 216, 216, 216, 216, 215, 215, 215, 214, 214, 214,
      213, 213, 213, 213, 212, 212, 212, 211, 211, 211, 211, 210, 210, 210, 210, 209, 209, 209, 208, 208,
      208, 207, 207, 207, 207, 206, 206, 206, 205, 205, 205, 204, 204, 204, 204, 203, 203, 203, 202, 202,
      202, 201, 201, 201, 200, 200, 200, 200, 199, 199, 199, 198, 198, 198, 197, 197, 197, 197, 196, 196,
      196, 195, 195, 195, 195, 194, 194, 194, 194, 193, 193, 193, 192, 192, 192, 192, 191, 191, 191, 191,
      190, 190, 190, 190, 189, 189, 189, 188, 188, 188, 188, 187, 187, 187, 187, 186, 186, 186, 185, 185,
      185, 184, 184, 184, 184, 183, 183, 183, 182, 182, 182, 181, 181, 181, 180, 180, 180, 180, 179, 179,
      179, 178, 178, 178, 177, 177, 177, 176, 176, 176, 176, 175, 175, 175, 174, 174, 174, 173, 173, 173,
      173, 172, 172, 172, 172, 171, 171, 171, 170, 170, 170, 170, 169, 169, 169, 169, 168, 168, 168, 168,
      167, 167, 167, 167, 166, 166, 166, 165, 165, 165, 165, 164, 164, 164, 164, 163, 163, 163, 163, 162,
      162, 162, 162, 161, 161, 161, 161, 160, 160, 160, 160, 159, 159, 159, 159, 159, 158, 158, 158, 158,
      158, 157, 157, 157, 157, 156, 156, 156, 156, 156, 155, 155, 155, 155, 154, 154, 154, 154, 153, 153,
      153, 153, 152, 152, 152, 152, 151, 151, 151, 151, 150, 150, 150, 150, 149, 149, 149, 149, 148, 148,
      148, 148, 148, 147, 147, 147, 147, 147, 146, 146, 146, 146, 146, 145, 145, 145, 145, 145, 144, 144,
      144, 144, 144, 143, 143, 143, 143, 143, 142, 142, 142, 142, 141, 141, 141, 141, 141, 140, 140, 140,
      140, 139, 139, 139, 139, 139, 138, 138, 138, 138, 137, 137, 137, 137, 137, 136, 136, 136, 136, 136,
      135, 135, 135, 135, 135, 135, 134, 134, 134, 134, 134, 133, 133, 133, 133, 133, 133, 132, 132, 132,
      132, 132, 132, 131, 131, 131, 131, 131, 131, 130, 130, 130, 130, 130, 129, 129, 129, 129, 129, 129,
      128, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 126, 126, 126, 126, 126, 126, 125, 125, 125,
      125, 125, 124, 124, 124, 124, 124, 123, 123, 123, 123, 123, 122, 122, 122, 122, 122, 121, 121, 121,
      121, 120, 120, 120, 120, 120, 119, 119, 119, 119, 119, 118, 118, 118, 118, 118, 117, 117, 117, 117,
      117, 116, 116, 116, 116, 116, 115, 115, 115, 115, 115, 115, 114, 114, 114, 114, 114, 113, 113, 113,
      113, 113, 112, 112, 112, 112, 112, 112, 111, 111, 111, 111, 111, 111, 110, 110, 110, 110, 110, 110,
      109, 109, 109, 109, 109, 109, 108, 108, 108, 108, 108, 108, 107, 107, 107, 107, 107, 107, 106, 106,
      106, 106, 106, 105, 105, 105, 105, 105, 105, 104, 104, 104, 104, 104, 103, 103, 103, 103, 103, 102,
      102, 102, 102, 102, 101, 101, 101, 101, 101, 100, 100, 100, 100, 100,  99,  99,  99,  99,  99,  98,
       98,  98,  98,  98,  97,  97,  97,  97,  96,  96,  96,  96,  96,  95,  95,  95,  95,  95,  94,  94,
       94,  94,  94,  93,  93,  93,  93,  93,  92,  92,  92,  92,  92,  91,  91,  91,  91,  91,  91,  90,
       90,  90,  90,  90,  89,  89,  89,  89,  89,  89,  88,  88,  88,  88,  88,  88,  87,  87,  87,  87,
       87,  86,  86,  86,  86,  86,  86,  85,  85,  85,  85,  85,  85,  84,  84,  84,  84,  84,  84,  83,
       83,  83,  83,  83,  83,  82,  82,  82,  82,  82,  82,  81,  81,  81,  81,  81,  81,  81,  81,  80,
       80,  80,  80,  80,  80,  80,  80,  79,  79,  79,  79,  79,  79,  79,  79,  78,  78,  78,  78,  78,
       78,  78,  77,  77,  77,  77,  77,  77,  77,  76,  76,  76,  76,  76,  76,  76,  75,  75,  75,  75,
       75,  74,  74,  74,  74,  74,  73,  73,  73,  73,  72,  72,  72,  72,  72,  71,  71,  71,  71,  70,
       70,  70,  70,  70,  69,  69,  69,  69,  69,  68,  68,  68,  68,  68,  67,  67,  67,  67,  67,  67,
       66,  66,  66,  66,  66,  66,  65,  65,  65,  65,  65,  65,  64,  64,  64,  64,  64,  64,  63,  63,
       63,  63,  63,  63,  63,  62,  62,  62,  62,  62,  62,  62,  61,  61,  61,  61,  61,  61,  61,  60,
       60,  60,  60,  60,  60,  59,  59,  59,  59,  59,  59,  59,  58,  58,  58,  58,  58,  58,  58,  57,
       57,  57,  57,  57,  57,  56,  56,  56,  56,  56,  56,  55,  55,  55,  55,  55,  55,  54,  54,  54,
       54,  54,  54,  53,  53,  53,  53,  53,  53,  52,  52,  52,  52,  52,  52,  51,  51,  51,  51,  51,
       51,  50,  50,  50,  50,  50,  50,  50,  49,  49,  49,  49,  49,  49,  49,  49,  48,  48,  48,  48,
       48,  48,  48,  48,  48,  47,  47,  47,  47,  47,  47,  47,  47,  47,  46,  46,  46,  46,  46,  46,
       46,  46,  46,  45,  45,  45,  45,  45,  45,  45,  45,  45,  45,  44,  44,  44,  44,  44,  44,  44,
       44,  44,  44,  44,  43,  43,  43,  43,  43,  43,  43,  43,  43,  42,  42,  42,  42,  42,  42,  42,
       42,  42,  41,  41,  41,  41,  41,  41,  41,  41,  41,  40,  40,  40,  40,  40,  40,  40,  40,  40,
       39,  39,  39,  39,  39,  39,  39,  39,  38,  38,  38,  38,  38,  38,  38,  37,  37,  37,  37,  37,
       37,  37,  36,  36,  36,  36,  36,  36,  35,  35,  35,  35,  35,  35,  34,  34,  34,  34,  34,  34,
       33,  33,  33,  33,  33,  33,  32,  32,  32,  32,  32,  32,  32,  31,  31,  31,  31,  31,  31,  31,
       31,  30,  30,  30,  30,  30,  30,  30,  30,  29,  29,  29,  29,  29,  29,  29,  29,  28,  28,  28,
       28,  28,  28,  28,  28,  28,  27,  27,  27,  27,  27,  27,  27,  27,  27,  26,  26,  26,  26,  26,
       26,  26,  26,  26,  26,  25,  25,  25,  25,  25,  25,  25,  25,  25,  24,  24,  24,  24,  24,  24,
       24,  24,  23,  23,  23,  23,  23,  23,  23,  23,  22,  22,  22,  22,  22,  22,  22,  22,  21,  21,
       21,  21,  21,  21,  21,  21,  20,  20,  20,  20,  20,  20,  20,  19,  19,  19,  19,  19,  19,  19,
       18,  18,  18,  18,  18,  18,  17,  17,  17,  17,  17,  17,  16,  16,  16,  16,  16,  16,  16,  15,
       15,  15,  15,  15,  15,  14,  14,  14,  14,  14,  14,  14,  13,  13,  13,  13,  13,  13,  12,  12,
       12,  12,  12,  12,  12,  12,  11,  11,  11,  11,  11,  11,  11,  11,  11,  10,  10,  10,  10,  10,
       10,  10,  10,  10,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9,   8,   8,   8,   8,   8,
        8,   8,   8,   8,   8,   8,   8,   8,   7,   7,   7,   7,   7,   7,   7,   7,   7,   7,   7,   7,
        7,   7,   7,   7,   7,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,
        6,   5,   5,   5,   5,   5,   4,   4,   4,   4,   3,   3,   3,   3,   2,   2,   2,   2,   1,   1,
        1,   1,   0};

  // Calculate the index for the table (7818 is the the azeotrope at 1013.25 hPa and the
  // starting point of the table) in �centiCelsius


  int16_t IndexABV = int16_t(T*100 + 0.5) - 7818;

  if (IndexABV < 0) return IndexABV; // Below azeotope
  if (IndexABV >= int16_t(sizeof ABV / sizeof *ABV)) return 0; // Above 100 �C
  if (IndexABV < 180) return float(pgm_read_byte(ABV + IndexABV) + 768) / 10;
  if (IndexABV < 460) return float(pgm_read_byte(ABV + IndexABV) + 512) / 10;
  if (IndexABV < 863) return float(pgm_read_byte(ABV + IndexABV) + 256) / 10;
  return float(pgm_read_byte(ABV + IndexABV)) / 10;

};

float TToABV::TtoVaporABV(float T) {

  const static uint8_t ABV[] PROGMEM = {
      /* by using PROGMEM the array stays in the program memory and is not copied to precious sram. */
      199, 196, 193, 192, 190, 188, 186, 185, 183, 178, 176, 176, 176, 175, 174, 173, 172, 171, 171, 170,
      169, 169, 168, 167, 166, 166, 165, 164, 164, 163, 162, 162, 162, 162, 161, 160, 159, 157, 157, 156,
      156, 155, 154, 154, 153, 152, 152, 151, 151, 150, 150, 150, 149, 148, 148, 147, 147, 147, 146, 146,
      145, 145, 144, 144, 143, 143, 142, 142, 142, 141, 141, 140, 140, 139, 139, 138, 138, 137, 137, 137,
      136, 136, 136, 135, 135, 134, 134, 133, 133, 132, 132, 132, 131, 131, 130, 130, 130, 129, 129, 129,
      128, 128, 128, 128, 128, 128, 127, 127, 126, 126, 126, 125, 125, 125, 124, 124, 124, 123, 123, 123,
      122, 122, 121, 121, 121, 120, 120, 120, 120, 120, 119, 119, 119, 119, 118, 118, 117, 117, 117, 116,
      116, 116, 115, 115, 115, 114, 114, 114, 114, 114, 113, 113, 113, 112, 112, 111, 111, 111, 110, 110,
      110, 109, 109, 109, 109, 108, 108, 108, 108, 108, 107, 107, 106, 106, 106, 105, 105, 105, 105, 104,
      104, 104, 104, 103, 103, 103, 102, 102, 102, 102, 102, 101, 101, 101, 101, 101, 101, 100, 100, 100,
       99,  99,  99,  99,  98,  98,  98,  98,  98,  97,  97,  97,  96,  96,  96,  96,  96,  96,  95,  95,
       95,  94,  94,  94,  94,  93,  93,  93,  93,  92,  92,  92,  92,  91,  91,  91,  91,  91,  91,  90,
       90,  90,  90,  90,  90,  89,  89,  89,  89,  89,  89,  89,  88,  88,  88,  88,  88,  87,  87,  87,
       87,  86,  86,  86,  86,  86,  85,  85,  85,  85,  85,  85,  85,  84,  84,  84,  84,  84,  84,  83,
       83,  82,  82,  82,  81,  81,  81,  81,  81,  80,  80,  80,  80,  80,  80,  79,  79,  79,  78,  78,
       78,  78,  77,  77,  77,  77,  77,  77,  77,  76,  76,  76,  76,  76,  76,  75,  75,  75,  74,  74,
       74,  74,  73,  73,  73,  73,  73,  73,  72,  72,  72,  72,  72,  72,  72,  71,  71,  71,  71,  71,
       71,  70,  70,  70,  70,  70,  70,  70,  69,  69,  69,  69,  69,  69,  68,  68,  68,  68,  68,  67,
       67,  67,  67,  66,  66,  66,  66,  65,  65,  65,  65,  65,  65,  65,  64,  64,  64,  64,  64,  63,
       63,  63,  63,  63,  63,  63,  62,  62,  62,  62,  62,  62,  61,  61,  61,  61,  61,  61,  61,  61,
       60,  60,  60,  60,  59,  59,  59,  59,  58,  58,  58,  58,  58,  58,  58,  58,  57,  57,  57,  57,
       57,  56,  56,  56,  55,  55,  55,  55,  55,  54,  54,  54,  54,  54,  54,  54,  54,  53,  53,  53,
       53,  53,  53,  52,  52,  52,  52,  51,  51,  51,  51,  50,  50,  50,  50,  50,  50,  50,  50,  50,
       50,  50,  49,  49,  49,  48,  48,  48,  48,  47,  47,  47,  47,  46,  46,  46,  46,  46,  46,  46,
       45,  45,  45,  45,  45,  44,  44,  44,  44,  43,  43,  43,  43,  43,  43,  42,  42,  42,  42,  42,
       42,  41,  41,  41,  41,  41,  41,  40,  40,  40,  40,  39,  39,  39,  39,  39,  39,  38,  38,  38,
       38,  38,  37,  37,  37,  37,  36,  36,  36,  36,  35,  35,  35,  35,  35,  34,  34,  34,  34,  34,
       34,  34,  34,  34,  33,  33,  33,  33,  33,  33,  32,  32,  32,  31,  31,  31,  31,  30,  30,  30,
       30,  30,  29,  29,  29,  29,  29,  29,  29,  29,  28,  28,  28,  28,  28,  27,  27,  27,  27,  27,
       27,  27,  26,  26,  26,  26,  26,  26,  26,  26,  25,  25,  25,  25,  25,  25,  24,  24,  24,  23,
       23,  23,  23,  22,  22,  22,  22,  21,  21,  21,  21,  21,  20,  20,  20,  20,  20,  19,  19,  19,
       19,  19,  19,  19,  19,  19,  18,  18,  18,  18,  18,  18,  17,  17,  17,  17,  16,  16,  16,  16,
       15,  15,  15,  15,  15,  14,  14,  14,  14,  14,  13,  13,  13,  13,  13,  12,  12,  12,  12,  12,
       11,  11,  11,  11,  10,  10,  10,  10,   9,   9,   9,   9,   9,   8,   8,   8,   8,   8,   7,   7,
        7,   6,   6,   6,   6,   5,   5,   5,   5,   4,   4,   4,   4,   4,   3,   3,   3,   3,   3,   2,
        2,   2,   2,   2,   1,   1,   1,   1,   0,   0,   0,   0, 255, 255, 255, 254, 254, 254, 254, 253,
      253, 253, 252, 252, 252, 252, 252, 251, 251, 251, 251, 251, 250, 250, 250, 249, 249, 249, 248, 248,
      248, 247, 247, 247, 247, 247, 246, 246, 246, 246, 246, 245, 245, 245, 244, 244, 244, 244, 243, 243,
      243, 242, 242, 242, 241, 241, 241, 240, 240, 240, 240, 239, 239, 239, 238, 238, 238, 237, 237, 237,
      236, 236, 236, 235, 235, 235, 234, 234, 234, 234, 233, 233, 233, 232, 232, 232, 232, 232, 231, 231,
      231, 231, 231, 231, 231, 230, 230, 230, 230, 230, 230, 230, 230, 229, 229, 229, 229, 229, 229, 229,
      229, 229, 229, 229, 229, 228, 228, 228, 228, 228, 228, 228, 228, 227, 227, 227, 227, 227, 227, 227,
      227, 227, 226, 226, 226, 226, 226, 226, 226, 226, 225, 225, 225, 225, 225, 225, 225, 225, 225, 224,
      224, 224, 224, 224, 224, 224, 224, 223, 223, 223, 223, 223, 223, 223, 223, 222, 222, 222, 222, 222,
      222, 222, 222, 222, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 220, 220, 220, 220, 220, 220,
      220, 220, 219, 219, 219, 219, 219, 219, 219, 218, 218, 218, 218, 218, 218, 217, 217, 217, 217, 217,
      216, 216, 216, 216, 215, 215, 215, 215, 214, 214, 214, 214, 213, 213, 213, 213, 212, 212, 212, 212,
      211, 211, 211, 211, 210, 210, 210, 209, 209, 209, 208, 208, 208, 208, 207, 207, 207, 206, 206, 206,
      206, 205, 205, 205, 205, 204, 204, 204, 204, 203, 203, 203, 203, 202, 202, 202, 202, 201, 201, 201,
      201, 200, 200, 200, 200, 199, 199, 199, 199, 198, 198, 198, 198, 197, 197, 197, 197, 197, 196, 196,
      196, 196, 195, 195, 195, 195, 195, 194, 194, 194, 194, 193, 193, 193, 193, 193, 192, 192, 192, 192,
      191, 191, 191, 191, 190, 190, 190, 190, 190, 189, 189, 189, 189, 188, 188, 188, 188, 187, 187, 187,
      187, 186, 186, 186, 186, 185, 185, 185, 185, 185, 184, 184, 184, 184, 183, 183, 183, 183, 182, 182,
      182, 182, 181, 181, 181, 181, 180, 180, 180, 180, 179, 179, 179, 178, 178, 178, 178, 177, 177, 177,
      177, 176, 176, 176, 176, 175, 175, 175, 175, 174, 174, 174, 174, 173, 173, 173, 173, 172, 172, 172,
      171, 171, 171, 171, 170, 170, 170, 169, 169, 169, 169, 168, 168, 168, 167, 167, 167, 167, 166, 166,
      166, 165, 165, 165, 165, 164, 164, 164, 163, 163, 163, 163, 162, 162, 162, 161, 161, 161, 161, 160,
      160, 160, 159, 159, 159, 159, 158, 158, 158, 157, 157, 157, 157, 156, 156, 156, 155, 155, 155, 154,
      154, 154, 154, 153, 153, 153, 152, 152, 152, 152, 151, 151, 151, 150, 150, 150, 149, 149, 149, 149,
      148, 148, 148, 147, 147, 147, 147, 146, 146, 146, 145, 145, 145, 145, 144, 144, 144, 144, 143, 143,
      143, 142, 142, 142, 142, 141, 141, 141, 141, 140, 140, 140, 139, 139, 139, 138, 138, 138, 137, 137,
      137, 137, 136, 136, 136, 135, 135, 135, 134, 134, 134, 133, 133, 133, 132, 132, 132, 131, 131, 131,
      130, 130, 130, 130, 129, 129, 129, 128, 128, 128, 128, 127, 127, 127, 126, 126, 126, 125, 125, 125,
      125, 124, 124, 124, 123, 123, 123, 122, 122, 122, 121, 121, 121, 120, 120, 120, 119, 119, 119, 118,
      118, 118, 117, 117, 117, 116, 116, 115, 115, 115, 114, 114, 114, 113, 113, 113, 112, 112, 112, 111,
      111, 111, 111, 110, 110, 110, 109, 109, 109, 108, 108, 108, 108, 107, 107, 107, 106, 106, 106, 105,
      105, 105, 105, 104, 104, 104, 104, 103, 103, 103, 103, 102, 102, 102, 102, 101, 101, 101, 101, 100,
      100, 100, 100,  99,  99,  99,  98,  98,  98,  98,  97,  97,  97,  97,  96,  96,  96,  95,  95,  95,
       95,  94,  94,  94,  93,  93,  93,  92,  92,  92,  91,  91,  91,  90,  90,  89,  89,  89,  88,  88,
       88,  87,  87,  86,  86,  86,  85,  85,  85,  84,  84,  83,  83,  83,  82,  82,  82,  81,  81,  81,
       80,  80,  79,  79,  79,  78,  78,  78,  77,  77,  77,  76,  76,  76,  75,  75,  75,  74,  74,  74,
       73,  73,  73,  72,  72,  72,  71,  71,  71,  70,  70,  70,  69,  69,  69,  68,  68,  68,  67,  67,
       67,  66,  66,  66,  65,  65,  65,  64,  64,  64,  63,  63,  62,  62,  62,  61,  61,  61,  60,  60,
       60,  59,  59,  59,  58,  58,  58,  57,  57,  56,  56,  56,  55,  55,  55,  54,  54,  53,  53,  53,
       52,  52,  51,  51,  51,  50,  50,  49,  49,  49,  48,  48,  47,  47,  46,  46,  46,  45,  45,  44,
       44,  43,  43,  42,  42,  41,  41,  40,  40,  39,  39,  38,  38,  37,  37,  36,  36,  35,  35,  34,
       34,  33,  33,  32,  32,  32,  31,  31,  30,  30,  29,  29,  28,  28,  28,  27,  27,  26,  26,  25,
       25,  24,  24,  24,  23,  23,  22,  22,  21,  21,  21,  20,  20,  19,  19,  18,  18,  17,  17,  17,
       16,  16,  15,  15,  14,  14,  13,  13,  12,  12,  12,  11,  11,  10,  10,   9,   9,   8,   8,   7,
        7,   6,   6,   6,   5,   5,   4,   4,   3,   3,   2,   2,   2,   1,   1,   0,   0,   0, 255, 255,
      255, 254, 254, 254, 253, 253, 252, 252, 252, 251, 251, 250, 250, 250, 249, 249, 248, 248, 248, 247,
      247, 246, 246, 245, 245, 244, 244, 244, 243, 243, 242, 242, 241, 241, 240, 240, 239, 239, 238, 238,
      237, 236, 235, 235, 234, 233, 233, 232, 231, 231, 230, 229, 228, 228, 227, 226, 226, 225, 224, 223,
      223, 222, 221, 220, 219, 219, 218, 217, 216, 216, 215, 214, 213, 213, 212, 211, 210, 210, 209, 208,
      208, 207, 206, 205, 205, 204, 203, 203, 202, 201, 200, 200, 199, 198, 198, 197, 196, 195, 195, 194,
      193, 193, 192, 191, 191, 190, 190, 189, 189, 188, 188, 187, 186, 186, 185, 185, 184, 184, 183, 183,
      182, 182, 181, 180, 180, 179, 179, 178, 178, 177, 176, 176, 175, 175, 174, 173, 173, 172, 172, 171,
      171, 170, 169, 169, 168, 168, 167, 166, 165, 164, 163, 162, 161, 160, 160, 159, 158, 157, 156, 155,
      154, 153, 153, 152, 151, 150, 149, 148, 147, 146, 146, 145, 144, 143, 142, 141, 140, 139, 138, 138,
      137, 136, 135, 134, 134, 133, 133, 132, 131, 131, 130, 130, 129, 129, 128, 128, 127, 126, 126, 125,
      125, 124, 124, 123, 123, 122, 122, 121, 121, 120, 119, 119, 118, 118, 117, 117, 116, 116, 115, 115,
      114, 114, 113, 113, 112, 112, 111, 111, 110, 110, 109, 109, 108, 108, 107, 107, 106, 106, 105, 105,
      104, 104, 103, 102, 102, 101, 100, 100,  99,  98,  98,  97,  96,  96,  95,  94,  93,  93,  92,  91,
       91,  90,  89,  88,  88,  87,  86,  85,  85,  84,  83,  82,  81,  81,  80,  79,  78,  77,  77,  76,
       75,  74,  73,  72,  72,  71,  70,  69,  68,  67,  66,  66,  65,  64,  63,  62,  61,  60,  59,  58,
       57,  56,  55,  54,  53,  52,  51,  50,  49,  48,  46,  45,  44,  43,  42,  41,  40,  39,  38,  37,
       36,  35,  34,  33,  32,  31,  30,  29,  28,  27,  26,  25,  24,  23,  22,  22,  21,  20,  19,  18,
       18,  17,  16,  15,  15,  14,  13,  12,  11,  11,  10,   9,   8,   7,   7,   6,   5,   4,   3,   3,
        2,   1,   0, 255, 255, 254, 253, 252, 251, 251, 250, 249, 248, 247, 247, 246, 245, 244, 243, 242,
      242, 241, 240, 239, 238, 238, 237, 236, 235, 234, 233, 232, 231, 230, 228, 227, 226, 225, 224, 223,
      222, 221, 220, 219, 217, 216, 215, 214, 213, 212, 211, 209, 208, 207, 206, 205, 204, 202, 201, 200,
      199, 198, 197, 195, 194, 193, 192, 190, 189, 188, 187, 186, 184, 183, 182, 181, 179, 178, 177, 175,
      174, 173, 172, 170, 169, 168, 166, 165, 164, 163, 161, 160, 159, 158, 156, 155, 154, 153, 151, 150,
      149, 148, 146, 145, 144, 143, 141, 140, 139, 138, 137, 135, 134, 133, 132, 131, 129, 128, 127, 126,
      125, 124, 123, 122, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105,
      104, 103, 102, 101, 100, 100,  99,  98,  97,  96,  95,  94,  93,  92,  91,  91,  90,  89,  88,  87,
       86,  86,  85,  84,  83,  82,  81,  81,  80,  79,  78,  78,  77,  76,  75,  75,  74,  73,  73,  72,
       71,  70,  70,  69,  68,  68,  67,  66,  66,  65,  64,  64,  63,  63,  62,  61,  61,  60,  60,  59,
       59,  56,  53,  50,  47,  43,  40,  38,  36,  33,  30,  27,  25,  22,  20,  18,  16,  13,  10,   8,
        6,   3,   0};

  // Calculate the index for the table (7818 is the the azeotrope at 1013.25 hPa and the
  // starting point of the table) in �centiCelsius

  int16_t IndexABV = int16_t(T * 100 + 0.5) - 7818;

  if (IndexABV < 0) return IndexABV; // Below azeotope
  if (IndexABV >= int16_t(sizeof ABV / sizeof *ABV)) return 0; // Above 100 �C
  if (IndexABV <  712) return float(pgm_read_byte(ABV + IndexABV) + 768) / 10;
  if (IndexABV < 1598) return float(pgm_read_byte(ABV + IndexABV) + 512) / 10;
  if (IndexABV < 1963) return float(pgm_read_byte(ABV + IndexABV) + 256) / 10;
  return float(pgm_read_byte(ABV + IndexABV)) / 10;

}

