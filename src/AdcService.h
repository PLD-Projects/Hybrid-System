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

    uint16_t ov_grid = 260;
    uint16_t uv_grid = 170;
    uint32_t timeout_grid = 5000;
    uint32_t _calc_time_grid = 0;
    uint32_t _calc_time_grid_fail = 0;
    uint32_t _calc_time_grid_ok = 0;
    bool status_grid = false;
    bool checking_grid = false;
    
    uint16_t ov_inv = 260;
    uint16_t uv_inv = 170;
    uint32_t timeout_inv = 5000;
    uint32_t _calc_time_inv = 0;
    bool status_inv = false;
    bool checking_inv = false;

    bool _inv_trans_cmpl = false;
    bool _grid_trans_cmpl = true;

    AdcService();
    // void calibrate();
    void initService();
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
