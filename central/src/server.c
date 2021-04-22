#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "data.h"
#include "csv.h"
#include "quit.h"

#define PORT_SERVER 10015

int serverSocket;
int socketClient;

void handleSensor(int sensor, int state)
{
    Data data = get_data();

    switch (sensor)
    {
    case PRESENCE_SENSOR_1:
        data.presences1 = state;
        write_csv(PRESENCE_SENSOR_1, state);
        break;

    case PRESENCE_SENSOR_2:
        data.presences2 = state;
        write_csv(PRESENCE_SENSOR_2, 1);
        break;

    case OPENING_SENSOR_1:
        data.openings1 = state;
        write_csv(OPENING_SENSOR_1, 1);
        break;

    case OPENING_SENSOR_2:
        data.openings2 = state;
        write_csv(OPENING_SENSOR_2, 1);
        break;

    case OPENING_SENSOR_3:
        data.openings3 = state;
        write_csv(OPENING_SENSOR_3, 1);
        break;

    case OPENING_SENSOR_4:
        data.openings4 = state;
        write_csv(OPENING_SENSOR_4, 1);
        break;

    case OPENING_SENSOR_5:
        data.openings5 = state;
        write_csv(OPENING_SENSOR_5, 1);
        break;

    case OPENING_SENSOR_6:
        data.openings6 = state;
        write_csv(OPENING_SENSOR_6, 1);
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
    int command, state;

    if ((responseLength = recv(socketClient, buffer, 16, 0)) < 0)
    {
        printf("(SERVER) Erro no recv() SERVER\n");
        finishWithError(0);
    }
    sscanf(buffer, "%d %d", &command, &state);
    snprintf(response, 15, "%d", command, state);
    handleSensor(command, state);

    if (send(socketClient, response, 16 - 1, 0) != 15)
    {
        printf("(SERVER) Erro no envio - sends() SERVER\n");
        finishWithError(0);
    }
}

void close_server_socket()
{
    close(socketClient);
    close(serverSocket);
}

void receive_messages()
{
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    unsigned int clientLength;

    if ((serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("(SERVER) falha no socker do Servidor\n");
        finishWithError(0);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(PORT_SERVER);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        printf("(SERVER) Falha no Bind\n");
        finishWithError(0);
    }

    if (listen(serverSocket, 10) < 0)
    {
        printf("(SERVER) Falha no Listen\n");
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
            printf("(SERVER) Falha no Accept\n");
            finishWithError(0);
        }

        handleClient(socketClient);
        close(socketClient);
    }
    close(serverSocket);
}