#ifndef ___SETTINGS_H___
#define ___SETTINGS_H___


#define ___DEBUG___
//#define ___OTA___
#define ___LAUNCH_WITHOUT_MS5837___

#include "classes/logging.h"
Logging logging;

#define SERIAL_SPEED 115200

//////////////////////////////////////////////////////
/////////////////////  AVERAGE  //////////////////////
//////////////////////////////////////////////////////

const int NUM_READ = 4;

///////////////////////////////////////////////////////
///////////////////  TIME CONST  //////////////////////
///////////////////////////////////////////////////////

const int SEC_IN_MINUTE = 60;
const int SEC_IN_HOUR = 60;
const int SEC_IN_DAY = 24;

///////////////////////////////////////////////////////
////////////////////  TIMINGS /////////////////////////
///////////////////////////////////////////////////////

#define ENV_SENSORS_TASK_PERIOD_MS 1000
#define MS5837_ERR_INIT_TIMEOUT 5000
#define MQTT_RECONNECT_TIMEOUT 5000
#define WIFI_CON_DOT_TIMEOUT 500
#define WIFI_RESET_TIMEOUT 1000



///////////////////////////////////////////////////////
////////////////  WI-Fi SETTINGS //////////////////////
///////////////////////////////////////////////////////

#define WIFI_SSID "Capybargo"
#define WIFI_PSWD "12345678"

///////////////////////////////////////////////////////
/////////////////  MQTT SETTINGS //////////////////////
///////////////////////////////////////////////////////

#define MQTT_HOST "192.168.177.51"
#define MQTT_PORT 1883
#define MQTT_USER "admin"
#define MQTT_PSWD "12344321"
#define MQTT_DEVICE_ID "esp32_argo-1"

///////////////////////////////////////////////////////
/////////////////  MQTT TOPICS ////////////////////////
///////////////////////////////////////////////////////

#define MQTT_START_TOPIC "start"

#define MQTT_REBOOT_TOPIC "reboot"
#define MQTT_RESET_MQTT_TOPIC "resetMqtt"
#define MQTT_RESET_WIFI_TOPIC "resetWifi"

#define MQTT_LOG_TOPIC "logs"
#define MQTT_DATA_TOPIC "sensorData"

#define MQTT_SET_DIVING_TIME_TOPIC "divingTime"
#define MQTT_SET_SWIMMING_TIME_TOPIC "swimmingTime"
#define MQTT_SET_FLOATTING_TIME_TOPIC "floattingTime"
#define MQTT_TARGET_DEPTH_TOPIC "targetDepth"
#define MQTT_SET_SERVO "setServo"

#define MQTT_TEST_TOPIC "test"
#define HELLO_MSG "Hello World!!!"

///////////////////////////////////////////////////////
///////////////////////   PINS   //////////////////////
///////////////////////////////////////////////////////

#define TDS_PIN 35
#define TURBIDITY_PIN 27 
#define DS12B20_1WIRE_BUS 33
#define PH_PIN 37

#define CON_UP_PIN 25  // точно вверх 
#define CON_DOWN_PIN 34  // точно вниз
#define BUOYANCY_SERVO_PIN 17

#define PIN_CHIP 5


#ifdef ___LOG___
  #define LOG(X) logging.log(X) 
#else
  #define LOG(X)
#endif


#ifdef ___DEBUG___
  #define DPRINT(X) Serial.print(X)
  #define DPRINTLN(X) Serial.println(X)
#else
  #define DPRINT(X)
  #define DPRINTLN(X)
#endif

#endif