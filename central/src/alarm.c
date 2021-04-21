#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "alarm.h"
#include "data.h"

int playing = 0;

void* play() {
  while (playing == 1) {
    system("cd ..; omxplayer alarm.mp3 > /dev/null");
  }

  return NULL;
}

void turn_on_alarm() {
  Data data = get_data();
    playing = 1;
    pthread_t alarm;
    pthread_create(&alarm, NULL, play, NULL);
}

void turn_off_alarm() {
  playing = 0;
}