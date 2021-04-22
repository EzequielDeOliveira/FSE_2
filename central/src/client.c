#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "data.h"
#include "dashboard.h"
#include "quit.h"

#define LEN 16

#define IP_Server "192.168.0.52"
#define Port_Server 10115

void send_command(int command)
{
    int clientSocket;
    struct sockaddr_in serverAddr;
    char message[LEN];
    char buffer[LEN];
    unsigned int messageLength;

    int totalBytesReceived;

    sprintf(message, "%d", command);

    if ((clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("(CLIENT) Erro no socket()");
        finishWithError(0);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(IP_Server);
    serverAddr.sin_port = htons(Port_Server);

    if (connect(clientSocket, (struct sockaddr *)&serverAddr,
                sizeof(serverAddr)) < 0)
    {
        printf("(CLIENT) Erro no connect()\n");
        finishWithError(0);
    }

    messageLength = strlen(message);

    if (send(clientSocket, message, messageLength, 0) != messageLength)
    {
        printf("(CLIENT) Erro no envio: numero de bytes enviados diferente do esperado\n");
        finishWithError(0);
    }

    totalBytesReceived = recv(clientSocket, buffer, LEN - 1, 0);

    if (totalBytesReceived < 1)
    {
        printf("(CLIENT) Não recebeu o total de bytes enviados\n");
        finishWithError(0);
    }

    if (command < 0)
    {
        float temperature;
        float humidity;
        int command_received;
        sscanf(buffer, "%d %f %f", &command_received, &temperature, &humidity);
        if (command == command_received)
        {
            Data data = get_data();
            data.temperature = temperature;
            data.humidity = humidity;
            set_data(data);
        }
    }
    close(clientSocket);
}