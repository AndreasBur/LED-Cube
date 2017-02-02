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
/* LedCube Configuration Parameter */
#define LEDCUBE_DATA_IN_PIN                         13
#define LEDCUBE_CLOCK_PIN                           11
#define LEDCUBE_STORAGE_PIN                         12

#define LEDCUBE_NUMBER_OF_LEDS_PER_SIDE             8
#define LEDCUBE_NUMBER_OF_LAYERS                    LEDCUBE_NUMBER_OF_LEDS_PER_SIDE
#define LEDCUBE_NUMBER_OF_SHIFT_REGISTERS           9
#define LEDCUBE_SHIFT_REGISTER_BITWIDTH             8


/******************************************************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *****************************************************************************************************************************************************/
//#define LEDCUBE_GET_VOXEL(X, Y, Z)                    bitRead(CurrentFrame[Y][Z], X)  
//#define LEDCUBE_SET_VOXEL(X, Y, Z)                    bitSet(NextFrame[Y][Z], X)
//#define LEDCUBE_CLEAR_VOXEL(X, Y, Z)                  bitClear(NextFrame[Y][Z], X)
//#define LEDCUBE_WRITE_VOXEL(X, Y, Z, Value)           bitWrite(NextFrame[Y][Z], X, Value)


/******************************************************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *****************************************************************************************************************************************************/
/* Type which describes the internal state of the LedCube */
typedef enum {
    LEDCUBE_STATE_NONE,
    LEDCUBE_STATE_INIT,
	LEDCUBE_STATE_READY,
    LEDCUBE_STATE_RUNNING,
    LEDCUBE_STATE_STOPPED
} LedCubeStateType;

/* Type which defines the axes */
typedef enum {
    LEDCUBE_AXIS_X,
    LEDCUBE_AXIS_Y,
    LEDCUBE_AXIS_Z
} LedCubeAxisType;

/* Type which describes the state of the next frame */
struct NextFrameAtributeType {
	boolean	Ready : 1;
	boolean TimeElapsed : 1;
};

/******************************************************************************************************************************************************
 *  CLASS  LedCube
 *****************************************************************************************************************************************************/
class LedCube
{
  private:
    byte CurrentLayer;
    LedCubeStateType State;
	NextFrameAtributeType NextFrameAtribute;
    byte (*CurrentFrame)[LEDCUBE_NUMBER_OF_LEDS_PER_SIDE];
    byte (*NextFrame)[LEDCUBE_NUMBER_OF_LEDS_PER_SIDE];
    byte CubeBuffer1[LEDCUBE_NUMBER_OF_LEDS_PER_SIDE][LEDCUBE_NUMBER_OF_LEDS_PER_SIDE];
    byte CubeBuffer2[LEDCUBE_NUMBER_OF_LEDS_PER_SIDE][LEDCUBE_NUMBER_OF_LEDS_PER_SIDE];

    // functions
    void clearCube();
    stdReturnType showLayer(byte);
    void sendData(byte Data);
    void switchBufferPointer();
    stdReturnType setLayer();
	stdReturnType showNextFrame();

  public:
    LedCube();
    ~LedCube();

    // get methods
    byte getCurrentLayer() { return CurrentLayer; }
    LedCubeStateType getState() { return State; }

    // set methods

    // methods
    void init();
    void task();
	stdReturnType start();
	stdReturnType stop();

    stdReturnType setVoxel(byte, byte, byte);
	stdReturnType clearVoxel(byte, byte, byte);
	stdReturnType writeVoxel(byte, byte, byte, boolean);
	stdReturnType getVoxel(byte, byte, byte, boolean*);

	inline void setVoxelFast(byte X, byte Y, byte Z) { bitSet(NextFrame[Y][Z], X); }
    inline void clearVoxelFast(byte X, byte Y, byte Z) { bitClear(NextFrame[Y][Z], X); }
    inline void writeVoxelFast(byte X, byte Y, byte Z, boolean Value) { bitWrite(NextFrame[Y][Z], X, Value); }
    inline byte getVoxelFast(byte X, byte Y, byte Z) { return bitRead(CurrentFrame[Y][Z], X); }

	void clearVoxels(void);
    stdReturnType setNextFrameReady();
};

#endif

/******************************************************************************************************************************************************
 *  E N D   O F   F I L E
 *****************************************************************************************************************************************************/
