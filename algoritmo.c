#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#include <softPwm.h>

//SerboMotor sensor arriba

#define SENSOR_ARRIBA_IZQUIERDA 2
#define SENSOR_ARRIBA_DERECHA 3

#define DIRECCION_PASO 1
#define PASO 4

#define DIRECCION_PASO_IZQUIERDA HIGH
#define DIRECCION_PASO_DERECHA LOW


#define TRIGER_ARRIBA_IZQUIERDA 370
#define TRIGER_ARRIBA_DERECHA 370

#define N_PASO 80
#define DELAY 1

//Ruedas sensor abajo

#define CHAN_CONFIG_SINGLE 8
#define CHAN_SPI 0

#define SENSOR_ABAJO_IZQUIERDA 1
#define SENSOR_ABAJO_DERECHA 0

#define PWM1 3//Izquierda
#define PWM2 0//Derecha

#define PWM1_RECTO 6//Izquierda
#define PWM2_RECTO 24//Derecha

#define TRIGER_ABAJO_IZQUIERDA 850
#define TRIGER_ABAJO_DERECHA 850

static int myFd;


void spiSetup(int spiChannel) {
    if ((myFd = wiringPiSPISetup(spiChannel, 1000000)) < 0) {
        fprintf(stderr, "Can't open the SPI bus: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

int myAnalogRead(int spiChannel, int channelConfig, int analogChannel) {
    if(analogChannel < 0 || analogChannel > 7)
        return -1;
    unsigned char buffer[3] = {1}; // start bit
    buffer[1] = (channelConfig + analogChannel) << 4;
    wiringPiSPIDataRW(spiChannel, buffer, 3);
    return ((buffer[1] & 3) << 8) + buffer[2]; // get last 10 bits
}

int main(int argc, char *argv[]) {

    int i;

    wiringPiSetup();

    //SerboMotor sensor arriba
    pinMode (DIRECCION_PASO, OUTPUT);
    pinMode (PASO, OUTPUT) ;
    //Ruedas sensor abajo
    spiSetup(CHAN_SPI);

    softPwmCreate (PWM1, 100, 100);
    softPwmCreate (PWM2, 100, 100);
    //softPwmWrite (PWM1, PWM1_RECTO);
    //softPwmWrite (PWM2, PWM2_RECTO);

    int encontrando = 1;
	while ((myAnalogRead(CHAN_SPI, CHAN_CONFIG_SINGLE, SENSOR_ARRIBA_DERECHA)>TRIGER_ARRIBA_DERECHA)||(myAnalogRead(CHAN_SPI, CHAN_CONFIG_SINGLE, SENSOR_ARRIBA_IZQUIERDA)>TRIGER_ARRIBA_IZQUIERDA)){}
    softPwmWrite (PWM1, PWM1_RECTO);
    softPwmWrite (PWM2, PWM2_RECTO);

while(encontrando){
		/*for(i = 0; i < 4; i++) {
	            printf("Canal %d = %d", i + 1, myAnalogRead(CHAN_SPI, CHAN_CONFIG_SINGLE, i));
		}*/
        if (myAnalogRead(CHAN_SPI, CHAN_CONFIG_SINGLE, SENSOR_ABAJO_IZQUIERDA)<TRIGER_ABAJO_IZQUIERDA){
            //softPwmWrite (PWM1, 100);
		softPwmWrite (PWM2, 100);
            while (myAnalogRead(CHAN_SPI, CHAN_CONFIG_SINGLE, SENSOR_ABAJO_IZQUIERDA)<TRIGER_ABAJO_IZQUIERDA){}
		 delay (170);
            //softPwmWrite (PWM1, PWM1_RECTO);
		softPwmWrite (PWM2, PWM2_RECTO);
        }
        if (myAnalogRead(CHAN_SPI, CHAN_CONFIG_SINGLE, SENSOR_ABAJO_DERECHA)<TRIGER_ABAJO_DERECHA){
            //softPwmWrite (PWM2, 100);
		softPwmWrite (PWM1, 100);
            while (myAnalogRead(CHAN_SPI, CHAN_CONFIG_SINGLE, SENSOR_ABAJO_DERECHA)<TRIGER_ABAJO_DERECHA){}
	            delay(170);
		//softPwmWrite (PWM2, PWM2_RECTO);
		softPwmWrite (PWM1, PWM1_RECTO);
        }
	
        if(myAnalogRead(CHAN_SPI, CHAN_CONFIG_SINGLE, SENSOR_ARRIBA_DERECHA)>TRIGER_ARRIBA_DERECHA){
            digitalWrite (DIRECCION_PASO, DIRECCION_PASO_DERECHA);
		delay(200);
            softPwmWrite (PWM1, 100);
            softPwmWrite (PWM2, 100);
            for (i=0;i<N_PASO;i++){
                digitalWrite (PASO, HIGH);
                delay (DELAY) ;
                digitalWrite (PASO, LOW);
                delay (DELAY);
            }
	digitalWrite (DIRECCION_PASO, DIRECCION_PASO_IZQUIERDA);
		delay(100);
		for(i=0;i<N_PASO/3;i++){
                digitalWrite (PASO, HIGH);
                delay (DELAY) ;
                digitalWrite (PASO, LOW);
                delay (DELAY);
            }
        digitalWrite (DIRECCION_PASO, DIRECCION_PASO_DERECHA);
                delay(100);
                for(i=0;i<N_PASO/3;i++){
                digitalWrite (PASO, HIGH);
                delay (DELAY) ;
                digitalWrite (PASO, LOW);
                delay (DELAY);
            }
        digitalWrite (DIRECCION_PASO, DIRECCION_PASO_IZQUIERDA);
                delay(100);
                for(i=0;i<N_PASO/3;i++){
                digitalWrite (PASO, HIGH);
                delay (DELAY) ;
                digitalWrite (PASO, LOW);
                delay (DELAY);
            }

            encontrando = 0;
        }
        if(myAnalogRead(CHAN_SPI, CHAN_CONFIG_SINGLE, SENSOR_ARRIBA_IZQUIERDA)>TRIGER_ARRIBA_IZQUIERDA){
            digitalWrite (DIRECCION_PASO, DIRECCION_PASO_IZQUIERDA);
		 delay(200);
            softPwmWrite (PWM1, 100);
            softPwmWrite (PWM2, 100);
            for (i=0;i<N_PASO;i++){
                digitalWrite (PASO, HIGH);
                delay (DELAY) ;
                digitalWrite (PASO, LOW);
                delay (DELAY);
            }
        digitalWrite (DIRECCION_PASO, DIRECCION_PASO_DERECHA);
                delay(100);
                for(i=0;i<N_PASO/3;i++){
                digitalWrite (PASO, HIGH);
                delay (DELAY) ;
                digitalWrite (PASO, LOW);
                delay (DELAY);
            }
        digitalWrite (DIRECCION_PASO, DIRECCION_PASO_IZQUIERDA);
                delay(100);
                for(i=0;i<N_PASO/3;i++){
                digitalWrite (PASO, HIGH);
                delay (DELAY) ;
                digitalWrite (PASO, LOW);
                delay (DELAY);
            }
        digitalWrite (DIRECCION_PASO, DIRECCION_PASO_DERECHA);
                delay(100);
                for(i=0;i<N_PASO/3;i++){
                digitalWrite (PASO, HIGH);
                delay (DELAY) ;
                digitalWrite (PASO, LOW);
                delay (DELAY);
            }


            encontrando = 0;
        }
	}
    softPwmWrite (PWM1, 100);
    softPwmWrite (PWM2, 100);
    close(myFd);
    return 0;
}
