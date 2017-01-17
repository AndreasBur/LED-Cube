#include <Arduino.h>
#include "LedCube.h"

#define SER_74 13  // serial input
#define RCK_74 12  // storage input
#define SCK_74 11  // clock input

LedCube Cube(SER_74, SCK_74, RCK_74);


void setup() {
	Cube.init();
}

void loop() {
	delay(500);
	Cube.task();
	
}