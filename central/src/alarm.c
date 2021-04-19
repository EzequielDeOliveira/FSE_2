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

  if (data.alarm == 1) {
    data.playing = 1;
    playing = 1;
    pthread_t alarm;
    pthread_create(&alarm, NULL, play, NULL);
    set_data(data);
  }
}

void turn_off_alarm() {
  Data data = get_data();
  playing = 0;
  data.playing = 0;
 set_data(data); 
}