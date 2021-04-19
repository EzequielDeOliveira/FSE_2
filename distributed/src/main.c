#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <bme280.h>
#include "gpio.h"
#include "csv.h"
#include "server.h"

void finish(int sinal)
{
    interrupcao();
}

int main(int argc, char **argv)
{

    signal(SIGINT, finish);
    bcm2835_setup();
    bme280_init();
    /*     
    float temperature = 0, humidity = 0;


    ligar_lampada(1);

    while(1){
        get_current_time();
        bme280_temperature(&temperature, &humidity);
        printf("%f %f\n", temperature, humidity);

        usleep(1000000);
    } */

    receive_messages();

    return 0;
}