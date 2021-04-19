#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <bme280.h>
#include "gpio.h"
#include "csv.h"
#include "server.h"
#include "data.h"

void finish(int sinal)
{
    interrupcao();
}

int main(int argc, char **argv)
{

    signal(SIGINT, finish);
    bcm2835_setup();
    bme280_init();
    init_data();

    pthread_t tid[2];

    pthread_create(&tid[0], NULL, (void *)receive_messages, (void *)NULL);
    pthread_create(&tid[0], NULL, (void *)handleSensor, (void *)NULL);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    return 0;
}