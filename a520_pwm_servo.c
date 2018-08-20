/****************************************************************************
*
* Copyright 2018 Primesoft All Rights Reserved.
*
* Filename: 353_ServoMotor.c
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

//======== pin number ==========
#define PWM_PIN			0
//==============================

#define EN		1
#define DIS		0

#define INC_DEC		10
#define PERIOD			20000000

static int index = 0;


bool pwmPin(int pin, int period, int duty_cycle, int val) {
	FILE * fd;
	char fName[128];
	
	// Exporting the pin to be used
	fd = fopen("/sys/class/pwm/pwmchip0/export", "w");
	if (!fd) {
		printf("Error: unable to export pin\n");
		return false;
	}
	fprintf(fd, "%d\n", pin);
	fclose(fd);
	
	// Setting period
	sprintf(fName, "/sys/class/pwm/pwmchip0/pwm%d/period", pin);
	fd = fopen(fName, "w");
	if (!fd) {
		printf("Error: can't open pin period\n");
		return false;
	}
	fprintf(fd, "%d\n", period);
	fclose(fd);
	
	// Setting duty cycle
	sprintf(fName, "/sys/class/pwm/pwmchip0/pwm%d/duty_cycle", pin);
	fd = fopen(fName, "w");
	if (!fd) {
		printf("Error: can't open pin duty cycle\n");
		return false;
	}
	fprintf(fd, "%d\n", duty_cycle);
	fclose(fd);
	
	// Setting value
	sprintf(fName, "/sys/class/pwm/pwmchip0/pwm%d/enable", pin);
	fd = fopen(fName, "w");
	if (!fd) {
		printf("Error: can't open pin value\n");
		return false;
	}
	if (val == HIGH) fprintf(fd, "1\n");
	else fprintf(fd, "0\n");
	fclose(fd);
	return true;
}

bool ServoAngle(int pwm_pin, int angle) {
	int duty_cycle;
	duty_cycle = 1500000 + angle * 8889;
	pwmPin(pwm_pin, PERIOD, duty_cycle, EN);
     printf("duty cycle : %d , angle : %d", duty_cycle, angle);
     return true;
}

int main(void)
{
    while(1)
    {
        ServoAngle(PWM_PIN,90);
        sleep(1);

        ServoAngle(PWM_PIN,45);
        sleep(1);

        ServoAngle(PWM_PIN,0);
        sleep(1);

        ServoAngle(PWM_PIN,-45);
        sleep(1);

        ServoAngle(PWM_PIN,-90);
        sleep(1);
    }
    return 0;
}
