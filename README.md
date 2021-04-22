## Dados

| Aluno | Matrícula |
| --- | --- |
| Ezequiel De Oliveira Dos Reis | 16/0119316 |

## Dependências

* [WiringPi](http://wiringpi.com/)
* [ncurses](https://invisible-island.net/ncurses/announce.html)

## Execução

Para executar o programa basta clonar o repositório presente, entrar no diretório do repositório e então entrar na pasta do servidor distribuido e executar:

``` bash
# Para compilar o projeto
$ make

# Para executar o projeto
$ make run
```

Logo em seguida entre na pasta do servidor central e executar:


``` bash
# Para compilar o projeto
$ make

# Para executar o projeto
$ make run
```

## Instruções

- Para se movimentar no menu utiliza as setas ***KEY_UP*** e ***KEY_DOWN***
- Para ativar ou desativar um item da lista use a tecla ***SPACE***
- Para ativar o alarme é preciso desativar todos os sensores
- Quando um sensor é ativado, é mostrado em amarelo na tela
- O sensor distribuido apenas mostra que a comunicação foi feita
- A comunicação entre os servidores é baseada em sockets, os IPs e PORTAS estão definidas nos arquivos **server** e **client** dos dois servidores

## Interface 

![image](https://user-images.githubusercontent.com/37127457/115646566-c378e000-a2f8-11eb-9038-3d719bc71c5c.png)

![image](https://user-images.githubusercontent.com/37127457/115646592-d2f82900-a2f8-11eb-9dda-cbd15b68a4c6.png)

![image](https://user-images.githubusercontent.com/37127457/115646612-e1464500-a2f8-11eb-905d-40a99b75943e.png)

![image](https://user-images.githubusercontent.com/37127457/115646662-ffac4080-a2f8-11eb-8558-2dfc897286d6.png)


## Referências
 
- [Driver da Bosh para o sensor BME280](https://github.com/BoschSensortec/BME280_driver)  
- [Biblioteca BCM2835 - GPIO](http://www.airspayce.com/mikem/bcm2835/)  
- [Biblioteca WiringPi GPIO](http://wiringpi.com)  

