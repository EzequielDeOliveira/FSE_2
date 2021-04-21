#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "alarm.h"
#include "data.h"

int playing = 0;
pthread_t alarm;

void *play()
{
  while (playing == 1)
  {
    system("cd ..; omxplayer alarm.mp3 > /dev/null");
  }

  return NULL;
}

void turn_on_alarm()
{
  Data data = get_data();
  playing = 1;
  pthread_create(&alarm, NULL, play, NULL);
}

void finish_alarm()
{
  pthread_cancel(alarm);
}

void turn_off_alarm()
{
  playing = 0;
}