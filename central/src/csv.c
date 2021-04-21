#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "data.h"

char buffer[26];

void csv_setup()
{
    FILE *file;

    file = fopen("data.csv", "w");
    fprintf(file, "DATETIME, DEVICE, STATE\n");
    fclose(file);
}

void get_current_time()
{
    time_t timer;
    struct tm *tm_info;

    timer = time(NULL);
    tm_info = localtime(&timer);

    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
}

void write_csv(int device, int state)
{
    FILE *file;
    file = fopen("data.csv", "a");
    char *stateText = state == 1 ? "ON" : "OFF";

    get_current_time();

    if (device == LAMP_1)
        fprintf(file, "%s,%s,%s\n", buffer, "Lâmpada 01 (Cozinha)", stateText);
    else if (device == LAMP_2)
        fprintf(file, "%s,%s,%s\n", buffer, "Lâmpada 02 (Sala)", stateText);
    else if (device == LAMP_3)
        fprintf(file, "%s,%s,%s\n", buffer, "Lâmpada 03 (Quarto 01)", stateText);
    else if (device == LAMP_4)
        fprintf(file, "%s,%s,%s\n", buffer, "Lâmpada 04 (Quarto 02)", stateText);
    else if (device == AIR_1)
        fprintf(file, "%s,%s,%s\n", buffer, "Ar-Condicionado 01 (Quarto 01)", stateText);
    else if (device == AIR_2)
        fprintf(file, "%s,%s,%s\n", buffer, "Ar-Condicionado 02 (Quarto 02)", stateText);
    else if (device == PRESENCE_SENSOR_1)
        fprintf(file, "%s,%s,%s\n", buffer, "Sensor de Presença 01 (Sala)", stateText);
    else if (device == PRESENCE_SENSOR_2)
        fprintf(file, "%s,%s,%s\n", buffer, "Sensor de Presença 02 (Cozinha)", stateText);
    else if (device == OPENING_SENSOR_1)
        fprintf(file, "%s,%s,%s\n", buffer, "Sensor Abertura 01 (Porta Cozinha)", stateText);
    else if (device == OPENING_SENSOR_2)
        fprintf(file, "%s,%s,%s\n", buffer, "Sensor Abertura 02 (Janela Cozinha)", stateText);
    else if (device == OPENING_SENSOR_3)
        fprintf(file, "%s,%s,%s\n", buffer, "Sensor Abertura 03 (Porta Sala)", stateText);
    else if (device == OPENING_SENSOR_4)
        fprintf(file, "%s,%s,%s\n", buffer, "Sensor Abertura 04 (Janela Sala)", stateText);
    else if (device == OPENING_SENSOR_5)
        fprintf(file, "%s,%s,%s\n", buffer, "Sensor Abertura 05 (Janela Quarto 01)", stateText);
    else if (device == OPENING_SENSOR_6)
        fprintf(file, "%s,%s,%s\n", buffer, "Sensor Abertura 06 (Janela Quarto 02)", stateText);
    else if (device == ALARM_ENABLED)
        fprintf(file, "%s,%s,%s\n", buffer, "Alarme", stateText);
    else if (device == ALARM_PLAYING)
        fprintf(file, "%s,%s,%s\n", buffer, "Alarme Disparado", stateText);

    fclose(file);
}