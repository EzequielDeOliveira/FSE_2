#include "gpio.h"

void bcm2835_setup() {
    if(!bcm2835_init())
        exit(0);

    // Outputs
    bcm2835_gpio_fsel(LAMPADA_1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LAMPADA_2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LAMPADA_3, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LAMPADA_4, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(AR_1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(AR_2, BCM2835_GPIO_FSEL_OUTP);

    // Inputs
    bcm2835_gpio_fsel(SENSOR_PRESENCA_1, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(SENSOR_PRESENCA_1, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_fsel(SENSOR_PRESENCA_2, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(SENSOR_PRESENCA_2, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_fsel(SENSOR_ABERTURA_1, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(SENSOR_ABERTURA_1, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_fsel(SENSOR_ABERTURA_2, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(SENSOR_ABERTURA_2, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_fsel(SENSOR_ABERTURA_3, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(SENSOR_ABERTURA_3, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_fsel(SENSOR_ABERTURA_4, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(SENSOR_ABERTURA_4, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_fsel(SENSOR_ABERTURA_5, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(SENSOR_ABERTURA_5, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_fsel(SENSOR_ABERTURA_6, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(SENSOR_ABERTURA_6, BCM2835_GPIO_PUD_UP);    
}

void ligar_lampada(int comando) {
    bcm2835_gpio_write(LAMPADA_1, comando);
    bcm2835_gpio_write(LAMPADA_2, comando);
    bcm2835_gpio_write(LAMPADA_3, comando);
    bcm2835_gpio_write(LAMPADA_4, comando);
    bcm2835_gpio_write(AR_1, comando);
    bcm2835_gpio_write(AR_2, comando);
}

void interrupcao(int sinal) {
    ligar_lampada(0);
    bcm2835_close();
    exit(0);
}