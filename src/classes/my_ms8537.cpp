#include "my_ms5837.h"
#include <Arduino.h>
#include "modules/settings.h"

#include "MS5837.h"

My_ms5837::My_ms5837()
:_inited(false){
    init();
}

My_ms5837::My_ms5837(String model)
:_inited(false){
    init(model);
}

My_ms5837::My_ms5837(int xfact)
:_inited(false){
    init(xfact);
}

My_ms5837::My_ms5837(String model, int xfact)
:_inited(false){
    init(model, xfact);
}

My_ms5837::~My_ms5837(){}

void My_ms5837::init(){
    init("MS5837_30BA", 997);
}

void My_ms5837::init(String model){
    init(model, 997);
}

void My_ms5837::init(int xfact){
    init("MS5837_30BA", xfact);
}

void My_ms5837::init(String model, int xfact){
    MS5837 ms5837_sensor;
    while (!ms5837_sensor.init()) {
    DPRINTLN("Init failed!");
    DPRINTLN("Are SDA/SCL connected correctly?");
    DPRINTLN("Blue Robotics Bar30: White=SDA, Green=SCL");
    DPRINTLN("\n\n\n");
    log("Init failed!");
    log("Are SDA/SCL connected correctly?");
    log("Blue Robotics Bar30: White=SDA, Green=SCL");
    delay(MS5837_ERR_INIT_TIMEOUT);
    #ifdef ___LAUNCH_WITHOUT_MS5837___
      break;
    #endif  
    }
    _model = model;
    _xfact = xfact;
    _average_number = 1;
    _inited = true;
}

void My_ms5837::set_model(String model){
    _model = model;
}

void My_ms5837::set_xFact(int xfact){
    _xfact = xfact;
}

void My_ms5837::set_average_number(int average_number){
    _average_number = average_number;
}

bool My_ms5837::isInited(){
    return _inited;
}

void My_ms5837::update(){
    MS5837 ms5837_sensor;
	if (isInited())
	{
		ms5837_sensor.setFluidDensity(_xfact);
        String models = "MS5837::" + _model;
        //ms5837_sensor.setModel(uint8_t(models));  не понимаю как написать, нужна ли модель?
        ms5837_sensor.read();
	}
}

float My_ms5837::get_pressure(){
    MS5837 ms5837_sensor;
    update();
    return ms5837_sensor.pressure();
}

float My_ms5837::get_temperature(){
    MS5837 ms5837_sensor;
    update();
    return ms5837_sensor.temperature();
}

float My_ms5837::get_depth(){
    MS5837 ms5837_sensor;
    update();
    return ms5837_sensor.depth();
}

float My_ms5837::get_altitude(){
    MS5837 ms5837_sensor;
    update();
    return ms5837_sensor.altitude();
}

float My_ms5837::average_pressure(){
    if (isInited()){
        float pressure = get_pressure();
        static float prevResult = 0;
        static float sum_pressure = 0;
        sum_pressure += pressure;
        counter_pressure++;
        if (counter_pressure == _average_number) {
            prevResult = sum_pressure / _average_number;
            sum_pressure = 0;
            counter_pressure = 0;
        }
        return prevResult;
    }
}

float My_ms5837::average_temp(){
    if (isInited()){
        float temp = get_temperature();
        static float prevResult = 0;
        static float sum_temp = 0;
        sum_temp += temp;
        counter_temp++;
        if (counter_temp == _average_number) {
            prevResult = sum_temp / _average_number;
            sum_temp = 0;
            counter_temp = 0;
        }
        return prevResult;
    }
}

float My_ms5837::average_depth(){
    if (isInited()){
        float depth = get_depth();
        static float prevResult = 0;
        static float sum_depth = 0;
        sum_depth += depth;
        counter_depth++;
        if (counter_depth == _average_number) {
            prevResult = sum_depth / _average_number;
            sum_depth = 0;
            counter_depth = 0;
        }
        return prevResult;
    }
}

float My_ms5837::average_altitude(){
    if (isInited()){
        float altitude = get_altitude();
        static float prevResult = 0;
        static float sum_altitude = 0;
        sum_altitude += altitude;
        counter_altitude++;
        if (counter_altitude == _average_number) {
            prevResult = sum_altitude / _average_number;
            sum_altitude = 0;
            counter_altitude = 0;
        }
        return prevResult;
    }
}

float My_ms5837::average(){
    if (isInited()){
    float ave_pressure = average_pressure();
    float ave_temp = average_temp();
    float ave_depth = average_depth();
    float ave_altitude = average_altitude();
    return ave_pressure, ave_temp, ave_depth, ave_altitude;
    }
}