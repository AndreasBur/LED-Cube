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
/**     \file       LedCube.c
 *      \brief      Main file of LedCube library
 *
 *      \details    Arduino library to drive an 8x8x8 LED Cube
 *                  
 *
 *****************************************************************************************************************************************************/
#define _LECUBE_SOURCE_

/******************************************************************************************************************************************************
 * INCLUDES
 *****************************************************************************************************************************************************/
#include "LedCube.h"

/******************************************************************************************************************************************************
 * P U B L I C   F U N C T I O N S
 *****************************************************************************************************************************************************/

/******************************************************************************************************************************************************
  CONSTRUCTOR OF LedCube
******************************************************************************************************************************************************/
/*! \brief          LedCube Constructor
 *  \details        Instantiation of the LedCube library
 *
 *  \param[in]      sDataInPin         number of the Data Input Pin
 *  \param[in]      sClockPin          number of the Clock Pin
 *  \param[in]      sClockPin          number of the Storage Pin
 *  \return         -
 *****************************************************************************************************************************************************/
LedCube::LedCube(byte sDataInPin, byte sClockPin, byte sStoragePin)
{
	DataInPin = sDataInPin;
	ClockPin = sClockPin;
	StoragePin = sStoragePin;
	CurrentLayer = 0;
	State = LEDCUBE_STATE_NONE;
	CurrentFrame = CubeBuffer1;
	NextFrame = CubeBuffer2;
	memset(CubeBuffer1, 0, sizeof(CubeBuffer1));
	memset(CubeBuffer2, 0, sizeof(CubeBuffer1));
} /* LedCube */


/******************************************************************************************************************************************************
  DESTRUCTOR OF LedCube
******************************************************************************************************************************************************/
LedCube::~LedCube()
{

} /* ~LedCube */


/******************************************************************************************************************************************************
  init()
******************************************************************************************************************************************************/
/*! \brief          initialization of the LedCube Hardware
 *  \details        this function initializes the IO Hardware and the shift registers 74HC595
 *                  
 *  \return         -
 *****************************************************************************************************************************************************/
void LedCube::init()
{
	State = LEDCUBE_STATE_INIT;
	clearCube();
	pinMode(DataInPin, OUTPUT);
	pinMode(ClockPin, OUTPUT);
	pinMode(StoragePin, OUTPUT);
	State = LEDCUBE_STATE_SHOW_FRAME;
} /* init */


/******************************************************************************************************************************************************
  task()
******************************************************************************************************************************************************/
/*! \brief          show layer which is the next in line
 *  \details        this function shows one layer of the current frame on the cube
 *					has to be called periodically
 *                  
 *  \return         -
 *****************************************************************************************************************************************************/
void LedCube::task()
{
	if(State == LEDCUBE_STATE_SHOW_FRAME || State == LEDCUBE_STATE_NEXT_FRAME_READY) {
		if(CurrentLayer >= LEDCUBE_NUMBER_OF_LAYERS) {
			CurrentLayer = 0;
		} else {
			showLayer(CurrentLayer);
			CurrentLayer++;
		}
	}
} /* task */


/******************************************************************************************************************************************************
  clearCube()
******************************************************************************************************************************************************/
/*! \brief          clear all LEDs on the cube
 *  \details        this function initializes the shift registers with zero
 *
 *  \return         -
 *****************************************************************************************************************************************************/
void LedCube::clearCube()
{
	digitalWriteFast(DataInPin, LOW);

	for(byte i = 0; i < (LEDCUBE_NUMBER_OF_SHIFT_REGISTERS * LEDCUBE_SHIFT_REGISTER_BITWIDTH); i++) {
		digitalWriteFast(ClockPin, HIGH);
		digitalWriteFast(ClockPin, LOW);
	}
	digitalWriteFast(StoragePin, HIGH);
	digitalWriteFast(StoragePin, LOW);
} /* clearCube */


/******************************************************************************************************************************************************
  setVoxel()
******************************************************************************************************************************************************/
/*! \brief          set a given voxel in the frame buffer
 *  \details        
 *                  
 *
 *  \return         E_OK
 *                  E_NOT_OK
 *****************************************************************************************************************************************************/
stdReturnType LedCube::setVoxel(byte X, byte Y, byte Z)
{
	if(X < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE && Y < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE && Z < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE)
	{
		LEDCUBE_SET_VOXEL(X, Y, Z);
		return E_OK;
	} else {
		return E_NOT_OK;
	}
} /* setVoxel */


/******************************************************************************************************************************************************
  clearVoxel()
******************************************************************************************************************************************************/
/*! \brief          
 *  \details        
 *                  
 *
 *  \return         E_OK
 *                  E_NOT_OK
 *****************************************************************************************************************************************************/
stdReturnType LedCube::clearVoxel(byte X, byte Y, byte Z)
{
	if(X < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE && Y < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE && Z < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE)
	{
		LEDCUBE_CLEAR_VOXEL(X, Y, Z);
		return E_OK;
	} else {
		return E_NOT_OK;
	}
} /* clearVoxel */


