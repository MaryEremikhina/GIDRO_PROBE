#include "tds.h"
#include <Arduino.h>

const float   Kt     = 0.02f;                     // Температурный коэффициент           (зависит от состава жидкости).
const float   Kp     = 0.5f;                      // Коэффициент пересчёта               (зависит от состава жидкости).
const float   Kf     = 0.85f;                     // Коэффициент передачи ФВЧ+ФНЧ модуля (зависит от частоты переменного тока используемого для проведения измерений).
const float   T      = 25.0f;                     // Опорная температура в °C.
const float   t      = 25.0f;                     // Температура исследуемой жидкости в °C.
const float   Ka     = 1000.0f;                   // Множитель степенной функции         (определяется калибровкой модуля). Можно получить функцией getKa().
const float   Kb     = -5.0f;                     // Степень степенной функции           (определяется калибровкой модуля). Можно получить функцией getKb().

TDS::TDS()
:_inited(false)
,_attached(false){
    init();
}

TDS::TDS(float vcc, int adc_max)
:_inited(false){
    init(vcc, adc_max);
}

TDS::TDS(byte pin)
:_attached(false){
    attach(pin);
    init();
}

TDS::TDS(byte pin, float vcc, int adc_max){
    attach(pin);
    init(vcc, adc_max);
}

TDS::~TDS(){}

void TDS::init(){
    init(3.3, 4096);
}

void TDS::init(float vcc, int adc_max){
    _vcc = vcc;
    _adc_max = adc_max;
    _average_number = 0;
    _inited = true;
}

void TDS::attach(byte pin){
    _pin = pin;
    _attached = true;
}

void TDS::detach(){
    _attached = false;
}

void TDS::set_vcc(float vcc){
    _vcc = vcc;
}

void TDS::set_adcMax(int adc_max){
    _adc_max = adc_max;
}

void TDS::set_average_number(int average_number){
    _average_number = average_number;
}

bool TDS::isInited(){
    return _inited;
}

bool TDS::isAttached(){
    return _attached;
}

int TDS::get_rawData(){
    return isAttached() ? analogRead(_pin) : 0;
}

float TDS::get_conductivity(){
	if (isInited() and isAttached()){
		int raw = get_rawData();
        return float(raw) * _vcc / (_adc_max - 1);
    }
}

float TDS::get_normConductivity(){
	if (isInited() and isAttached()){
		int raw = get_conductivity();
        return Ka * pow((_vcc - Kf * raw) / 2, Kb) / 1000;
    }
}

float TDS::get_EC(){
	if (isInited() and isAttached()){
		int raw = get_normConductivity();
        return raw / (1 + Kt * (t - T));
    }
}

float TDS::get_TDS(){
	if (isInited() and isAttached()){
		int raw = get_EC();
        return raw * Kp;
    }
}

float TDS::average_normConductivity(){
    if (isInited() and isAttached()){
        float normConductivity = get_normConductivity();
        static float prevResult = 0;
        static float sum_NormConductivity = 0;
        sum_NormConductivity += normConductivity;
        counter_normConductivity++;
        if (counter_normConductivity == _average_number) {
            prevResult = sum_NormConductivity / _average_number;
            sum_NormConductivity = 0;
            counter_normConductivity = 0;
        }
        return prevResult;
    }
}

float TDS::average_EC(){
    if (isInited() and isAttached()){
        float EC = get_EC();
        static float prevResult = 0;
        static float sum_EC = 0;
        sum_EC += EC;
        counter_EC++;
        if (counter_EC == _average_number) {
            prevResult = sum_EC / _average_number;
            sum_EC = 0;
            counter_EC = 0;
        }
        return prevResult;
    }
}

float TDS::average_TDS(){
    if (isInited() and isAttached()){
        float TDS = get_TDS();
        static float prevResult = 0;
        static float sum_TDS = 0;
        sum_TDS += TDS;
        counter_TDS++;
        if (counter_TDS == _average_number) {
            prevResult = sum_TDS / _average_number;
            sum_TDS = 0;
            counter_TDS = 0;
        }
        return prevResult;
    }
}

float TDS::average(){
    if (isInited() and isAttached()){
        float normConductivity = average_normConductivity();
        float EC = average_EC();
        float TDS = average_TDS();
        return normConductivity, EC, TDS;
    }
}