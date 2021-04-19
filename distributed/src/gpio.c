#include "gpio.h"

void bcm2835_setup()
{
    if (!bcm2835_init())
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

int device_is_valide(int device)
{
    if (device == LAMP_1 || device == LAMP_2 || device == LAMP_3 || device == LAMP_4 || device == AIR_1 || device == AIR_2)
        return 1;
    return 0;
}

void turn_on(int device)
{
    if (device_is_valide(device))
        bcm2835_gpio_write(device, 1);
}

void turn_off(int device)
{
    if (device_is_valide(device))
        bcm2835_gpio_write(device, 0);
}

void turn_off_all()
{
    bcm2835_gpio_write(LAMP_1, 0);
    bcm2835_gpio_write(LAMP_2, 0);
    bcm2835_gpio_write(LAMP_3, 0);
    bcm2835_gpio_write(LAMP_4, 0);
    bcm2835_gpio_write(AIR_1, 0);
    bcm2835_gpio_write(AIR_2, 0);
}

void interrupcao()
{
    turn_off_all();
    bcm2835_close();
    exit(0);
}