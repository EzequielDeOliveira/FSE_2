#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "client.h"
#include "csv.h"
#include "server.h"
#include "data.h"
#include "dashboard.h"

void menu()
{
    int command = 0;
    while(command != -1){
        scanf("%d", &command);
        send_command(command);
    }
}

void getbme()
{
    while (1)
    {
        send_command(-1);
        usleep(700000);
    }
}

int main(int argc, char **argv)
{
    pthread_t tid[3];
    init_data();
    csv_setup();

    pthread_create(&tid[0], NULL, (void *)dashboard, (void *)NULL);
    /* pthread_create(&tid[0], NULL, (void *)menu, (void *)NULL);
    pthread_create(&tid[1], NULL, (void *)getbme, (void *)NULL); */

    pthread_join(tid[0], NULL);
    /* pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL); */

    return 0;
}