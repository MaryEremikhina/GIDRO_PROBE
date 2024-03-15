#include <Arduino.h>
#include <SD.h>

#include "settings.h"

#include "libraries/NTPClient-master/NTPClient.h"
#include <WiFiUdp.h>

File myF;
WiFiUDP lntpUDP;
NTPClient ltimeClient(lntpUDP);

int llasttime;
int lnow;

int lday;
int lhour;
int lmini;
int lsec;

void file_log(){
    ltimeClient.begin();
    ltimeClient.setTimeOffset(10800);
    String formattedDate;
    while(!ltimeClient.update()) {
        ltimeClient.forceUpdate();
    };
    formattedDate = ltimeClient.getFormattedDate();
    lday = ltimeClient.getDay();
    lhour = ltimeClient.getHours();
    lmini = ltimeClient.getMinutes();
    lsec = ltimeClient.getSeconds();
    myF = SD.open("/log.txt", FILE_APPEND);
    DPRINTLN("file was opened");
    log("file was opened");
    llasttime = millis();
    myF.close();
}

void lsec_to_min(){
    int secs = lsec + (lnow - llasttime) / 1000;
    lsec = secs % SEC_IN_MINUTE;
    lmini += secs / SEC_IN_MINUTE;
}

void lsec_to_hour(){
    int mins = lmini + ((lnow - llasttime) / 1000) / SEC_IN_MINUTE;
    lmini = mins % SEC_IN_HOUR;
    lhour += mins / SEC_IN_HOUR;
}

void lsec_to_day(){
    int hours = lhour + ((lnow - llasttime) / 1000) / (SEC_IN_MINUTE * SEC_IN_HOUR);
    lhour = hours % SEC_IN_DAY;
    lday += hours / SEC_IN_DAY;
}

void log(String text){
    lnow = millis();
    lsec_to_min();
    lsec_to_day();
    lsec_to_day();
    if (SD.exists("/log.txt")){
        myF = SD.open("/log.txt", FILE_APPEND);
        myF.println((String)lhour + ":" + lmini + ":" + lsec + " :) " + text);
        myF.close();
        DPRINTLN("data was received");

    }
    else {
        DPRINTLN(F("file doesn't exist on SD Card."));
    }
}