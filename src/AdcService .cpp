#include "AdcService.h"

static void _core_task(void *parameter){

    while (1)
    {
        AdcService *l_pThis = (AdcService *) parameter; 
        uint32_t period = 1000000 / l_pThis->frequency;

        uint16_t grid_acc = 0;
        uint16_t grid_max_val = 0;
        uint16_t grid_min_val = 5000;
        uint32_t grid_Vsum = 0;
        int32_t grid_Vnow = 0;

        uint16_t inv_acc = 0;
        uint16_t inv_max_val = 0;
        uint16_t inv_min_val = 5000;
        uint32_t inv_Vsum = 0;
        int32_t inv_Vnow = 0;

        uint16_t bat_acc = 0;
        uint32_t bat_Vsum = 0;

        uint32_t measurements_count = 0;

        uint32_t t_start = micros();
        while (micros() - t_start < period) {
            grid_acc = analogRead(GRID_PIN);
            grid_max_val = max(grid_acc,grid_max_val);
            grid_min_val = min(grid_acc,grid_min_val);
            grid_Vnow = grid_acc - l_pThis->_zero_grid;
            grid_Vsum += grid_Vnow*grid_Vnow;

            inv_acc = analogRead(INV_PIN);
            // inv_acc = adc1_get_raw((adc1_channel_t)ADC1_CHANNEL_A3);
            inv_max_val = max(inv_acc,inv_max_val);
            inv_min_val = min(inv_acc,inv_min_val);
            inv_Vnow = inv_acc - l_pThis->_zero_inv;
            inv_Vsum += inv_Vnow*inv_Vnow;

            bat_acc = analogRead(BAT_PIN);
            bat_Vsum += bat_acc;
            
            measurements_count++;
        }
        l_pThis->_zero_grid = ((grid_max_val-grid_min_val)/2)+grid_min_val;
        l_pThis->_zero_inv = ((inv_max_val-inv_min_val)/2)+inv_min_val;

        l_pThis->read_grid = (sqrt(grid_Vsum / measurements_count))*l_pThis->sentivity_grid; //((Vrms / ADC_SCALE) * VREF)
        l_pThis->read_inv = (sqrt(inv_Vsum / measurements_count))*l_pThis->sentivity_inv; //((Vrms / ADC_SCALE) * VREF)
        l_pThis->read_bat = (bat_Vsum / measurements_count)*l_pThis->sentivity_bat; //((Vrms / ADC_SCALE) * VREF)

    }
    
}

AdcService::AdcService(){

}

void AdcService::calibrate(){
    uint16_t grid_acc = 0;
	uint16_t grid_max_val = 0;
	uint16_t grid_min_val = 5000;
    uint16_t inv_acc = 0;
	uint16_t inv_max_val = 0;
	uint16_t inv_min_val = 5000;

	for (int i = 0; i < 1000; i++) {
		grid_acc = analogRead(GRID_PIN);
		grid_max_val = max(grid_acc,grid_max_val);
		grid_min_val = min(grid_acc,grid_min_val);
        inv_acc = analogRead(INV_PIN);
		inv_max_val = max(inv_acc,inv_max_val);
		inv_min_val = min(inv_acc,inv_min_val);
	}
	_zero_grid = ((grid_max_val-grid_min_val)/2)+grid_min_val;
    _zero_inv = ((inv_max_val-inv_min_val)/2)+inv_min_val;
}

void AdcService::startService(){
    xTaskCreatePinnedToCore(
      _core_task, /* Function to implement the task */
      "ADC_Task", /* Name of the task */
      10000,  /* Stack size in words */
      this,  /* Task input parameter */
      0,  /* Priority of the task */
      &ADC_Task,  /* Task handle. */
      0); /* Core where the task should run */
}

void AdcService::stopService(){
    vTaskDelete(ADC_Task);
}

