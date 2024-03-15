#include <Arduino.h>

#include "average_num.h"
#include "settings.h"

byte counter = 0;


float envSensorsAverage_dsTemp(float newVal_dsTemp){
  static float prevResult_dsTemp = 0;
  static float sum_dsTemp = 0;
  sum_dsTemp += newVal_dsTemp;
  counter++;
  if (counter == NUM_READ) {
    prevResult_dsTemp = sum_dsTemp / NUM_READ;
    sum_dsTemp = 0;
  }
  return prevResult_dsTemp;
}

float envSensorsAverage_msPressure(float newVal_msPressure){
  static float prevResult_msPressure = 0;
  static float sum_msPressure = 0;
  sum_msPressure += newVal_msPressure;
  if (counter == NUM_READ) {
    prevResult_msPressure = sum_msPressure / NUM_READ;
    sum_msPressure = 0;
  }
  return prevResult_msPressure;
}

float envSensorsAverage_msTemp(float newVal_msTemp){
  static float prevResult_msTemp = 0;
  static float sum_msTemp = 0;
  sum_msTemp += newVal_msTemp;
  if (counter == NUM_READ) {
    prevResult_msTemp = sum_msTemp / NUM_READ;
    sum_msTemp = 0;
  }
  return prevResult_msTemp;
}

float envSensorsAverage_msDepth(float newVal_msDepth){
  static float prevResult_msDepth = 0;
  static float sum_msDepth = 0;
  sum_msDepth += newVal_msDepth;
  if (counter == NUM_READ) {
    prevResult_msDepth = sum_msDepth / NUM_READ;
    sum_msDepth = 0;
  }
  return prevResult_msDepth;
}

float envSensorsAverage_msAltitude(float newVal_msAltitude){
  static float prevResult_msAltitude = 0;
  static float sum_msAltitude = 0;
  sum_msAltitude += newVal_msAltitude;
  if (counter == NUM_READ) {
    prevResult_msAltitude = sum_msAltitude / NUM_READ;
    sum_msAltitude = 0;
  }
  return prevResult_msAltitude;
}

float envSensorsAverage_tdsNormConductivity(float newVal_tdsNormConductivity){
  static float prevResult_tdsNormConductivity = 0;
  static float sum_tdsNormConductivity = 0;
  sum_tdsNormConductivity += newVal_tdsNormConductivity;
  if (counter == NUM_READ) {
    prevResult_tdsNormConductivity = sum_tdsNormConductivity / NUM_READ;
    sum_tdsNormConductivity = 0;
  }
  return prevResult_tdsNormConductivity;
}

float envSensorsAverage_tdsEC(float newVal_tdsEC){
  static float prevResult_tdsEC = 0;
  static float sum_tdsEC = 0;
  sum_tdsEC += newVal_tdsEC;
  if (counter == NUM_READ) {
    prevResult_tdsEC = sum_tdsEC / NUM_READ;
    sum_tdsEC = 0;
  }
  return prevResult_tdsEC;
}

float envSensorsAverage_tdsTDS(float newVal_tdsTDS){
  static float prevResult_tdsTDS = 0;
  static float sum_tdsTDS = 0;
  sum_tdsTDS += newVal_tdsTDS;
  if (counter == NUM_READ) {
    prevResult_tdsTDS = sum_tdsTDS / NUM_READ;
    sum_tdsTDS = 0;
  }
  return prevResult_tdsTDS;
}

float envSensorsAverage_PH(float newVal_PH){
  static float prevResult_PH = 0;
  static float sum_PH = 0;
  sum_PH += newVal_PH;
  if (counter == NUM_READ) {
    prevResult_PH = sum_PH / NUM_READ;
    sum_PH = 0;
  }
  return prevResult_PH;
}

float envSensorsAverage_Turbidity(float newVal_Turbidity){
  static float prevResult_Turbidity = 0;
  static float sum_Turbidity = 0;
  sum_Turbidity += newVal_Turbidity;
  if (counter == NUM_READ) {
    prevResult_Turbidity = sum_Turbidity / NUM_READ;
    sum_Turbidity = 0;
    counter = 0;
  }
  return prevResult_Turbidity;
}