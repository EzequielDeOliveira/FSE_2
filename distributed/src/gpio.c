#include <stdlib.h>
#include "gpio.h"
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
    send_command(PRESENCE_SENSOR_1);
}

void handle_presence_2()
{
    send_command(PRESENCE_SENSOR_2);
}

void handle_opening_1()
{
    send_command(OPENING_SENSOR_1);
}

void handle_opening_2()
{
    send_command(OPENING_SENSOR_2);
}

void handle_opening_3()
{
    send_command(OPENING_SENSOR_3);
}

void handle_opening_4()
{
    send_command(OPENING_SENSOR_4);
}

void handle_opening_5()
{
    send_command(OPENING_SENSOR_5);
}

void handle_opening_6()
{
    send_command(OPENING_SENSOR_6);
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

void interrupcao()
{
    turn_off_all();
    exit(0);
}