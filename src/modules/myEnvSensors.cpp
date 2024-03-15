#include "myEnvSensors.h"

#include "tds_sensor.h"
#include "my_ms5837.h"
#include "ds12b20.h"
#include "turbidity.h"
#include "ph_sensor.h"
#include "sd_card.h"
#include "average_num.h"

#include "settings.h"
#include "buoyancy.h"


#define ___DEBUG_MODE___

byte count = 0;

envSensorData envSensorData_stamp;

envSensorData get_envData_stamp()
{
  return envSensorData_stamp;
};

//////////////////////////////////////////////////////////////////////////////
///////////////////   COMMON SENSOR FUNCTIONS   //////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void envSensors_init() {
  tds_init();
  ds12b20_init();
  ms5837_init();
  ph_init();
}

void envSensorsUpdate(envSensorData &data) {
  float dsTemp = ds12b20_getTemp();

  ms5837_update();
  float msPressure = get_pressure();
  float msTemperature = get_temperature();
  float msDepth = get_depth();
  float msAltitude = get_altitude();
  
  
  float tdsNormConductivity = get_normConductivity();
  float tdsEC = get_EC(data.tdsNormConductivity);
  float tdsTDS = get_TDS(data.tdsEC);

  float PH = get_ph();
  float Turbidity = get_turbidity();

  data.dsTemp = envSensorsAverage_dsTemp(dsTemp);
  data.msPressure = envSensorsAverage_msPressure(msPressure);
  data.msTemperature = envSensorsAverage_msTemp(msTemperature);
  data.msDepth = envSensorsAverage_msDepth(msDepth);
  data.msAltitude = envSensorsAverage_msAltitude(msAltitude);
  data.tdsNormConductivity = envSensorsAverage_tdsNormConductivity(tdsNormConductivity);
  data.tdsEC = envSensorsAverage_tdsEC(tdsEC);
  data.tdsTDS = envSensorsAverage_tdsTDS(tdsTDS);
  data.PH = envSensorsAverage_PH(PH);
  data.Turbidity = envSensorsAverage_Turbidity(Turbidity);
  count += 1;
  if (count == NUM_READ){
    DPRINTLN("Start averaging");
    log("Start averaging");
    saveDataFrame(data);
    count = 0;
  }
}

void envSensorData_print(envSensorData &data) {
  Serial.print((String)"Temp C: " + data.dsTemp + " deg C\n" +
               "Pressure: " + data.msPressure + " mbar\n" +
               "Temperature: " + data.msTemperature + " deg C\n" +
               "Depth: " + data.msDepth + " m\n" +
               "Altitude: " + data.msAltitude + " m above mean sea level\n" +
               "S = " + data.tdsNormConductivity + " мСм/см\n" +
               "EC = " + data.tdsEC + " мСм/см\n" +
               "TDS = " + data.tdsTDS + " мг/л\n" +
               "PH = " + data.PH + "\n" +
               "Turbidity = " + data.Turbidity + " мг/л\n");
}


String envSensorData_toString(envSensorData &data) {
  String msg = "";
  msg += (String)"Temp C: " + data.dsTemp + " deg C\n" +
         "Pressure: " + data.msPressure + " mbar\n" +
         "Temperature: " + data.msTemperature + " deg C\n" +
         "Depth: " + data.msDepth + " m\n" +
         "Altitude: " + data.msAltitude + " m above mean sea level\n" +
         "S = " + data.tdsNormConductivity + " мСм/см\n" +
         "EC = " + data.tdsEC + " мСм/см\n" +
         "TDS = " + data.tdsTDS + " мг/л\n" +
         "PH = " + data.PH + "\n" +
         "Turbidity = " + data.Turbidity + " мг/л\n";
  return msg;
}



void print_dataframe_csvHeader(){
  String msg = "";
  msg += (String)"Time" + ";" + "Temp" + ";" + "Pressure" + ";" +
          "Temperature" + ";" + "Depth" + ";" +
          "Altitude" + ";" + "S" + ";" + "EC" + ";" +
          "TDS" + ";" + "PH" + ";" + "Turbidity" + ";" + "UP_ender" + ";" + "DOWN_ender";
  DPRINTLN(msg);
  log(msg);
}

String dataframe_csvHeader_toString(){
  String msg = "";
  msg += (String)"Time" + ";" + "Temp" + ";" + "Pressure" + ";" +
          "Temperature" + ";" + "Depth" + ";" +
          "Altitude" + ";" + "S" + ";" + "EC" + ";" +
          "TDS" + ";" + "PH" + ";" + "Turbidity" + ";" + "UP_ender" + ";" + "DOWN_ender";
  return msg;
}


void print_dataframe_csvData(envSensorData &data){
  String msg = "";
  msg += (String)data.dsTemp + ";" + 
          data.msPressure + ";" +
          data.msTemperature + ";" + 
          data.msDepth + ";" +
          data.msAltitude + ";" + 
          data.tdsNormConductivity + ";" + 
          data.tdsEC  + ";" +
          data.tdsTDS + ";" + 
          data.PH + ";" + 
          data.Turbidity + ";" + 
          (String)check_conUpEnder() + ";" + 
          (String)check_conDownEnder() + ";";
  DPRINTLN(msg);
  log(msg);
}

String dataframe_csvData_toString(envSensorData &data){
  String msg = "";
  msg += (String)data.dsTemp + ";" + 
          data.msPressure + ";" +
          data.msTemperature + ";" + 
          data.msDepth + ";" +
          data.msAltitude + ";" + 
          data.tdsNormConductivity + ";" + 
          data.tdsEC  + ";" +
          data.tdsTDS + ";" + 
          data.PH + ";" + 
          data.Turbidity + ";" +
          (String)check_conUpEnder() + ";" + 
          (String)check_conDownEnder() + ";";
  return msg;
}

String get_sensorMsg(){
  envSensorData dataStamp = get_envData_stamp();
  envSensorsUpdate(dataStamp);
  return dataframe_csvData_toString(dataStamp);
}