/******************************************************************************************************************************************************
  writeVoxel()
******************************************************************************************************************************************************/
/*! \brief          
 *  \details        
 *                  
 *
 *  \return         E_OK
 *                  E_NOT_OK
 *****************************************************************************************************************************************************/
stdReturnType LedCube::writeVoxel(byte X, byte Y, byte Z, boolean Value)
{
	if(X < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE && Y < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE && Z < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE)
	{
		LEDCUBE_WRITE_VOXEL(X, Y, Z, Value);
		return E_OK;
	} else {
		return E_NOT_OK;
	}
} /* writeVoxel */


/******************************************************************************************************************************************************
  getVoxel()
******************************************************************************************************************************************************/
/*! \brief          
 *  \details        
 *                  
 *
 *  \return         E_OK
 *                  E_NOT_OK
 *****************************************************************************************************************************************************/
stdReturnType LedCube::getVoxel(byte X, byte Y, byte Z, boolean* Value)
{
	if(X < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE && Y < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE && Z < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE)
	{
		*Value = LEDCUBE_GET_VOXEL(X, Y, Z);
		return E_OK;
	} else {
		return E_NOT_OK;
	}
} /* getVoxel */


/******************************************************************************************************************************************************
  setNextFrameReady()
******************************************************************************************************************************************************/
/*! \brief          set next frame to ready state
 *  \details        
 *                  
 *  \return         E_OK
 *                  E_NOT_OK
 *
 *****************************************************************************************************************************************************/
stdReturnType LedCube::setNextFrameReady()
{
	if(State == LEDCUBE_STATE_SHOW_FRAME) {
		State = LEDCUBE_STATE_NEXT_FRAME_READY;
		return E_OK;
	} else {
		return E_NOT_OK;
	}
}


/******************************************************************************************************************************************************
  showNextFrame()
******************************************************************************************************************************************************/
/*! \brief          show next frame on the cube
 *  \details        this function activates the next frame only if next frame is ready
 *                  function is called from timer interrupt normally
 *  \return         E_OK
 *                  E_NOT_OK
 *  \pre			setNextFrameReady() has to be called first
 *****************************************************************************************************************************************************/
stdReturnType LedCube::showNextFrame()
{
	if(State == LEDCUBE_STATE_NEXT_FRAME_READY) {
		switchBufferPointer();
		State = LEDCUBE_STATE_SHOW_FRAME;
		return E_OK;
	} else {
		return E_NOT_OK;
	}
}


/******************************************************************************************************************************************************
 * P R I V A T E   F U N C T I O N S
 *****************************************************************************************************************************************************/

/******************************************************************************************************************************************************
  sendData()
******************************************************************************************************************************************************/
/*! \brief          send data to shift registers
 *  \details        this function shifts the given data to the shift registers 74HC595
 *
 *  \param[in]      Data	data (Byte) to send
 *  \return         -
 *****************************************************************************************************************************************************/
void LedCube::sendData(byte Data)
{
	for (byte i = 0; i < 8; i++) {
		// LSB First
		digitalWriteFast(DataInPin, !!(Data & (1 << i)));
		// MSB First
		//digitalWrite(DataInPin, !!(Data & (1 << (7 - i))));
		// toggle clock pin
		digitalWriteFast(ClockPin, HIGH);
		digitalWriteFast(ClockPin, LOW);
	}
} /* sendData */


/******************************************************************************************************************************************************
  showLayer()
******************************************************************************************************************************************************/
/*! \brief          show a given layer on the cube
 *  \details        this function shows a given layer on the cube
 *                  
 *  \param[in]      Layer		layer which should be shown on the cube
 *  \return         E_OK
 *                  E_NOT_OK
 *****************************************************************************************************************************************************/
stdReturnType LedCube::showLayer(byte Layer)
{
	stdReturnType ReturnValue = E_NOT_OK;
	
	if(Layer < LEDCUBE_NUMBER_OF_LAYERS) {
		/* put on given layer */
		sendData(1 << (Layer - 1));
		//sendData(1 << Layer);
		/* send the layer data to the shift registers */
		for(byte Y = 0; Y < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; Y++) {
			sendData(CurrentFrame[Y][Layer]);
		}
		// toggle storage pin
		digitalWriteFast(StoragePin, HIGH);
		digitalWriteFast(StoragePin, LOW);

		ReturnValue = E_OK;
	}
	return ReturnValue;
} /* showLayer */


/******************************************************************************************************************************************************
  switchBufferPointer()
******************************************************************************************************************************************************/
/*! \brief          switch the two frame buffers
 *  \details        this function switches the two frame buffers CubeBuffer1 and CubeBuffer2
 *                  
 *  \return         -
 *****************************************************************************************************************************************************/
void LedCube::switchBufferPointer()
{
		byte (*pTmp)[LEDCUBE_NUMBER_OF_LEDS_PER_SIDE];

		pTmp = CurrentFrame;
		CurrentFrame = NextFrame;
		NextFrame = pTmp;
} /* switchBufferPointer */


/******************************************************************************************************************************************************
 *  E N D   O F   F I L E
 *****************************************************************************************************************************************************/
 