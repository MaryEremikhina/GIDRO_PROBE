#ifndef ___BUOYANCY_H___
#define ___BUOYANCY_H___

void buoyancyServo_init();
void buoyancyServo_dive();
void buoyancyServo_float();
void enders_init();
void buoyancyServo_swim();

bool check_conUpEnder();
bool check_conDownEnder();

#endif