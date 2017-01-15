/******************************************************************************************************************************************************
 *  COPYRIGHT
 *  ---------------------------------------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) Andreas Burnickl                                                                                                 All rights reserved.
 *
 *  \endverbatim
 *  ---------------------------------------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------------------------------------*/
/**     \file       LedCube.h
 *      \brief      Main header file of LedCube library
 *
 *      \details    Arduino library to drive an 8x8x8 LED Cube 
 *                  
 *
 *****************************************************************************************************************************************************/
#ifndef _LEDCUBE_H_
#define _LEDCUBE_H_

/******************************************************************************************************************************************************
 * INCLUDES
 *****************************************************************************************************************************************************/
#include "StandardTypes.h"
#include "Arduino.h"
#include "digitalWriteFast.h"


/******************************************************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *****************************************************************************************************************************************************/
//#define LEDCUBE_BUFFER_SIZE						64

#define LEDCUBE_NUMBER_OF_LEDS_PER_SIDE				8
#define LEDCUBE_NUMBER_OF_LAYERS					LEDCUBE_NUMBER_OF_LEDS_PER_SIDE


#define SER_74 13  // datain input
#define RCK_74 12  // storage input
#define SCK_74 11  // clock input


/******************************************************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *****************************************************************************************************************************************************/
#define LEDCUBE_GET_VOXEL(X)(Y)(Z)					bitRead(CurrentFrame[Y][Z], LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - Y)	
#define LEDCUBE_SET_VOXEL(X)(Y)(Z)					bitSet(NextFrame[Y][Z], LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - Y)
#define LEDCUBE_CLEAR_VOXEL(X)(Y)(Z)				bitClear(NextFrame[Y][Z], LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - Y)
#define LEDCUBE_WRITE_VOXEL(X)(Y)(Z)(Value)			bitWrite(NextFrame[Y][Z], LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - Y, Value)


/******************************************************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *****************************************************************************************************************************************************/
typedef enum {
	LEDCUBE_AXIS_X,
	LEDCUBE_AXIS_Y,
	LEDCUBE_AXIS_Z
} LedCubeAxisType;

/******************************************************************************************************************************************************
 *  CLASS  LedCube
 *****************************************************************************************************************************************************/
class LedCube
{
  private:
	byte DataInPin;
	byte ClockPin;
	byte StoragePin;
	byte CurrentLayer;
	byte **CurrentFrame;
	byte **NextFrame;
	boolean FrameReady;
    byte CubeBuffer1[LEDCUBE_NUMBER_OF_LEDS_PER_SIDE][LEDCUBE_NUMBER_OF_LEDS_PER_SIDE];
	byte CubeBuffer2[LEDCUBE_NUMBER_OF_LEDS_PER_SIDE][LEDCUBE_NUMBER_OF_LEDS_PER_SIDE];
	stdReturnType showLayer(byte Layer);
	void sendData(byte Data);
	void switchBufferPointer();

  public:
    LedCube(byte, byte, byte);
    ~LedCube();

	void task();
	stdReturnType setCube();
	stdReturnType setLayer();
	stdReturnType setVoxel(byte X, byte Y, byte Z);
	stdReturnType clearVoxel(byte X, byte Y, byte Z);
	stdReturnType writeVoxel(byte X, byte Y, byte Z, boolean Value);
	stdReturnType getVoxel(byte X, byte Y, byte Z, boolean *Value);
	void clearVoxels(void);
};

#endif

/******************************************************************************************************************************************************
 *  E N D   O F   F I L E
 *****************************************************************************************************************************************************/