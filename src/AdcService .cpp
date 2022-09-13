#include "AdcService.h"

static void _core_task(void *parameter)
{
    AdcService *l_pThis = (AdcService *) parameter;
    l_pThis->core_task();
}

AdcService::AdcService()
{

}

void AdcService::initService()
{
    pinMode(GRID_LED,OUTPUT);
    pinMode(INV_LED,OUTPUT);
    pinMode(STS_LED,OUTPUT);
    // pinMode(CHG_RLY,OUTPUT);
    pinMode(P_ATS_RLY,OUTPUT);
    pinMode(SG_ATS_RLY,OUTPUT);
    pinMode(SI_ATS_RLY ,OUTPUT);
    pinMode(INV_RLY,OUTPUT);
    

    _adc_grid.attach(GRID_PIN);
    _adc_inv.attach(INV_PIN);
    _adc_bat.attach(BAT_PIN);

    _runstat_grid.setWindowSecs( windowLength );
    _runstat_inv.setWindowSecs( windowLength );
    _runstat_bat.setWindowSecs( windowLength );

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

void AdcService::core_task()
{
    uint32_t _counter_timer = 0;
    uint32_t filter_timer_grid = 0;
    uint16_t filter_cnt_grid = 0;
    uint32_t filter_timer_inv = 0;
    uint16_t filter_cnt_inv = 0;
    uint32_t grid_Vsum_avg = 0;
    uint32_t inv_Vsum_avg = 0;

    while (1)
    {
        uint32_t period = (5000000 / frequency);

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
            grid_acc = _adc_grid.readMiliVolts();
            grid_max_val = max(grid_acc,grid_max_val);
            grid_min_val = min(grid_acc,grid_min_val);
            grid_Vnow = grid_acc - _zero_grid;
            grid_Vsum += grid_Vnow*grid_Vnow;

            inv_acc = _adc_inv.readMiliVolts();
            inv_max_val = max(inv_acc,inv_max_val);
            inv_min_val = min(inv_acc,inv_min_val);
            inv_Vnow = inv_acc - _zero_inv;
            inv_Vsum += inv_Vnow*inv_Vnow;

            bat_acc = _adc_bat.readMiliVolts();
            bat_Vsum += bat_acc;
            
            measurements_count++;
        }
        _zero_grid = (_zero_grid+(((grid_max_val-grid_min_val)/2)+grid_min_val))/2;
        _zero_inv = (_zero_inv+(((inv_max_val-inv_min_val)/2)+inv_min_val))/2;

        read_grid = (sqrt(grid_Vsum / measurements_count))*sentivity_grid; //((Vrms / ADC_SCALE) * VREF)
        read_inv = (sqrt(inv_Vsum / measurements_count))*sentivity_inv; //((Vrms / ADC_SCALE) * VREF)
        read_bat = (bat_Vsum / measurements_count)*sentivity_bat; //((Vrms / ADC_SCALE) * VREF)

        // Serial.print(read_grid);
        // Serial.print("  ");
        // Serial.print(read_inv);
        // // Serial.print("  ");
        // // Serial.print(read_bat);
        // Serial.println();

        if(read_grid < 150)read_grid = 0;
        else
        {
            filter_cnt_grid++;
            grid_Vsum_avg += read_grid;
            if(millis()-filter_timer_grid > 1000)
            {
                filter_timer_grid = millis();
                read_grid = grid_Vsum_avg/filter_cnt_grid;
                filter_cnt_grid = 0;
                grid_Vsum_avg = 0;
            }

        }
        
        if(read_inv < 150)read_inv = 0;
        else
        {
            filter_cnt_inv++;
            inv_Vsum_avg += read_inv;
            if(millis()-filter_timer_inv > 1000)
            {
                filter_timer_inv = millis();
                read_inv = inv_Vsum_avg/filter_cnt_inv;
                filter_cnt_inv = 0;
                inv_Vsum_avg = 0;
            }

        }
        
        // Serial.print(read_grid);
        // Serial.print("  ");
        // Serial.print(read_inv);
        // // Serial.print("  ");
        // // Serial.print(read_bat);
        // Serial.println();

        if(read_grid > ov_grid || read_grid < uv_grid)
        {
            checking_grid = false;
            if (status_grid)
            {
                Serial.println("Grid failed");
                Serial.println(read_grid);
                status_grid = false;
                digitalWrite(P_ATS_RLY,1);
                digitalWrite(SG_ATS_RLY,1);
                digitalWrite(GRID_LED,0);
                _calc_time_grid = millis();
                _calc_time_grid_fail = millis();
                _grid_trans_cmpl = false;
            }

            else
            {
                _calc_time_grid = millis();
                if (!(_inv_trans_cmpl))
                {
                    if ((millis()-_calc_time_grid_fail > 5000) && !(digitalRead(INV_RLY)))digitalWrite(INV_RLY,1);
                    if ((millis()-_calc_time_grid_fail > 7000) && (digitalRead(INV_RLY)))
                    {
                        digitalWrite(SI_ATS_RLY,1);
                        _inv_trans_cmpl = true;
                        _grid_trans_cmpl = false;
                    }
                } 
            }
                        
        }

        if(read_grid <= ov_grid && read_grid >= uv_grid)
        {
            if (!(status_grid))
            {
                // Serial.println("Grid checking");
                checking_grid = true;
            }
            else
            {
                if (!(_grid_trans_cmpl))
                {
                    if((millis()-_calc_time_grid_ok > 2000) && (digitalRead(INV_RLY)))digitalWrite(INV_RLY,0);
                    if (millis()-_calc_time_grid_ok > 4000)
                    {
                        if(digitalRead(SG_ATS_RLY))digitalWrite(SG_ATS_RLY,0);
                        if(digitalRead(SI_ATS_RLY))digitalWrite(SI_ATS_RLY,0);
                        _inv_trans_cmpl = false;
                        _grid_trans_cmpl = true;
                    }
                }
            }
            
            
        }

        if((millis()-_calc_time_grid > timeout_grid) && (checking_grid))
        {
            // Serial.println("Grid OK");
            status_grid = true;
            checking_grid = false;
            digitalWrite(GRID_LED,1);
            digitalWrite(P_ATS_RLY,0);
            _calc_time_grid_ok = millis();
        }

        if(read_inv > ov_inv || read_inv < uv_inv)
        {
            // Serial.println("inv failed");
            status_inv = false;
            checking_inv = false;
            digitalWrite(INV_LED,0);
            _calc_time_inv = millis();
        }

        if((read_inv <= ov_inv && read_inv >= uv_inv) && !(status_inv) )
        {
            // Serial.println("Grid checking");
            checking_inv = true;
        }

        if((millis()-_calc_time_inv > timeout_inv) && (checking_inv))
        {
            // Serial.println("Grid OK");
            status_inv = true;
            checking_inv = false;
            digitalWrite(INV_LED,1);
        }

        if(millis()-_counter_timer > 500)
        {
            _counter_timer = millis();
            if(checking_grid)digitalWrite(GRID_LED,!digitalRead(GRID_LED));
            if(checking_inv)digitalWrite(INV_LED,!digitalRead(INV_LED));
            digitalWrite(STS_LED,!digitalRead(STS_LED));
        }
    }
}