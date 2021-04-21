#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "data.h"
#include "csv.h"

void handleSensor(int sensor, int state)
{
    //printf("(SERVER) HANDLE SENSOR\n");
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

void TrataClientTCP(int socketClient)
{
    char buffer[16];
    char response[16];
    int tamanhoRecebido;
    int command, state;

    if ((tamanhoRecebido = recv(socketClient, buffer, 16, 0)) < 0)
        printf("(SERVER) Erro no recv() SERVER\n");
    sscanf(buffer, "%d %d", &command, &state);
    snprintf(response, 15, "%d", command, state);
    printf("(SERVER) %d SERVER RECEIVED\n", state);
    handleSensor(command, state);

    while (tamanhoRecebido > 0)
    {
        if (send(socketClient, response, 16 - 1, 0) != 15)
            printf("(SERVER) Erro no envio - sends() SERVER\n");

        if ((tamanhoRecebido = recv(socketClient, buffer, 16, 0)) < 0)
            printf("(SERVER) Erro no recv() SERVER\n");
        sscanf(buffer, "%d %d", &command, &state);
        snprintf(response, 15, "%d", command, state);
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
        printf("(SERVER) falha no socker do Servidor\n");

    memset(&servidorAddr, 0, sizeof(servidorAddr));
    servidorAddr.sin_family = AF_INET;
    servidorAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servidorAddr.sin_port = htons(servidorPorta);

    if (bind(servidorSocket, (struct sockaddr *)&servidorAddr, sizeof(servidorAddr)) < 0)
        printf("(SERVER) Falha no Bind\n");

    if (listen(servidorSocket, 10) < 0)
        printf("(SERVER) Falha no Listen\n");

    while (1)
    {
        clienteLength = sizeof(clienteAddr);
        if ((socketCliente = accept(
                 servidorSocket,
                 (struct sockaddr *)&clienteAddr,
                 &clienteLength)) < 0)
            printf("(SERVER) Falha no Accept\n");

        //printf("(SERVER) Conexão do Cliente %s\n", inet_ntoa(clienteAddr.sin_addr));

        TrataClientTCP(socketCliente);
        close(socketCliente);
    }
    close(servidorSocket);
}