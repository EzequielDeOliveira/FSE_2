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

    receive_messages();

    return 0;
}