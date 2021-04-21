#include <stdlib.h>
#include "data.h"
#include "gpio.h"
#include "client.h"

int device_is_valide(int device)
{
    if (device == LAMP_1 || device == LAMP_2 || device == LAMP_3 || device == LAMP_4 || device == AIR_1 || device == AIR_2)
        return 1;
    return 0;
}

void handle_presence_1()
{
    int state = digitalRead(PRESENCE_SENSOR_1) ? 1: 0;
    printf("Sensor Detected \n");
    send_command(PRESENCE_SENSOR_1, state);
}

void handle_presence_2()
{
    int state = digitalRead(PRESENCE_SENSOR_2);
    printf("Sensor Detected \n");
    send_command(PRESENCE_SENSOR_2, state);
}

void handle_opening_1()
{
    int state = digitalRead(OPENING_SENSOR_1);
    printf("Sensor Detected \n");
    send_command(OPENING_SENSOR_1, state);
}

void handle_opening_2()
{
    int state = digitalRead(OPENING_SENSOR_2);
    printf("Sensor Detected \n");
    send_command(OPENING_SENSOR_2, state);
}

void handle_opening_3()
{
    int state = digitalRead(OPENING_SENSOR_3);
    printf("Sensor Detected \n");
    send_command(OPENING_SENSOR_3, state);
}

void handle_opening_4()
{
    int state = digitalRead(OPENING_SENSOR_4);
    printf("Sensor Detected \n");
    send_command(OPENING_SENSOR_4, state);
}

void handle_opening_5()
{
    int state = digitalRead(OPENING_SENSOR_5);
    printf("Sensor Detected \n");
    send_command(OPENING_SENSOR_5, state);
}

void handle_opening_6()
{
    int state = digitalRead(OPENING_SENSOR_6);
    printf("Sensor Detected \n");
    send_command(OPENING_SENSOR_6, state);
}

void gpio_setup()
{
    wiringPiSetup();

    pinMode(PRESENCE_SENSOR_1, OUTPUT);
    wiringPiISR(PRESENCE_SENSOR_1, INT_EDGE_BOTH, &handle_presence_1);

    pinMode(PRESENCE_SENSOR_2, OUTPUT);
    wiringPiISR(PRESENCE_SENSOR_2, INT_EDGE_BOTH, &handle_presence_2);

    pinMode(OPENING_SENSOR_1, OUTPUT);
    wiringPiISR(OPENING_SENSOR_1, INT_EDGE_BOTH, &handle_opening_1);

    pinMode(OPENING_SENSOR_2, OUTPUT);
    wiringPiISR(OPENING_SENSOR_2, INT_EDGE_BOTH, &handle_opening_2);

    pinMode(OPENING_SENSOR_3, OUTPUT);
    wiringPiISR(OPENING_SENSOR_3, INT_EDGE_BOTH, &handle_opening_3);

    pinMode(OPENING_SENSOR_4, OUTPUT);
    wiringPiISR(OPENING_SENSOR_4, INT_EDGE_BOTH, &handle_opening_4);

    pinMode(OPENING_SENSOR_5, OUTPUT);
    wiringPiISR(OPENING_SENSOR_5, INT_EDGE_BOTH, &handle_opening_5);

    pinMode(OPENING_SENSOR_6, OUTPUT);
    wiringPiISR(OPENING_SENSOR_6, INT_EDGE_BOTH, &handle_opening_6);
}

void change_state(int device, int state)
{
    if(device_is_valide(device))
    {
        pinMode(device, OUTPUT);
        digitalWrite(device, state);
    }
}

void turn_off_all()
{
    change_state(LAMP_1, LOW);
    change_state(LAMP_2, LOW);
    change_state(LAMP_3, LOW);
    change_state(LAMP_4, LOW);
    change_state(AIR_1, LOW);
    change_state(AIR_2, LOW);
}