#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include "client.h"
#include "csv.h"
#include "server.h"
#include "data.h"
#include "dashboard.h"
#include "quit.h"

void getbme()
{
    while (1)
    {
        send_command(-1);
        usleep(800000);
    }
}

int main(int argc, char **argv)
{

    pthread_t tid[3];
    init_data();
    csv_setup();
    quit_handler();

    pthread_create(&tid[0], NULL, (void *)dashboard, (void *)NULL);
    pthread_create(&tid[1], NULL, (void *)getbme, (void *)NULL);
    pthread_create(&tid[2], NULL, (void *)receive_messages, (void *)NULL);
    

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);

    return 0;
}