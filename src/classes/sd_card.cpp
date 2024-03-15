#include "sd_card.h"
#include <Arduino.h>

#include <SD.h>

#include "modules/myEnvSensors.h"
#include "modules/wifi_mqtt.h"
#include "modules/settings.h"

#include "mqtt.h"

File myFile;
MQTT mqtt;

Sd_card::Sd_card()
:_inited(false)
,_attached(false){
    init();
}

Sd_card::Sd_card(String file_name)
:_inited(false)
,_attached(false){
    init(file_name);
}

Sd_card::Sd_card(byte pin)
:_inited(false)
,_attached(false){
    attach(pin);
    init(pin);
}

Sd_card::Sd_card(byte pin, String file_name)
:_inited(false)
,_attached(false){
    attach(pin);
    init(pin, file_name);
}

Sd_card::~Sd_card(){}

void Sd_card::init(){
    init(5, "/data.csv");
}

void Sd_card::init(byte pin){
    init(pin, "/data.csv");
}

void Sd_card::init(String file_name){
    init(5, file_name);
}

void Sd_card::init(byte pin, String file_name){
    _pin = pin;
    _file_name = file_name;
    while (!SD.begin(_pin)) {
        DPRINTLN("Card failed, or not present");
        // Если что-то пошло не так, завершаем работу:*/
        delay(100);
    }
    DPRINTLN("card initialized.");
    myFile = SD.open(_file_name, FILE_APPEND);
    DPRINTLN("file was opened");
    myFile.close();
    _inited = true;
}

void Sd_card::attach(byte pin){
    _pin = pin;
    pinMode(_pin, OUTPUT);
    _attached = true;
}

void Sd_card::detach(){
    _attached = false;
}

void Sd_card::set_file_name(String file_name){
    _file_name = file_name;
}

bool Sd_card::isInited(){
    return _inited;
}

bool Sd_card::isAttached(){
    return _attached;
}

void Sd_card::saveDataFrame(envSensorData df){
    /*now = millis();
    sec_to_min();
    sec_to_hour();
    sec_to_day();*/
    if (isInited() and isAttached()){
        myFile = SD.open(_file_name, FILE_APPEND);
        myFile.println(/*(String)hour + ":" + mini + ":" + sec + ";" + */dataframe_csvData_toString(df));
        myFile.close();
        DPRINTLN("data was received");
        log("data was received");
    }
    else {
        DPRINTLN(F("file doesn't exist on SD Card."));
        log("file doesn't exist on SD Card.");
    }
}

void Sd_card::sendDataFrame(){
    if (isInited() and isAttached()){
        myFile = SD.open(_file_name, FILE_READ);
        DPRINTLN("Start reading data from SD-card");
        String msg;
        while (myFile.available()) {
            char data = myFile.read(); // read characters one by one from Micro SD Card
            // print the character to Serial Monitor
            if (data == '\n') {
                mqtt_send_sensorData(msg);
                msg = "";
            }
            else {
                msg += data;
            }
        }
        DPRINTLN(msg);
        mqtt.send_sensorData(msg);
        myFile.close();
    } 
    else {
        DPRINTLN(F("SD Card: Issue encountered while attempting to open the file"));
        log("SD Card: Issue encountered while attempting to open the file");
    }
}