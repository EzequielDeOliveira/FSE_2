#ifndef DATA_H_
#define DATA_H_

#define LAMP_1 0 
#define LAMP_2 1
#define LAMP_3 2
#define LAMP_4 3
#define AIR_1 23
#define AIR_2 24
#define PRESENCE_SENSOR_1 6
#define PRESENCE_SENSOR_2 25
#define OPENING_SENSOR_1 21
#define OPENING_SENSOR_2 22
#define OPENING_SENSOR_3 26
#define OPENING_SENSOR_4 27
#define OPENING_SENSOR_5 28
#define OPENING_SENSOR_6 29
#define ALARM_ENABLED 10
#define ALARM_PLAYIMG 11

typedef struct
{
    int lamp1;
    int lamp2;
    int lamp3;
    int lamp4;
    int air1;
    int air2;
    int openings1;
    int openings2;
    int openings3;
    int openings4;
    int openings5;
    int openings6;
    int presences1;
    int presences2;
    float humidity;
    float temperature;
    int alarm;
    int playing;
} Data;

void init_data();
Data get_data();
void set_data();

#endif