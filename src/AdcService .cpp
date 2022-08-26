#include "AdcService.h"

static void _core_task(void *parameter)
{
    uint32_t _counter_timer = 0;
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
        while (micros() - t_start < period) 
        {
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
        l_pThis->_zero_grid = (l_pThis->_zero_grid+(((grid_max_val-grid_min_val)/2)+grid_min_val))/2;
        l_pThis->_zero_inv = (l_pThis->_zero_inv+(((inv_max_val-inv_min_val)/2)+inv_min_val))/2;

        l_pThis->read_grid = (sqrt(grid_Vsum / measurements_count))*l_pThis->sentivity_grid; //((Vrms / ADC_SCALE) * VREF)
        l_pThis->read_inv = (sqrt(inv_Vsum / measurements_count))*l_pThis->sentivity_inv; //((Vrms / ADC_SCALE) * VREF)
        l_pThis->read_bat = (bat_Vsum / measurements_count)*l_pThis->sentivity_bat; //((Vrms / ADC_SCALE) * VREF)

        if(l_pThis->read_grid < 30)l_pThis->read_grid = 0;
        if(l_pThis->read_inv < 30)l_pThis->read_inv = 0;

        if(l_pThis->read_grid > l_pThis->ov_grid || l_pThis->read_grid < l_pThis->uv_grid)
        {
            if (l_pThis->status_grid)
            {
                // Serial.println("Grid failed");
                l_pThis->status_grid = false;
                l_pThis->checking_grid = false;
                digitalWrite(P_ATS_RLY,1);
                digitalWrite(SG_ATS_RLY,1);
                digitalWrite(GRID_LED,0);
                l_pThis->_calc_time_grid = millis();
                l_pThis->_calc_time_grid_fail = millis();
                l_pThis->_grid_trans_cmpl = false;
            }

            else
            {
                l_pThis->_calc_time_grid = millis();
                if (!(l_pThis->_inv_trans_cmpl))
                {
                    if ((millis()-l_pThis->_calc_time_grid_fail > 5000) && !(digitalRead(INV_RLY)))digitalWrite(INV_RLY,1);
                    if ((millis()-l_pThis->_calc_time_grid_fail > 7000) && (digitalRead(INV_RLY)))
                    {
                        digitalWrite(SI_ATS_RLY,1);
                        l_pThis->_inv_trans_cmpl = true;
                        l_pThis->_grid_trans_cmpl = false;
                    }
                } 
            }
                        
        }

        if(l_pThis->read_grid <= l_pThis->ov_grid && l_pThis->read_grid >= l_pThis->uv_grid)
        {
            if (!(l_pThis->status_grid))
            {
                // Serial.println("Grid checking");
                l_pThis->checking_grid = true;
            }
            else
            {
                if (!(l_pThis->_grid_trans_cmpl))
                {
                    if((millis()-l_pThis->_calc_time_grid_ok > 2000) && (digitalRead(INV_RLY)))digitalWrite(INV_RLY,0);
                    if (millis()-l_pThis->_calc_time_grid_ok > 4000)
                    {
                        if(digitalRead(SG_ATS_RLY))digitalWrite(SG_ATS_RLY,0);
                        if(digitalRead(SI_ATS_RLY))digitalWrite(SI_ATS_RLY,0);
                        l_pThis->_inv_trans_cmpl = false;
                        l_pThis->_grid_trans_cmpl = true;
                    }
                }
            }
            
            
        }

        if((millis()-l_pThis->_calc_time_grid > l_pThis->timeout_grid) && (l_pThis->checking_grid))
        {
            // Serial.println("Grid OK");
            l_pThis->status_grid = true;
            l_pThis->checking_grid = false;
            digitalWrite(GRID_LED,1);
            digitalWrite(P_ATS_RLY,0);
            l_pThis->_calc_time_grid_ok = millis();
        }




        if(l_pThis->read_inv > l_pThis->ov_inv || l_pThis->read_inv < l_pThis->uv_inv)
        {
            // Serial.println("inv failed");
            l_pThis->status_inv = false;
            l_pThis->checking_inv = false;
            digitalWrite(INV_LED,0);
            l_pThis->_calc_time_inv = millis();
        }

        if((l_pThis->read_inv <= l_pThis->ov_inv && l_pThis->read_inv >= l_pThis->uv_inv) && !(l_pThis->status_inv) )
        {
            // Serial.println("Grid checking");
            l_pThis->checking_inv = true;
        }

        if((millis()-l_pThis->_calc_time_inv > l_pThis->timeout_inv) && (l_pThis->checking_inv))
        {
            // Serial.println("Grid OK");
            l_pThis->status_inv = true;
            l_pThis->checking_inv = false;
            digitalWrite(INV_LED,1);
        }
        




        if(millis()-_counter_timer > 500)
        {
            _counter_timer = millis();
            if(l_pThis->checking_grid)digitalWrite(GRID_LED,!digitalRead(GRID_LED));
            if(l_pThis->checking_inv)digitalWrite(INV_LED,!digitalRead(INV_LED));
        }
    }
    
}

AdcService::AdcService()
{

}

void AdcService::initService()
{
    pinMode(GRID_LED,OUTPUT);
    pinMode(INV_LED,OUTPUT);
    pinMode(CHG_RLY,OUTPUT);
    pinMode(P_ATS_RLY,OUTPUT);
    pinMode(SG_ATS_RLY,OUTPUT);
    pinMode(SI_ATS_RLY ,OUTPUT);
    pinMode(INV_RLY,OUTPUT);

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

void AdcService::startService()
{
    xTaskCreatePinnedToCore(
      _core_task, /* Function to implement the task */
      "ADC_Task", /* Name of the task */
      10000,  /* Stack size in words */
      this,  /* Task input parameter */
      0,  /* Priority of the task */
      &ADC_Task,  /* Task handle. */
      0); /* Core where the task should run */
}

void AdcService::stopService()
{
    vTaskDelete(ADC_Task);
}

