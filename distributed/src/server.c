#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <bme280.h>
#include "gpio.h"
#include "data.h"
#include "quit.h"

#define PORT 10115

void handleDevices(int device)
{
    Data data = get_data();

    switch (device)
    {
    case LAMP_1:
        if (data.lamp1 == 0)
        {
            change_state(device, 1);
            data.lamp1 = 1;
        }
        else
        {

            change_state(device, 0);
            data.lamp1 = 0;
        }
        break;
    case LAMP_2:
        if (data.lamp2 == 0)
        {
            change_state(device, 1);
            data.lamp2 = 1;
        }
        else
        {

            change_state(device, 0);
            data.lamp2 = 0;
        }
        break;
    case LAMP_3:
        if (data.lamp3 == 0)
        {
            change_state(device, 1);
            data.lamp3 = 1;
        }
        else
        {

            change_state(device, 0);
            data.lamp3 = 0;
        }
        break;
    case LAMP_4:
        if (data.lamp4 == 0)
        {
            change_state(device, 1);
            data.lamp4 = 1;
        }
        else
        {

            change_state(device, 0);
            data.lamp4 = 0;
        }
        break;
    case AIR_1:
        if (data.air1 == 0)
        {
            change_state(device, 1);
            data.air1 = 1;
        }
        else
        {

            change_state(device, 0);
            data.air1 = 0;
        }
        break;
    case AIR_2:
        if (data.air2 == 0)
        {
            change_state(device, 1);
            data.air2 = 1;
        }
        else
        {

            change_state(device, 0);
            data.air2 = 0;
        }
        break;

    default:
        break;
    }
    set_data(data);
}

void handleClient(int socketClient)
{
    char buffer[16];
    char response[16];
    int responseLength;
    int command;
    struct bme280_data data = bme280_read();

    if ((responseLength = recv(socketClient, buffer, 16, 0)) < 0)
    {
        printf("Erro no recv()\n");
        finishWithError(0);
    }
    sscanf(buffer, "%d", &command);
    handleDevices(command);
    data = bme280_read();
    snprintf(response, 15, "%d %.2f %.2f", command, data.temperature, data.humidity);

    if (send(socketClient, response, 16 - 1, 0) != 15)
    {
        printf("Erro no envio - sends()\n");
        finishWithError(0);
    }
}

void receive_messages()
{
    int serverSocket;
    int socketClient;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    unsigned int clientLength;

    if ((serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("falha no socker do Servidor\n");
        finishWithError(0);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        printf("Falha no Bind\n");
        finishWithError(0);
    }

    if (listen(serverSocket, 10) < 0)
    {
        printf("Falha no Listen\n");
        finishWithError(0);
    }

    while (1)
    {
        clientLength = sizeof(clientAddr);
        if ((socketClient = accept(
                 serverSocket,
                 (struct sockaddr *)&clientAddr,
                 &clientLength)) < 0)
        {
            printf("Falha no Accept\n");
            finishWithError(0);
        }

        printf("Client Connected %s\n", inet_ntoa(clientAddr.sin_addr));

        handleClient(socketClient);
        close(socketClient);
    }
    close(serverSocket);
}