#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <bme280.h>
#include "gpio.h"
#include "server.h"
#include "data.h"
#include "quit.h"


int main(int argc, char **argv)
{
    bme280_init();
    init_data();
    gpio_setup();
    quit_handler();   
    receive_messages();
    return 0;
}