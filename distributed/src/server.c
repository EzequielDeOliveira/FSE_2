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

void TrataClientTCP(int socketClient)
{
    char buffer[16];
    char response[16];
    int tamanhoRecebido;
    int command;
    struct bme280_data data = bme280_read();

    if ((tamanhoRecebido = recv(socketClient, buffer, 16, 0)) < 0)
    {
        printf("Erro no recv()\n");
        finishWithError(0);
    }
    sscanf(buffer, "%d", &command);
    handleDevices(command);
    data = bme280_read();
    snprintf(response, 15, "%d %.2f %.2f", command, data.temperature, data.humidity);

    while (tamanhoRecebido > 0)
    {
        if (send(socketClient, response, 16 - 1, 0) != 15)
        {
            printf("Erro no envio - sends()\n");
            finishWithError(0);
        }

        if ((tamanhoRecebido = recv(socketClient, buffer, 16, 0)) < 0)
        {
            printf("Erro no recv()\n");
            finishWithError(0);
        }
        sscanf(buffer, "%d", &command);
        data = bme280_read();
        snprintf(response, 15, "%d %.2f %.2f", command, data.temperature, data.humidity);
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

    servidorPorta = 10115;

    if ((servidorSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("falha no socker do Servidor\n");
        finishWithError(0);
    }

    memset(&servidorAddr, 0, sizeof(servidorAddr));
    servidorAddr.sin_family = AF_INET;
    servidorAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servidorAddr.sin_port = htons(servidorPorta);

    if (bind(servidorSocket, (struct sockaddr *)&servidorAddr, sizeof(servidorAddr)) < 0)
    {
        printf("Falha no Bind\n");
        finishWithError(0);
    }

    if (listen(servidorSocket, 10) < 0)
    {
        printf("Falha no Listen\n");
        finishWithError(0);
    }

    while (1)
    {
        clienteLength = sizeof(clienteAddr);
        if ((socketCliente = accept(
                 servidorSocket,
                 (struct sockaddr *)&clienteAddr,
                 &clienteLength)) < 0)
        {
            printf("Falha no Accept\n");
            finishWithError(0);
        }

        //printf("Conexão do Cliente %s\n", inet_ntoa(clienteAddr.sin_addr));

        TrataClientTCP(socketCliente);
        close(socketCliente);
    }
    close(servidorSocket);
}