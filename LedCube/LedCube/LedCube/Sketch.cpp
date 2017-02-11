﻿#include <Arduino.h>
#include "LedCube.h"
#include "Transformation.h"
#include "8x8_horizontal_LSB_1.h"

#define SER_74 13  // serial input
#define RCK_74 12  // storage input
#define SCK_74 11  // clock input

void setChar(byte);

LedCube Cube;
Transformation CubeTrans;
int Counter;
byte CharCounter = 0;

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
	//Cube.setVoxelsX(0,1,128);
	
	Cube.start();
	Cube.setNextFrameReady();
	Cube.setNextFrameTimeElapsed();
	setChar(3);
}

void loop()
{
	if(Counter == 200) {
		//CubeTrans.shiftBackward(&Cube, true);
		//setChar(CharCounter);
		Cube.setNextFrameReady();
		Cube.setNextFrameTimeElapsed();
		CubeTrans.shiftCircle(&Cube, LEDCUBE_AXIS_Z, TRANSFORMATION_ROTATION_COUNTERCLOCKWISE, 1);
		Counter = 0;
		CharCounter++;
	}
	Counter++;
	delay(1);
	digitalWrite(7, STD_ON);
	Cube.task();
	digitalWrite(7, STD_OFF);
}

void setChar(byte Number) {
	for(byte i = 0; i < 8; i++) {
		Cube.setVoxelsYFast(0, 7-i, pgm_read_byte_near(&font[Number][i]));
	}
}