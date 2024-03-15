#include "turbidity.h"
#include <Arduino.h>

Turbidity::Turbidity()
:_inited(false)
,_attached(false){
    init();
}

Turbidity::Turbidity(float xfact)
:_inited(false){
    init(xfact);
}

Turbidity::Turbidity(byte pin)
:_attached(false){
    attach(pin);
    init();
}

Turbidity::Turbidity(byte pin, float xfact){
    attach(pin);
    init(xfact);
}

Turbidity::~Turbidity(){}

void Turbidity::init(){
    init(0.001);
}

void Turbidity::init(float xfact){
    _xfact = xfact;
    _average_number = 0;
    _inited = true;
}

void Turbidity::attach(byte pin){
    _pin = pin;
    _attached = true;
}

void Turbidity::detach(){
    _attached = false;
}

void Turbidity::set_xFact(float xfact){
    _xfact = xfact;
}

void Turbidity::set_average_number(int average_number){
    _average_number = average_number;
}

bool Turbidity::isInited(){
    return _inited;
}

bool Turbidity::isAttached(){
    return _attached;
}

int Turbidity::get_rawData(){
	return isAttached() ? analogRead(_pin) : 0;
}

float Turbidity::get_turbidity(){
	if (isInited() and isAttached()){
		int raw = get_rawData();
	return _xfact * raw;
    }
}

float Turbidity::average(){
    if (isInited() and isAttached()){
        float turbidity = get_turbidity();
        static float prevResult = 0;
        static float sum_turbidity = 0;
        sum_turbidity += turbidity;
        counter++;
        if (counter == _average_number) {
            prevResult = sum_turbidity / _average_number;
            sum_turbidity = 0;
            counter = 0;
        }
        return prevResult;
    }
}