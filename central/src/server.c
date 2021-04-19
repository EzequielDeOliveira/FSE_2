#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "data.h"

void handleSensor(int sensor)
{
    Data data = get_data();

    switch (sensor)
    {
    case PRESENCE_SENSOR_1:
        if (data.presences1 == 0)
        {
            data.presences1 = 1;
        }
        else
        {
            data.presences1 = 0;
        }
        break;

    case PRESENCE_SENSOR_2:
        if (data.presences2 == 0)
        {
            data.presences2 = 1;
        }
        else
        {
            data.presences2 = 0;
        }
        break;

    case OPENING_SENSOR_1:
        if (data.openings1 == 0)
        {
            data.openings1 = 1;
        }
        else
        {
            data.openings1 = 0;
        }
        break;

    case OPENING_SENSOR_2:
        if (data.openings2 == 0)
        {
            data.openings2 = 1;
        }
        else
        {
            data.openings2 = 0;
        }
        break;

    case OPENING_SENSOR_3:
        if (data.openings3 == 0)
        {
            data.openings3 = 1;
        }
        else
        {
            data.openings3 = 0;
        }
        break;

    case OPENING_SENSOR_4:
        if (data.openings4 == 0)
        {
            data.openings4 = 1;
        }
        else
        {
            data.openings4 = 0;
        }
        break;

    case OPENING_SENSOR_5:
        if (data.openings5 == 0)
        {
            data.openings5 = 1;
        }
        else
        {
            data.openings5 = 0;
        }
        break;

    case OPENING_SENSOR_6:
        if (data.openings6 == 0)
        {
            data.openings6 = 1;
        }
        else
        {
            data.openings6 = 0;
        }
        break;

    default:
        break;
    }

    set_data(data);
}

void TrataClientTCP(int socketClient)
{
    char buffer[16];
    char response[16];
    int tamanhoRecebido;
    int command;

    if ((tamanhoRecebido = recv(socketClient, buffer, 16, 0)) < 0)
        printf("Erro no recv()\n");
    sscanf(buffer, "%d", &command);
    snprintf(response, 15, "%d", command);
    printf("%d", command);
    handleSensor(command);

    while (tamanhoRecebido > 0)
    {
        if (send(socketClient, response, 16 - 1, 0) != 15)
            printf("Erro no envio - sends()\n");

        if ((tamanhoRecebido = recv(socketClient, buffer, 16, 0)) < 0)
            printf("Erro no recv()\n");
        sscanf(buffer, "%d", &command);
        snprintf(response, 15, "%d", command);
    }
}

void receive_messages()
{
    int servidorSocket;
    int socketCliente;
    struct sockaddr_in servidorAddr;
    struct sockaddr_in clienteAddr;
    unsigned short servidorPorta;
    unsigned int clienteLength;

    servidorPorta = 10015;

    if ((servidorSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        printf("falha no socker do Servidor\n");

    memset(&servidorAddr, 0, sizeof(servidorAddr));
    servidorAddr.sin_family = AF_INET;
    servidorAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servidorAddr.sin_port = htons(servidorPorta);

    if (bind(servidorSocket, (struct sockaddr *)&servidorAddr, sizeof(servidorAddr)) < 0)
        printf("Falha no Bind\n");

    if (listen(servidorSocket, 10) < 0)
        printf("Falha no Listen\n");

    while (1)
    {
        clienteLength = sizeof(clienteAddr);
        if ((socketCliente = accept(
                 servidorSocket,
                 (struct sockaddr *)&clienteAddr,
                 &clienteLength)) < 0)
            printf("Falha no Accept\n");

        printf("Conexão do Cliente %s\n", inet_ntoa(clienteAddr.sin_addr));

        TrataClientTCP(socketCliente);
        close(socketCliente);
    }
    close(servidorSocket);
}