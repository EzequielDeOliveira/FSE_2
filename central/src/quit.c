#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "dashboard.h"
#include "alarm.h"

void finish(int signal)
{
    finish_alarm();
    finish_dashboard();
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
    signal(SIGTSTP, finish);
    signal(SIGPIPE, finishWithError);
}