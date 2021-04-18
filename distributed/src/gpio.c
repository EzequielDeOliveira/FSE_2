#include "gpio.h"

void bcm2835_setup() {
    if(!bcm2835_init())
        exit(0);

    // Outputs
    bcm2835_gpio_fsel(LAMP_1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LAMP_2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LAMP_3, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LAMP_4, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(AIR_1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(AIR_2, BCM2835_GPIO_FSEL_OUTP);

    // Inputs
    bcm2835_gpio_fsel(PRESENCE_SENSOR_1, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(PRESENCE_SENSOR_1, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_fsel(PRESENCE_SENSOR_2, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(PRESENCE_SENSOR_2, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_fsel(OPENING_SENSOR_1, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(OPENING_SENSOR_1, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_fsel(OPENING_SENSOR_2, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(OPENING_SENSOR_2, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_fsel(OPENING_SENSOR_3, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(OPENING_SENSOR_3, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_fsel(OPENING_SENSOR_4, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(OPENING_SENSOR_4, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_fsel(OPENING_SENSOR_5, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(OPENING_SENSOR_5, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_fsel(OPENING_SENSOR_6, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(OPENING_SENSOR_6, BCM2835_GPIO_PUD_UP);    
}

void ligar_lampada(int comando) {
    bcm2835_gpio_write(LAMP_1, comando);
    bcm2835_gpio_write(LAMP_2, comando);
    bcm2835_gpio_write(LAMP_3, comando);
    bcm2835_gpio_write(LAMP_4, comando);
    bcm2835_gpio_write(AIR_1, comando);
    bcm2835_gpio_write(AIR_2, comando);
}

void interrupcao() {
    ligar_lampada(0);
    bcm2835_close();
    exit(0);
}