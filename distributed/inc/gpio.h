#ifndef GPIO_H
#define GPIO_H

#include <bcm2835.h>

#define LAMP_1 RPI_V2_GPIO_P1_11 // BCM 17
#define LAMP_2 RPI_V2_GPIO_P1_12 // BCM 18
#define LAMP_3 RPI_V2_GPIO_P1_13 // BCM 27
#define LAMP_4 RPI_V2_GPIO_P1_15 // BCM 22
#define AIR_1 RPI_V2_GPIO_P1_33 // BCM 13
#define AIR_2 RPI_V2_GPIO_P1_35 // BCM 19
#define PRESENCE_SENSOR_1 RPI_V2_GPIO_P1_22 // BCM 25
#define PRESENCE_SENSOR_2 RPI_V2_GPIO_P1_37 // BCM 26
#define OPENING_SENSOR_1 RPI_V2_GPIO_P1_29 // BCM 05
#define OPENING_SENSOR_2 RPI_V2_GPIO_P1_31 // BCM 06
#define OPENING_SENSOR_3 RPI_V2_GPIO_P1_31 // BCM 12
#define OPENING_SENSOR_4 RPI_V2_GPIO_P1_36 // BCM 16
#define OPENING_SENSOR_5 RPI_V2_GPIO_P1_38 // BCM 20
#define OPENING_SENSOR_6 RPI_V2_GPIO_P1_40 // BCM 21


void bcm2835_setup();
void turn_off_all();
void turn_on(int device);
void turn_off(int device);
void interrupcao();

#endif