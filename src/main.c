#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "gpio.h"

int main(int argc, char **argv){

    bcm2835_setup();

    signal(SIGINT, interrupcao);

    ligar_lampada(1);

    while(1){
        while(bcm2835_gpio_lev(SENSOR_PRESENCA_1) || bcm2835_gpio_lev(SENSOR_ABERTURA_1)) {
            printf("SENSOR DE PRESENÇA ACIONADO\n");
        }
    }

    return 0;
}