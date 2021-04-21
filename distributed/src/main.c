#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <bme280.h>
#include "gpio.h"
#include "server.h"
#include "data.h"

void finish(int sinal)
{
    interrupcao();
}

int main(int argc, char **argv)
{

    signal(SIGINT, finish);
    bme280_init();
    init_data();
    gpio_setup();
    
    receive_messages();
    return 0;
}