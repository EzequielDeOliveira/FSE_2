#include "bme280temperature.h"
#include "bcm2835.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    
    int temperature = 0, humidity = 0;
    
    while(1){
        bme280_temperature(&temperature, &humidity);
        printf("%d %d\n", temperature, humidity);
    }

    return 0;
}