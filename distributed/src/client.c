#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "data.h"
#include "quit.h"

#define LEN 16

#define IP_Server "192.168.0.53"
#define Port_Server 10015

void send_command(int command, int state)
{
    int clientSocket;
    struct sockaddr_in serverAddr;
    char message[16];
    char buffer[16];
    unsigned int messageLength;

    int bytesRecebidos;
    int totalBytesRecebidos;

    sprintf(message, "%d %d", command, state);

    if ((clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("Erro no socket()");
        finishWithError(0);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(IP_Server);
    serverAddr.sin_port = htons(Port_Server);

    if (connect(clientSocket, (struct sockaddr *)&serverAddr,
                sizeof(serverAddr)) < 0)
    {
        printf("Erro no connect()\n");
        finishWithError(0);
    }

    messageLength = strlen(message);

    if (send(clientSocket, message, messageLength, 0) != messageLength)
    {
        printf("Erro no envio: numero de bytes enviados diferente do esperado\n");
        finishWithError(0);
    }

    totalBytesRecebidos = recv(clientSocket, buffer, 16 - 1, 0);

    if (totalBytesRecebidos < 1)
    {
        printf("Não recebeu o total de bytes enviados\n");
        finishWithError(0);
    }

    printf("%s\n", buffer);

    close(clientSocket);
}