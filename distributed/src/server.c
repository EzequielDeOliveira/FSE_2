#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define serverPort 10115

void TrataClientTCP(int socketClient)
{
    char request[16];
    char response[16];
    int tamanhoRecebido;

    if ((tamanhoRecebido = recv(socketClient, request, 16, 0)) < 0)
        printf("Erro no recv()\n");

    while (tamanhoRecebido > 0)
    {

        request[16] = '\0';
        printf("%d", atoi(request));

/* 
        sscanf(request, "%d %lf %lf", &command_received, &temperature, &humidity);

        if(send(socketClient, response,tamanhoRecebido, 0) != tamanhoRecebido)
            printf("Erro no envio - send()\n");

        if((tamanhoRecebido = recv(socketClient, request, 16, 0)) < 0)
            printf("Erro no recv()\n");
   */  }
}

void receive_messages(int argc, char *argv[])
{
    int servidorSocket;
    int socketCliente;
    struct sockaddr_in servidorAddr;
    struct sockaddr_in clienteAddr;
    unsigned int clienteLength;

    if ((servidorSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        printf("falha no socker do Servidor\n");

    memset(&servidorAddr, 0, sizeof(servidorAddr));
    servidorAddr.sin_family = AF_INET;
    servidorAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servidorAddr.sin_port = htons(serverPort);

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