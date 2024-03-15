#include <ESP32Servo.h>

#include "settings.h"
#include "buoyancy.h"
#include "mqtt_handlers.h"


#define DOWN 0
#define STOP 90
#define UP   180

Servo buoyancyServo;

void enders_init(){
  pinMode(CON_UP_PIN, INPUT_PULLUP);
  pinMode(CON_DOWN_PIN, INPUT_PULLUP);
}

bool check_conUpEnder(){
  bool upEnder = digitalRead(CON_UP_PIN);
  return upEnder;
}

bool check_conDownEnder(){
  bool downEnder = digitalRead(CON_DOWN_PIN);
  return downEnder;
}

void buoyancyServo_init(){
 buoyancyServo.attach(BUOYANCY_SERVO_PIN, 544, 2400);
}

void buoyancyServo_detach(){
 buoyancyServo.detach();
}  

void buoyancyServo_dive(){
  DPRINTLN("BuoyancyServo diving start!");
  log("BuoyancyServo diving start!");
  buoyancyServo.write(UP);
  DPRINTLN("Waiting for up ender...");
  log("Waiting for up ender...");
  while (!check_conUpEnder()){
    //nnnnn
  }
  DPRINTLN("Up Ender was clicked!");
  log("Up Ender was clicked!");
  buoyancyServo.write(STOP);
  DPRINT("Servo was stopped!!!");
  log("Servo was stopped!!!");
}

void buoyancyServo_float(){
  DPRINTLN("BuoyancyServo floating start!");
  log("BuoyancyServo floating start!");
  buoyancyServo.write(DOWN);
  DPRINTLN("Waiting for down ender...");
  log("Waiting for down ender...");
  while (!check_conDownEnder()){
    //DPRINTLN();
  }
  DPRINTLN("Down Ender was clicked!");
  log("Down Ender was clicked!");
  buoyancyServo.write(STOP);
  DPRINTLN("Servo was stopped!!!");
  log("Servo was stopped!!!");
}

void buoyancyServo_swim(){
  DPRINTLN("BuoyancyServo swimming start!");
  log("BuoyancyServo swimming start!");
  delay(get_SwimmingTime());
}