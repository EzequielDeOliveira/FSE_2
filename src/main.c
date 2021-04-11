#include "bme280temperature.h"

int main(int argc, char *argv[]) {
    
    int temperature = 0, humidity = 0;
    
    while(1){
        bme280_temperature(&temperature, &humidity);
        printf("%d %d\n", temperature, humidity);
    }

    return 0;
}