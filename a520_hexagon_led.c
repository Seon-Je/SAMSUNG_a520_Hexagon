/****************************************************************************
*
* Copyright 2018 Primesoft All Rights Reserved.
*
* Filename: 231_BlinkLed.c
* Author: enj.park, yr.kim
* Release date: 2018/03/22
* Version: 1.0
*
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define HIGH 1
#define LOW 0
#define INPUT 1
#define OUTPUT 0

int RED_LED = 121; // port : GPIO 0 D2
int GREEN_LED = 123; // port : GPIO 0 D4
int SW_LEFT = 124; // PORT : GPIO 1 D7
int SW_RIGHT = 125; // PORT : GPIO 1 D8


bool digitalPinMode(int pin, int dir) {
    FILE * fd;
    char fName[128];

    // Exporting the pin to be used
    fd = fopen("/sys/class/gpio/export", "w");
    if (fd == NULL) {
        printf("Error: unable to export pin\n");
        return false;
    }
    fprintf(fd, "%d\n", pin);
    fclose(fd);

    // Setting direction of the pin
    sprintf(fName, "/sys/class/gpio/gpio%d/direction", pin);
    fd = fopen(fName, "w");
    if (fd == NULL) {
        printf("Error: can't open pin direction\n");
        return false;
    }
    if (dir == OUTPUT) fprintf(fd, "out\n");
    else fprintf(fd, "in\n");

    fclose(fd);
    return true;
}

bool digitalWrite(int pin, int val) {
    FILE * fd;
    char fName[128] = { 0 };

    // Open pin value file
    sprintf(fName, "/sys/class/gpio/gpio%d/value", pin);
    fd = fopen(fName, "w");
    if(fd == NULL) {
        printf("Error: can't open pin value\n");
        return false;
    }
    if(val == HIGH) fprintf(fd, "1\n");
    else fprintf(fd, "0\n");

    fclose(fd);
    return true;
}

int digitalRead(int pin) {
    FILE * fd;
    char fName[128];
    char val[2];

    // Open pin value file
    sprintf(fName, "/sys/class/gpio/gpio%d/value", pin);
    fd = fopen(fName, "r");
    if (fd == NULL) {
        printf("Error: can't open pin value\n");
        return false;
    }
    fgets(val, 2, fd);
    fclose(fd);
    return atoi(val);
}


int setup()
{
    digitalPinMode(RED_LED, OUTPUT);
    digitalPinMode(GREEN_LED, OUTPUT);
    digitalPinMode(SW_LEFT, INPUT);
    digitalPinMode(SW_RIGHT, INPUT);
    return 0;
}

int main(void)
{
    int LSW_val = 0;
    int RSW_val = 0;

    if (setup() == -1) {exit(1);}
    printf("Left Switch : RED LED , Right Switch : Green LED\n" );

    while(1)
    {
        digitalWrite(RED_LED, digitalRead(SW_LEFT));
        digitalWrite(GREEN_LED, digitalRead(SW_RIGHT));

//        digitalWrite(RED_LED, HIGH);
//        digitalWrite(GREEN_LED, LOW);
//        sleep(1);

//        digitalWrite(RED_LED, LOW);
//        digitalWrite(GREEN_LED, HIGH);
//        sleep(1);
    }
    return 0;
}