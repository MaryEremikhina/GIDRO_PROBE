#include <Arduino.h>

#include "mqtt_handlers.h"

#include "settings.h"
#include "buoyancy.h"

bool startStatus = 0;

uint32_t divingTime = 0;
uint32_t swimmingTime = 0;
uint32_t floattingTime = 0;

float targetDepth = 0;
float floattingDepth = 0;

bool get_startStatus(){
    return startStatus;
}

void set_startStatus(bool new_startStatus){
    startStatus = new_startStatus;
}

uint32_t get_DivingTime(){
    return divingTime;
}

void set_DivingTime(uint32_t new_divingTime){
    divingTime = new_divingTime;
}

uint32_t get_SwimmingTime(){
    return swimmingTime;
}

void set_SwimmingTime(uint32_t new_swimmingTime){
    swimmingTime = new_swimmingTime;
}

uint32_t get_FloattingTime(){
    return floattingTime;
}

void set_FloattingTime(uint32_t new_floattingTime){
    floattingTime = new_floattingTime;
}

float get_targetDepth(){
    return targetDepth;
}

void set_targetDepth(float new_targetDepth){
    targetDepth = new_targetDepth;
}

float get_floattingDepth(){
    return floattingDepth;
}

void set_floattingDepth(float new_floattingDepth){
    floattingDepth = new_floattingDepth;
}

void mqtt_start_handler(String msg){
    DPRINTLN("Start msg was received!!!");
    log("Start msg was received!!!");
    set_startStatus(true);
}




void mqtt_reboot_handler(String msg){
    ESP.restart();
}

void mqtt_resetMqtt_handler(String msg){
    DPRINTLN("mqtt resetMQTT handler");
    log("mqtt resetMQTT handler");
}

void mqtt_resetWifi_handler(String msg){
    DPRINTLN("mqtt_resetWifi_handler");
    log("mqtt_resetWifi_handler");
}

void mqtt_setDivingTime_handler(String msg){
    DPRINTLN("mqtt_setDivingTime_handler");
    log("mqtt_setDivingTime_handler");
    set_DivingTime(msg.toInt());
}

void mqtt_setSwimmingTime_handler(String msg){
    DPRINTLN("mqtt_setSwimmingTime_handler");
    log("mqtt_setSwimmingTime_handler");
    set_SwimmingTime(msg.toInt());
}

void mqtt_setFloattingTime_handler(String msg){
    DPRINTLN("mqtt_setFloattingTime_handler");
    log("mqtt_setFloattingTime_handler");
    set_FloattingTime(msg.toInt());
}

void mqtt_setTargetDepth_handler(String msg){
    DPRINTLN("mqtt_setTargetDepth_handler");
    log("mqtt_setTargetDepth_handler");
    set_targetDepth(msg.toFloat());
}

void mqtt_setServo_handler(String msg){
    DPRINTLN("Received Servo command:");
    log("Received Servo command:");
    Serial.println(msg);
    if (msg == "Up"){
        DPRINTLN("Floating Up!");
        log("Floating Up!");
        buoyancyServo_float();
    }
    else if (msg == "Down"){
        DPRINTLN("Diving Down!");
        log("Diving Down!");
        buoyancyServo_dive();
    }
    else{
        DPRINTLN("Wrong servo-command");
        log("Wrong servo-command");
    }
}