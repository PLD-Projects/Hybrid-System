#include "ZMPT101B.h"

ZMPT101B::ZMPT101B(uint8_t _pin) {
	pin = _pin;
	sensitivity = 1;
}

int ZMPT101B::calibrate() {
	uint16_t acc = 0;
	uint16_t max_val = 0;
	uint16_t min_val = ADC_SCALE-1;
	for (int i = 0; i < 1000; i++) {
		acc = analogRead(pin);
		max_val = max(acc,max_val);
		min_val = min(acc,min_val);
	}
	zero = ((max_val-min_val)/2)+min_val;
	return zero;
}

void ZMPT101B::setZeroPoint(int _zero) {
	zero = _zero;
}

void ZMPT101B::setSensitivity(float sens) {
	sensitivity = sens;
}

float ZMPT101B::getVoltageDC() {
	int16_t acc = 0;
	for (int i = 0; i < 10; i++) {
		acc += analogRead(pin) - zero;
	}
	float V = (float)acc / 10.0 / ADC_SCALE * VREF / sensitivity;
	return V;
}

float ZMPT101B::getVoltageAC(uint16_t frequency) {
	uint32_t period = 1000000 / frequency;
	uint32_t t_start = micros();

	uint32_t Vsum = 0, measurements_count = 0;
	int32_t Vnow;

	uint16_t acc = 0;
	uint16_t max_val = 0;
	uint16_t min_val = ADC_SCALE-1;

	while (micros() - t_start < period) {
		acc = analogRead(pin);
		max_val = max(acc,max_val);
		min_val = min(acc,min_val);
		Vnow = acc - zero;
		Vsum += Vnow*Vnow;
		measurements_count++;
	}
	zero = ((max_val-min_val)/2)+min_val;

	float Vrms = sqrt(Vsum / measurements_count);
	Vrms =  Vrms * sensitivity; //((Vrms / ADC_SCALE) * VREF)
	return Vrms;
}
