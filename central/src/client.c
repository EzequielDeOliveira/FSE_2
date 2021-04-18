#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "data.h"

#define LEN 16

char *IP_Server = "192.168.0.52";
unsigned short Port_Server = 10115;

void getbme280(int command)
{
    int clienteSocket;
    struct sockaddr_in servidorAddr;
    unsigned short servidorPorta;
    char *IP_Servidor;
    char *mensagem;
    char buffer[16];
    unsigned int tamanhoMensagem;

    int bytesRecebidos;
    int totalBytesRecebidos;

    IP_Servidor = IP_Server;
    servidorPorta = Port_Server;
    mensagem = "0";

    if ((clienteSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        printf("Erro no socket()");

    memset(&servidorAddr, 0, sizeof(servidorAddr));
    servidorAddr.sin_family = AF_INET;
    servidorAddr.sin_addr.s_addr = inet_addr(IP_Servidor);
    servidorAddr.sin_port = htons(servidorPorta);

    if (connect(clienteSocket, (struct sockaddr *)&servidorAddr,
                sizeof(servidorAddr)) < 0)
        printf("Erro no connect()\n");

    tamanhoMensagem = strlen(mensagem);

    if (send(clienteSocket, mensagem, tamanhoMensagem, 0) != tamanhoMensagem)
        printf("Erro no envio: numero de bytes enviados diferente do esperado\n");

    totalBytesRecebidos = recv(clienteSocket, buffer, 16 - 1, 0);

    if (totalBytesRecebidos < 1)
    {
        printf("Não recebeu o total de bytes enviados\n");
    }

    buffer[totalBytesRecebidos] = '\0';

    float temperature;
    float humidity;
    int command_received;
    sscanf(buffer, "%d %f %f", &command_received, &temperature, &humidity);
    printf("%s\n%d %f %f\n", buffer, command_received, temperature, humidity);

    close(clienteSocket);
}