#include <WiFiUdp.h>
#include <SD.h>

#include "myEnvSensors.h"
#include "settings.h"
#include "wifi_mqtt.h"
#include "libraries/NTPClient-master/NTPClient.h"

#include "sd_card.h"

File myFile;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

String file_name; 
int lasttime;
int now;

int day;
int hour;
int mini;
int sec;

void sd_card_init(){
    pinMode(PIN_CHIP, OUTPUT);
    while (!SD.begin(PIN_CHIP)) {
        DPRINTLN("Card failed, or not present");
        log("Card failed, or not present");
        // Если что-то пошло не так, завершаем работу:
        delay(100);
    }
    DPRINTLN("card initialized.");
    log("card initialized.");
}

void create_file(){
    timeClient.begin();
    timeClient.setTimeOffset(10800);
    String formattedDate;
    while(!timeClient.update()) {
        timeClient.forceUpdate();
    };
    formattedDate = timeClient.getFormattedDate();
    day = timeClient.getDay();
    hour = timeClient.getHours();
    mini = timeClient.getMinutes();
    sec = timeClient.getSeconds();
    file_name = (String)"/" + day + "_" + hour + "_" + mini + "_" + sec + ".csv";
    DPRINTLN(file_name);
    log(formattedDate);
    lasttime = millis();
}

void file_init(){
    // create a new file by opening a new file and immediately close it
    myFile = SD.open(file_name, FILE_APPEND);
    myFile.println(dataframe_csvHeader_toString());
    DPRINTLN("file was opened");
    log("file was opened");
    myFile.close();
}

void sec_to_min(){
    int secs = sec + (now - lasttime) / 1000;
    sec = secs % SEC_IN_MINUTE;
    mini += secs / SEC_IN_MINUTE;
}

void sec_to_hour(){
    int mins = mini + ((now - lasttime) / 1000) / SEC_IN_MINUTE;
    mini = mins % SEC_IN_HOUR;
    hour += mins / SEC_IN_HOUR;
}

void sec_to_day(){
    int hours = hour + ((now - lasttime) / 1000) / (SEC_IN_MINUTE * SEC_IN_HOUR);
    hour = hours % SEC_IN_DAY;
    day += hours / SEC_IN_DAY;
}

void saveDataFrame(envSensorData df){
    now = millis();
    sec_to_min();
    sec_to_hour();
    sec_to_day();
    if (SD.exists(file_name)){
        myFile = SD.open(file_name, FILE_APPEND);
        myFile.println((String)hour + ":" + mini + ":" + sec + ";" + dataframe_csvData_toString(df));
        myFile.close();
        DPRINTLN("data was received");
        log("data was received");
    }
    else {
        DPRINTLN(F("file doesn't exist on SD Card."));
        log("file doesn't exist on SD Card.");
    }
}

void sendDataFrame(){
    myFile = SD.open(file_name, FILE_READ);
    DPRINTLN("Start reading data from SD-card");
    if (myFile) {
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
        mqtt_send_sensorData(msg);
        myFile.close();
    } else {
        DPRINTLN(F("SD Card: Issue encountered while attempting to open the file"));
        log("SD Card: Issue encountered while attempting to open the file");
    }
}

/*envSensorData dataBuffer[300];

int index_db = 0;

void db_saveDataFrame(envSensorData df){
    dataBuffer[index_db] = df;
    index_db++;
}

envSensorData get_df_fromDB_byIndex(int i){
    return dataBuffer[0];
}

void reset_DB(){
    index_db=0;
}

int get_DB_index(){
    return index_db;
}*/
