#ifndef GPIO_H
#define GPIO_H

#include <wiringPi.h>

#define LAMP_1 0 
#define LAMP_2 1
#define LAMP_3 2
#define LAMP_4 3
#define AIR_1 23
#define AIR_2 24
#define PRESENCE_SENSOR_1 6
#define PRESENCE_SENSOR_2 25
#define OPENING_SENSOR_1 21
#define OPENING_SENSOR_2 22
#define OPENING_SENSOR_3 26
#define OPENING_SENSOR_4 27
#define OPENING_SENSOR_5 28
#define OPENING_SENSOR_6 29

void gpio_setup();
void change_state(int device, int state);
void interrupcao();

#endif