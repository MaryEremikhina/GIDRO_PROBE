#include "mqtt.h"
#include <Arduino.h>

#include "modules/settings.h"
#include <WiFi.h>
#include <PubSubClient.h>

#include "WIFI.h"

#define MQTT_IS_OFF 0x0
#define MQTT_IS_ON 0x1

void callback(char* topic, byte* message, unsigned int length);

WiFiClient espClient;
PubSubClient client(MQTT_HOST,
                    MQTT_PORT,
                    callback,
                    espClient);

WIFI wifi;

MQTT::MQTT(){
    _host = MQTT_HOST;
    _port = MQTT_PORT;
    _mode = MQTT_IS_ON;
    connect();
}

MQTT::MQTT(bool mode){
    _host = MQTT_HOST;
    _port = MQTT_PORT;
    _mode = mode;
    connect();
}

MQTT::MQTT(char* host, int port){
    _host = host;
    _port = port;
    _mode = MQTT_IS_ON;
    connect();
}

MQTT::MQTT(char* host, int port, bool mode){
    _host = host;
    _port = port;
    _mode = mode;
    connect();
}

MQTT::~MQTT(){}

void MQTT::set_host(char* host){
    _host = host;
}

void MQTT::set_port(int port){
    _port = port;
}

void MQTT::set_mode(bool mode){
    _mode = mode;
}

bool MQTT::get_mode(){
    return _mode;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////// НАСКОЛЬКО ЭТО НУЖНО ПИХАТЬ СЮДА??? (mqtt_handler) ////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void MQTT::set_divingTime(uint32_t divingTime){
    _divingTime = divingTime;
}

uint32_t MQTT::get_divingTime(){
    return _divingTime;
}

void MQTT::set_swimmingTime(uint32_t swimmingTime){
    _swimmingTime = swimmingTime;
}

uint32_t MQTT::get_swimmingTime(){
    return _swimmingTime;
}

void MQTT::set_floatingTime(uint32_t floatingTime){
    _floatingTime = floatingTime;
}

uint32_t MQTT::get_floatingTime(){
    return _floatingTime;
}

void MQTT::set_targetDepth(float targetDepth){
    _targetDepth = targetDepth;
}

float MQTT::get_targetDepth(){
    return _targetDepth;
}

void MQTT::set_floatingDepth(float floatingDepth){
    _floatingDepth = floatingDepth;
}

float MQTT::get_floatingDepth(){
    return _floatingDepth;
}

void MQTT::set_startStatus(bool startStatus){
    _startStatus = startStatus;
}

bool MQTT::get_startStatus(){
    return _startStatus;
}

/////////////////////////////////////////////// HANDLERS ///////////////////////////////////////////

void MQTT::start_handler(){
    DPRINTLN("Start msg was received!!!");
    log("Start msg was received!!!");
    set_startStatus(true);
}

void MQTT::reboot_handler(){
    ESP.restart();
}

void MQTT::resetWIFI_handler(){
    DPRINTLN("mqtt resetWIFI handler");
    log("mqtt resetWIFI handler");
}

void MQTT::resetMQTT_handler(){
    DPRINTLN("mqtt resetMQTT handler");
    log("mqtt resetMQTT handler");
}

void MQTT::set_divingTime_handler(String msg){
    DPRINTLN("mqtt_setDivingTime_handler");
    log("mqtt_setDivingTime_handler");
    set_divingTime(msg.toInt());
}

void MQTT::set_floatingTime_handler(String msg){
    DPRINTLN("mqtt_setFloattingTime_handler");
    log("mqtt_setFloattingTime_handler");
    set_floatingTime(msg.toInt());
}

void MQTT::set_swimmingTime_handler(String msg){
    DPRINTLN("mqtt_setSwimmingTime_handler");
    log("mqtt_setSwimmingTime_handler");
    set_swimmingTime(msg.toInt());
}

void MQTT::set_targetDepth_handler(String msg){
    DPRINTLN("mqtt_setTargetDepth_handler");
    log("mqtt_setTargetDepth_handler");
    set_targetDepth(msg.toFloat());
}

