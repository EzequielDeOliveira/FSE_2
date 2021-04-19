#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "client.h"
#include "csv.h"

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
        send_command(0);
        get_current_time();
        usleep(700000);
    }
}

int main(int argc, char **argv)
{

    pthread_t tid[2];

    pthread_create(&tid[0], NULL, (void *)menu, (void *)NULL);
    pthread_create(&tid[1], NULL, (void *)getbme, (void *)NULL);

    return 0;
}