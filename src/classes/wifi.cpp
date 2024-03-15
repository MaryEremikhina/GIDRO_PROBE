#include "wifi.h"
#include <Arduino.h>

#include <WiFi.h>
#include "modules/settings.h"

#define WIFI_IS_OFF 0x0
#define WIFI_IS_ON 0x1

WIFI::WIFI(){
    _ssid = WIFI_SSID;
    _pswd = WIFI_PSWD;
    _mode = WIFI_IS_ON;
    setup();
}

WIFI::WIFI(String ssid, String pswd){
    _ssid = ssid;
    _pswd = pswd;
    _mode = WIFI_IS_ON;
    setup();
}

WIFI::WIFI(bool mode){
    _ssid = WIFI_SSID;
    _pswd = WIFI_PSWD;
    _mode = mode;
    setup();
}

WIFI::WIFI(String ssid, String pswd, bool mode){
    _ssid = ssid;
    _pswd = pswd;
    _mode = mode;
    setup();
}

WIFI::~WIFI(){}

void WIFI::setup(){
    if (get_mode() == WIFI_IS_OFF){
        return;
    }
    delay(10);
    DPRINT("\nConnecting to ");
    DPRINTLN(WIFI_SSID);
    log((String)"\nConnecting to " + WIFI_SSID);
    WiFi.begin(_ssid, _pswd);
    while (!check_connection()) {
        delay(WIFI_CON_DOT_TIMEOUT);
        DPRINT(".");
        log(".");
    }
    DPRINTLN((String)"WiFi connected\n" +
            "IP address: " + 
            String(WiFi.localIP()));  /// Bug with IP print!
    log((String)"WiFi connected\n" +
            "IP address: " + 
            String(WiFi.localIP()));
}

void WIFI::stop(){
    WiFi.disconnect();
}

void WIFI::set_ssid(String ssid){
    _ssid = ssid;
}

void WIFI::set_pswd(String pswd){
    _pswd = pswd;
}

void WIFI::set_mode(bool mode){
    _mode = mode;
}

bool WIFI::get_mode(){
    return _mode;
}

bool WIFI::check_connection(){
    return (WiFi.status() == WL_CONNECTED);
}