#ifndef ADCSERVICE_h
#define ADCSERVICE_h

#include <Arduino.h>
#include "PinMapping.h"

class AdcService{
public:
    int _zero_grid = 0;
    int _zero_inv = 0;
    float read_grid = 0;
    float read_inv = 0;
    float read_bat = 0;
    float sentivity_grid = 0;
    float sentivity_inv = 0;
    float sentivity_bat = 0;
    uint16_t frequency = 50;

    AdcService();
    void calibrate();
    // void initService();
    void startService();
    void stopService();
    // void setGridSensitivity();
    // void setInvSensitivity();
    // void setBatSensitivity();
    // void setFrequency(uint16_t frequency);
    // float getGridVoltage();
    // float getInvVoltage();
    // float getBatVoltage();

private:
    TaskHandle_t ADC_Task;
    
    // static void _core_task(void *parameter);
};

#endif
