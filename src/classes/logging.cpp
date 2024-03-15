#include "logging.h"
#include <Arduino.h>

#include <SD.h>

#include "modules/myEnvSensors.h"
#include "modules/wifi_mqtt.h"
#include "modules/settings.h"

File myF;

Logging::Logging()
:_inited(false)
,_attached(false){
    init();
}

Logging::Logging(byte pin)
:_inited(false)
,_attached(false){
    init(pin);
    attach(pin);
}

Logging::Logging(String file_name)
:_inited(false)
,_attached(false){
    init(file_name);
}

Logging::Logging(byte pin, String file_name)
:_inited(false)
,_attached(false){
    init(pin, file_name);
    attach(pin);
}

Logging::~Logging(){}

void Logging::init(){
    init(5, "/log.txt");
}

void Logging::init(byte pin){
    init(pin, "/log.txt");
}

void Logging::init(String file_name){
    init(5, file_name);
}

void Logging::init(byte pin, String file_name){
    _pin = pin;
    _file_name = file_name;
    while (!SD.begin(_pin)) {
        DPRINTLN("Card failed, or not present");
        // Если что-то пошло не так, завершаем работу:*/
        delay(100);
    }
    DPRINTLN("card initialized.");
    myF = SD.open(_file_name, FILE_APPEND);
    DPRINTLN("file was opened");
    myF.close();
    _inited = true;
}

void Logging::attach(byte pin){
    _pin = pin;
    pinMode(_pin, OUTPUT);
    _attached = true;
}

void Logging::detach(){
    _attached = false;
}

bool Logging::isInited(){
    return _inited;
}

bool Logging::isAttached(){
    return _attached;
}

void Logging::set_file_name(String file_name){
    _file_name = file_name;
}

void Logging::log(String text){
    /*lnow = millis();
    lsec_to_min();
    lsec_to_day();
    lsec_to_day();*/
    if (isInited() and isAttached()){
        myF = SD.open(_file_name, FILE_APPEND);
        myF.println(/*(String)lhour + ":" + lmini + ":" + lsec + " :) " + */text);
        myF.close();
        DPRINTLN("data was received");

    }
    else {
        DPRINTLN(F("file doesn't exist on SD Card."));
    }
}