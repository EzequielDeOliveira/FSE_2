#ifndef GPIO_H
#define GPIO_H

#include <bcm2835.h>

#define LAMPADA_1 RPI_V2_GPIO_P1_11 // BCM 17
#define LAMPADA_2 RPI_V2_GPIO_P1_12 // BCM 18
#define LAMPADA_3 RPI_V2_GPIO_P1_13 // BCM 27
#define LAMPADA_4 RPI_V2_GPIO_P1_15 // BCM 22
#define AR_1 RPI_V2_GPIO_P1_33 // BCM 13
#define AR_2 RPI_V2_GPIO_P1_35 // BCM 19
#define SENSOR_PRESENCA_1 RPI_V2_GPIO_P1_22 // BCM 25
#define SENSOR_PRESENCA_2 RPI_V2_GPIO_P1_37 // BCM 26
#define SENSOR_ABERTURA_1 RPI_V2_GPIO_P1_29 // BCM 05

void cofigura_pinos();
void ligar_lampada(int comando);
void interrupcao(int sinal);

#endif