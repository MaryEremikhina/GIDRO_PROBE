#include <Arduino.h>

#include "turbidity.h"
#include "settings.h"

/////////////////////////////////////////////////////////////////////////////
//////////////////////  TURBIDITY SENSOR  ///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


int get_turbidity(){
  float turbidity = analogRead(TURBIDITY_PIN) * 0.001;
  return turbidity;
}