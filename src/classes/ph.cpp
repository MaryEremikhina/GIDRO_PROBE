#include "ph.h"
#include <Arduino.h>

PH::PH()
:_inited(false)
,_attached(false){
	init();
}

PH::PH(float vcc, int adc_max, float xfact)
:_attached(false){
	init(vcc, adc_max, xfact);
}

PH::PH(byte pin)
:_inited(false){
	attach(pin);
	init();
}

PH::PH(byte pin, float vcc, int adc_max, float xfact){
	attach(pin);
	init(vcc, adc_max, xfact);
}

PH::~PH(){} 

void PH::init(){
	init(3.3, 4096, 3.5);
}

void PH::init(float vcc, int adc_max, float xfact){
	_vcc = vcc;
	_adc_max = adc_max;
	_xfact = xfact;
	_average_number = 0;
	_inited = true;
}

void PH::attach(byte pin){
	_pin = pin;
	_attached = true;
}

void PH::detach(){
	_attached = false;
}

void PH::set_vcc(float vcc){
	_vcc = vcc;
}

void PH::set_adcMax(int adc_max){
	_adc_max = adc_max;
}

void PH::set_xFact(float xfact){
	_xfact = xfact;
}

void PH::set_average_number(int average_number){
	_average_number = average_number;
}

bool PH::isInited(){
	return _inited;
}

bool PH::isAttached(){
	return _attached;
}

int PH::get_rawData(){
	return isAttached() ? analogRead(_pin) : 0;
}

float PH::get_ph(){
	float phValue = 0;
	if (isInited() and isAttached()){
		int raw = get_rawData();
		phValue = (float)raw * _vcc / _adc_max;
	}
	return _xfact * phValue;
}

float PH::average(){
	if (isInited() and isAttached()){
		float ph = get_ph();
		static float prevResult = 0;
  		static float sum_PH = 0;
  		sum_PH += ph;
		if (counter == _average_number) {
			prevResult = sum_PH / _average_number;
			sum_PH = 0;
			counter = 0;
		}
		return prevResult;
	}
}