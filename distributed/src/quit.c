#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <bme280.h>
#include "gpio.h"
#include "server.h"
#include "data.h"

void finish(int signal)
{
    turn_off_all();
    printf("Finzalização completa...\n");
    exit(0);
}

void finishWithError(int signal)
{
    printf("Erro no socket...\n");
    finish(0);
}

void quit_handler()
{
    signal(SIGINT, finish);
    signal(SIGPIPE, finishWithError);
}