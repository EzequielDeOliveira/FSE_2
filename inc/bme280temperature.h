#ifndef BME280_TEMPERATURE_H
#define BME280_TEMPERATURE_H

float bme280_temperature(float *temperature, float *humidity);
void bme280_setup();
void close_bme280();

#endif