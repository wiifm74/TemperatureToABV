

#ifndef TEMPERATURE2ABV
#define TEMPERATURE2ABV

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

};

#endif