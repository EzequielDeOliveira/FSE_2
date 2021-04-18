#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void TrataClientTCP(int socketClient) {
    char buffer[16];
    int tamanhoRecebido;

    if((tamanhoRecebido = recv(socketClient, buffer, 16, 0)) < 0)
        printf("Erro no recv()\n");

    while(tamanhoRecebido > 0) {
        if(send(socketClient, buffer,tamanhoRecebido, 0) != tamanhoRecebido)
            printf("Erro no envio - send()\n");

        if((tamanhoRecebido = recv(socketClient, buffer, 16, 0)) < 0)
            printf("Erro no recv()\n");
    }   
}  

void receive_messages() {
    int servidorSocket;
    int socketCliente;
    struct sockaddr_in servidorAddr;
    struct sockaddr_in clienteAddr;
    unsigned short servidorPorta;
    unsigned int clienteLength;

    servidorPorta = 10115;

    if((servidorSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        printf("falha no socker do Servidor\n");

    memset(&servidorAddr, 0, sizeof(servidorAddr));
    servidorAddr.sin_family = AF_INET;
    servidorAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servidorAddr.sin_port = htons(servidorPorta);

    if(bind(servidorSocket, (struct sockaddr *) &servidorAddr, sizeof(servidorAddr)) < 0)
        printf("Falha no Bind\n");

    if(listen(servidorSocket, 10) < 0)
        printf("Falha no Listen\n");

    while(1) {
        clienteLength = sizeof(clienteAddr);
        if((socketCliente = accept(
            servidorSocket,
            (struct sockaddr *) &clienteAddr,
            &clienteLength)) < 0)
                printf("Falha no Accept\n");

        printf("Conexão do Cliente %s\n", inet_ntoa(clienteAddr.sin_addr));

        TrataClientTCP(socketCliente);
        close(socketCliente);
    }
    close(servidorSocket);
}