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
#define LEDCUBE_NUMBER_OF_LEDS_PER_SIDE				8
#define LEDCUBE_NUMBER_OF_LAYERS					LEDCUBE_NUMBER_OF_LEDS_PER_SIDE
#define LEDCUBE_NUMBER_OF_SHIFT_REGISTERS			9
#define LEDCUBE_SHIFT_REGISTER_BITWIDTH				8


/******************************************************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *****************************************************************************************************************************************************/
#define LEDCUBE_GET_VOXEL(X, Y, Z)					bitRead(CurrentFrame[Y][Z], LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - X)	
#define LEDCUBE_SET_VOXEL(X, Y, Z)					bitSet(NextFrame[Y][Z], LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - X)
#define LEDCUBE_CLEAR_VOXEL(X, Y, Z)				bitClear(NextFrame[Y][Z], LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - X)
#define LEDCUBE_WRITE_VOXEL(X, Y, Z, Value)			bitWrite(NextFrame[Y][Z], LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - X, Value)


/******************************************************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *****************************************************************************************************************************************************/
/* Type which describes the internal state of the LedCube */
typedef enum {
	LEDCUBE_STATE_NONE,
	LEDCUBE_STATE_INIT,
	LEDCUBE_STATE_SHOW_FRAME,
	LEDCUBE_STATE_NEXT_FRAME_READY
} LedCubeStateType;

/* Type which describes the axes */
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
	LedCubeStateType State;
	byte (*CurrentFrame)[LEDCUBE_NUMBER_OF_LEDS_PER_SIDE];
	byte (*NextFrame)[LEDCUBE_NUMBER_OF_LEDS_PER_SIDE];
    byte CubeBuffer1[LEDCUBE_NUMBER_OF_LEDS_PER_SIDE][LEDCUBE_NUMBER_OF_LEDS_PER_SIDE];
	byte CubeBuffer2[LEDCUBE_NUMBER_OF_LEDS_PER_SIDE][LEDCUBE_NUMBER_OF_LEDS_PER_SIDE];

	// functions
	void clearCube();
	stdReturnType showLayer(byte Layer);
	void sendData(byte Data);
	void switchBufferPointer();
	stdReturnType setLayer();

  public:
    LedCube(byte, byte, byte);
    ~LedCube();

	// get methods
	byte getDataInPin() { return DataInPin; }
	byte getClockPin() { return ClockPin; }
	byte getCurrentLayer() {return CurrentLayer; }
	boolean getState() {return State; }

	// set methods
	void setDataInPin(byte sDataInPin) { DataInPin = sDataInPin; }
	void setClockPin(byte sClockPin) { ClockPin = sClockPin; }
	void setStoragePin(byte sStoragePin) { StoragePin = sStoragePin; }

	// methods
	void init();
	void task();
	stdReturnType setVoxel(byte X, byte Y, byte Z);
	stdReturnType clearVoxel(byte X, byte Y, byte Z);
	stdReturnType writeVoxel(byte X, byte Y, byte Z, boolean Value);
	stdReturnType getVoxel(byte X, byte Y, byte Z, boolean *Value);
	void clearVoxels(void);
	stdReturnType setNextFrameReady();
	stdReturnType showNextFrame();
};

#endif

/******************************************************************************************************************************************************
 *  E N D   O F   F I L E
 *****************************************************************************************************************************************************/
