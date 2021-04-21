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

char *IP_Server = "192.168.0.4";
unsigned short Port_Server = 10115;

void send_command(int command)
{
    int clienteSocket;
    struct sockaddr_in servidorAddr;
    unsigned short servidorPorta;
    char *IP_Servidor;
    char mensagem[16];
    char buffer[16];
    unsigned int tamanhoMensagem;

    int bytesRecebidos;
    int totalBytesRecebidos;

    IP_Servidor = "192.168.0.4";
    servidorPorta = 10115;
    sprintf(mensagem, "%d", command);

    if ((clienteSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("(CLIENT) Erro no socket()");
        finishWithError(0);
    }

    memset(&servidorAddr, 0, sizeof(servidorAddr));
    servidorAddr.sin_family = AF_INET;
    servidorAddr.sin_addr.s_addr = inet_addr(IP_Servidor);
    servidorAddr.sin_port = htons(servidorPorta);

    if (connect(clienteSocket, (struct sockaddr *)&servidorAddr,
                sizeof(servidorAddr)) < 0)
    {
        printf("(CLIENT) Erro no connect()\n");
        finishWithError(0);
    }

    tamanhoMensagem = strlen(mensagem);

    if (send(clienteSocket, mensagem, tamanhoMensagem, 0) != tamanhoMensagem)
    {
        printf("(CLIENT) Erro no envio: numero de bytes enviados diferente do esperado\n");
        finishWithError(0);
    }

    totalBytesRecebidos = recv(clienteSocket, buffer, 16 - 1, 0);

    if (totalBytesRecebidos < 1)
    {
        printf("(CLIENT) Não recebeu o total de bytes enviados\n");
        finishWithError(0);
    }

    if (command < 0)
    {
        float temperature;
        float humidity;
        int command_received;
        //printf("(CLIENT) %s\n", buffer);
        sscanf(buffer, "%d %f %f", &command_received, &temperature, &humidity);
        if (command == command_received)
        {
            Data data = get_data();
            data.temperature = temperature;
            data.humidity = humidity;
            set_data(data);
        }
        //printf("(CLIENT) %d %.2f %.2f", command_received, temperature, humidity);
        //render_info_win(temperature, humidity);
    }
    close(clienteSocket);
}