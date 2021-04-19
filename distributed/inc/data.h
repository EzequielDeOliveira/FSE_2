#ifndef DATA_H_
#define DATA_H_

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
} Data;

void init_data();
Data get_data();
void set_data();

#endif