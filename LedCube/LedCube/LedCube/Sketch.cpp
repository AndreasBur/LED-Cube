#include <Arduino.h>
#include "LedCube.h"
#include "Transformation.h"

#define SER_74 13  // serial input
#define RCK_74 12  // storage input
#define SCK_74 11  // clock input

LedCube Cube;
Transformation CubeTrans;
int Counter;

void setup() {
	Cube.init();
	pinMode(7, OUTPUT);
	for(byte x = 0; x<LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; x++) {
		for(byte y = 0; y<LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; y++) {
			for(byte z = 0; z<LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; z++) {
				//Cube.setVoxel(x, y, z);
			}
		}
	}
	Cube.setVoxelsX(0,1,128);
	
	

	Cube.start();
	Cube.setNextFrameReady();
	Cube.setNextFrameTimeElapsed();
}

void loop()
{
	if(Counter == 1000) { 
		CubeTrans.shiftForward(&Cube, true);
		Cube.setNextFrameReady();
		Cube.setNextFrameTimeElapsed();
		Counter = 0;
	}
	Counter++;
	delay(1);
	digitalWrite(7, STD_ON);
	Cube.task();
	digitalWrite(7, STD_OFF);
}