#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "data.h"

#define LEN 16

char *IP_Server = "192.168.0.52";
char *Port_Server = "10115";

void getbme280(int command)
{
    int clienteSocket;
    struct sockaddr_in servidorAddr;
    unsigned int tamanhoMensagem;
    unsigned int totalBytesRecebidos;
    unsigned int bytesRecebidos;
    char buffer[LEN];
    char response[LEN];

    char tamanhoMensagem = snprintf(buffer, 6, "%d", command);

    if ((clienteSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        printf("Erro no socket()");

        if(send(clienteSocket, buffer, tamanhoMensagem, 0) != tamanhoMensagem)
        		printf("Erro no envio: numero de bytes enviados diferente do esperado\n");

    memset(&servidorAddr, 0, sizeof(servidorAddr));
    servidorAddr.sin_family = AF_INET;
    servidorAddr.sin_addr.s_addr = inet_addr(IP_Server);
    servidorAddr.sin_port = htons(Port_Server);

    if(connect(clienteSocket, (struct sockaddr *) &servidorAddr, 
							sizeof(servidorAddr)) < 0)
        printf("Erro no connect()\n");

    
    if(send(clienteSocket, buffer, tamanhoMensagem, 0) != tamanhoMensagem)
        		printf("Erro no envio: numero de bytes enviados diferente do esperado\n");

    bytesRecebidos = recv(clienteSocket, response, LEN-1, 0);
    if(bytesRecebidos < 0)
        printf("Não recebeu o total de bytes enviados\n");

    response[15] = '\0';


    float temperature;
    float humidity;
    int command_received;
    sscanf(response, "%d %lf %lf", &command_received, &temperature, &humidity);

    close(clienteSocket);
    printf("%d %lf %lf\n", &command_received, &temperature, &humidity);
}