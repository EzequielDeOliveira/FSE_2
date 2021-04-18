#ifndef DATA_H_
#define DATA_H_

#define LAMP_1 17
#define LAMP_2 18
#define LAMP_3 27
#define LAMP_4 22
#define AIR_1 13
#define AIR_2 19

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
} Data;

void init_data();
Data get_data();
void set_data();

#endif