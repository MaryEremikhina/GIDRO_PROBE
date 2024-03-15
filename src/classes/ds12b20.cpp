#include "ds12b20.h"
#include <Arduino.h>

#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define DS12B20_SENSOR_ID 0

Temperature::Temperature()
:_inited(false)
,_attached(false){
    init();
}

Temperature::Temperature(byte pin)
:_attached(false){
    attach(pin);
    init();
}

Temperature::~Temperature(){}

void Temperature::init(){
    OneWire oneWire(_pin);
    DallasTemperature ds12b20_sensor(&oneWire);
    Wire.begin();
    ds12b20_sensor.begin();
    _average_number = 0;
    _inited = true;
}

void Temperature::attach(byte pin){
    _pin = pin;
    OneWire oneWire(_pin);
    DallasTemperature ds12b20_sensor(&oneWire);
    Wire.begin();
    ds12b20_sensor.begin();
    _attached = true;
}

void Temperature::detach(){
    _attached = false;
}

void Temperature::set_average_number(int average_number){
    	_average_number = average_number;
}

bool Temperature::isInited(){
    return _inited;
}

bool Temperature::isAttached(){
    return _attached;
}

float Temperature::get_temperature(){
    OneWire oneWire(_pin);
    DallasTemperature ds12b20_sensor(&oneWire);
    Wire.begin();
    ds12b20_sensor.begin();
	if (isInited() and isAttached())
	{
	    ds12b20_sensor.requestTemperatures();
	}
	return ds12b20_sensor.getTempCByIndex(DS12B20_SENSOR_ID);
}

float Temperature::average(){
    if (isInited() and isAttached()){
        float temp = get_temperature();
        static float prevResult = 0;
        static float sum_temp = 0;
        sum_temp += temp;
        counter++;
        if (counter == _average_number) {
            prevResult = sum_temp / _average_number;
            sum_temp = 0;
            counter = 0;
        }
        return prevResult;
    }
}