void MQTT::set_servo_handler(String msg){
    DPRINTLN("Received Servo command:");
    log("Received Servo command:");
    Serial.println(msg);
    if (msg == "Up"){
        DPRINTLN("Floating Up!");
        log("Floating Up!");
        //buoyancyServo_float();
    }
    else if (msg == "Down"){
        DPRINTLN("Diving Down!");
        log("Diving Down!");
        //buoyancyServo_dive();
    }
    else{
        DPRINTLN("Wrong servo-command");
        log("Wrong servo-command");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

bool MQTT::check_connection(){
    return (WiFi.status() == WL_CONNECTED);
}

bool MQTT::connect(){
    /*PubSubClient client(_host, // проблема перевода char в const char
                    _port,
                    callback,
                    espClient);*/
    bool result = 0;
    if (client.connect(MQTT_DEVICE_ID, MQTT_USER, MQTT_PSWD)) {
        client.publish(MQTT_TEST_TOPIC, HELLO_MSG);
        client.subscribe(MQTT_START_TOPIC);
        client.subscribe(MQTT_REBOOT_TOPIC);
        client.subscribe(MQTT_RESET_MQTT_TOPIC);
        client.subscribe(MQTT_RESET_WIFI_TOPIC);
        client.subscribe(MQTT_SET_DIVING_TIME_TOPIC);
        client.subscribe(MQTT_SET_SWIMMING_TIME_TOPIC);
        client.subscribe(MQTT_SET_FLOATTING_TIME_TOPIC);
        client.subscribe(MQTT_TARGET_DEPTH_TOPIC);
        client.subscribe(MQTT_SET_SERVO);
        
        client.subscribe(MQTT_SET_DIVING_TIME_TOPIC);
        
        client.subscribe(MQTT_SET_DIVING_TIME_TOPIC);
        
        client.subscribe(MQTT_SET_DIVING_TIME_TOPIC);
        result = 1;
    }
    return result;
}

void MQTT::tick(){
    client.loop();
}

void MQTT::routine(){
    if (!check_connection()) {
        reconnect();
    }
    tick();
}

void MQTT::reconnect(){
    if (!wifi.check_connection()){
        wifi.stop();
        delay(WIFI_RESET_TIMEOUT);
        wifi.setup();
    }
    bool fl = 0;
    while (!fl) {
        DPRINT("Attempting MQTT connection...");
        log("Attempting MQTT connection...");

        if (connect()) {
            fl = 1;
            DPRINTLN("connected!\nsubscribed!");
            log("connected!\nsubscribed!");
        } else {
            DPRINTLN((String)"failed, rc=" + 
                    client.state() + 
                    "try again in 5 seconds");
            delay(MQTT_RECONNECT_TIMEOUT);
        }
    }
}

void MQTT::log(String msg){
    DPRINTLN((String)"LOGS:" + msg);
    client.publish(MQTT_LOG_TOPIC, msg.c_str());
}

void MQTT::send_sensorData(String msg){
    client.publish(MQTT_DATA_TOPIC, msg.c_str());
}

void MQTT::callback(char* topic, byte* message, unsigned int length){
    String topicStr = topic;

    DPRINT((String)"Message arrived on topic: " +
            topic + 
            ". Message: ");
    log((String)"Message arrived on topic: " +
            topic + 
            ". Message: ");

    String msgStr;

    for (int i = 0; i < length; i++) {
        DPRINT((char)message[i]);
        msgStr += (char)message[i];
    }
    log(msgStr);

    /*
    switch (topicStr){
        case MQTT_REBOOT_TOPIC:{
            mqtt_reboot_handler(msgStr);
        }
        case MQTT_RESET_MQTT_TOPIC:{
            mqtt_resetMqtt_handler(msgStr);
        }
        case MQTT_RESET_WIFI_TOPIC:{
            mqtt_resetWifi_handler(msgStr);
        }
    }
    */

    if (topicStr == MQTT_REBOOT_TOPIC){
        DPRINTLN("rebooting...");
        log("rebooting...");
        reboot_handler();
    }
    else if (topicStr == MQTT_RESET_MQTT_TOPIC){
        DPRINTLN("mqtt setting...");
        log("mqtt setting...");
        resetMQTT_handler();
    }
    else if (topicStr == MQTT_RESET_WIFI_TOPIC){
        DPRINTLN("wifi reset setting...");
        log("wifi reset setting...");
        resetWIFI_handler();
    }
    else if (topicStr == MQTT_SET_DIVING_TIME_TOPIC){
        DPRINTLN("DiveT setting...");
        log("DiveT setting...");
        set_divingTime_handler(msgStr);
    }
    else if (topicStr == MQTT_SET_SWIMMING_TIME_TOPIC){
        DPRINTLN("SwimmT setting...");
        log("SwimmT setting...");
        set_swimmingTime_handler(msgStr);
    }
    else if (topicStr == MQTT_SET_FLOATTING_TIME_TOPIC){
        DPRINTLN("FLOATT setting...");
        log("FLOATT setting...");
        set_floatingTime_handler(msgStr);
    }
    else if (topicStr == MQTT_TARGET_DEPTH_TOPIC){
        DPRINTLN("target depth setting...");
        log("target depth setting...");
        set_targetDepth_handler(msgStr);
    }
    else if (topicStr == MQTT_SET_SERVO){
        DPRINTLN("Set servo");
        log("Set servo");
        set_servo_handler(msgStr);
    }
    else if (topicStr == MQTT_START_TOPIC){
        DPRINTLN("Start cmd received!");
        log("Start cmd received!");
        start_handler();
    }
}