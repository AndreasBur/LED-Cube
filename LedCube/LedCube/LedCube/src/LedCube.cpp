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
 *  \return         -
 *****************************************************************************************************************************************************/
LedCube::LedCube()
{
    CurrentLayer = 0;
    State = LEDCUBE_STATE_NONE;
	NextFrameReady = false,
	NextFrameTimeElapsed = false;
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
    pinModeFast(LEDCUBE_DATA_IN_PIN, OUTPUT);
    pinModeFast(LEDCUBE_CLOCK_PIN, OUTPUT);
    pinModeFast(LEDCUBE_STORAGE_PIN, OUTPUT);
    State = LEDCUBE_STATE_READY;
} /* init */


/******************************************************************************************************************************************************
  start()
******************************************************************************************************************************************************/
/*! \brief          
 *  \details        
 *                  
 *  \return         -
 *****************************************************************************************************************************************************/
stdReturnType LedCube::start()
{
	if(State == LEDCUBE_STATE_READY || LEDCUBE_STATE_STOPPED) {
		State = LEDCUBE_STATE_RUNNING;
		return E_OK;
	}
	return E_NOT_OK;
} /* start */


/******************************************************************************************************************************************************
  stop()
******************************************************************************************************************************************************/
/*! \brief          
 *  \details        
 *                  
 *  \return         -
 *****************************************************************************************************************************************************/
stdReturnType LedCube::stop()
{
	if(State == LEDCUBE_STATE_RUNNING) {
		State = LEDCUBE_STATE_STOPPED;
		return E_OK;
	}
	return E_NOT_OK;
} /* start */


/******************************************************************************************************************************************************
  task()
******************************************************************************************************************************************************/
/*! \brief          show layer which is the next in line
 *  \details        this function shows one layer of the current frame on the cube
 *                  has to be called periodically
 *                  
 *  \return         -
 *****************************************************************************************************************************************************/
void LedCube::task()
{
    if(State == LEDCUBE_STATE_RUNNING) {
        if(CurrentLayer >= LEDCUBE_NUMBER_OF_LAYERS) {
            CurrentLayer = 0;
			/* is next frame ready to show? */
			if(NextFrameReady && NextFrameTimeElapsed) { 
				showNextFrame();
				NextFrameReady = false;
				NextFrameTimeElapsed = false;
			}
        }
        showLayer(CurrentLayer);
        CurrentLayer++;
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
    digitalWriteFast(LEDCUBE_DATA_IN_PIN, LOW);

    for(byte i = 0; i < (LEDCUBE_NUMBER_OF_SHIFT_REGISTERS * LEDCUBE_SHIFT_REGISTER_BITWIDTH); i++) {
        digitalWriteFast(LEDCUBE_CLOCK_PIN, HIGH);
        digitalWriteFast(LEDCUBE_CLOCK_PIN, LOW);
    }
    digitalWriteFast(LEDCUBE_STORAGE_PIN, HIGH);
    digitalWriteFast(LEDCUBE_STORAGE_PIN, LOW);
} /* clearCube */


/******************************************************************************************************************************************************
  setVoxel()
******************************************************************************************************************************************************/
/*! \brief          set a given voxel in the frame buffer
 *  \details        
              
 *  \param[in]      X          x-axis coordinate
 *  \param[in]      Y          y-axis coordinate
 *  \param[in]      Z          z-axis coordinate
 *  \return         E_OK
 *                  E_NOT_OK
 *****************************************************************************************************************************************************/
stdReturnType LedCube::setVoxel(byte X, byte Y, byte Z)
{
    if(X < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE && Y < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE && Z < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE)
    {
        bitSet(NextFrame[Y][Z], X);
        return E_OK;
    } else {
        return E_NOT_OK;
    }
} /* setVoxel */


/******************************************************************************************************************************************************
  clearVoxel()
******************************************************************************************************************************************************/
/*! \brief          clear a given voxel in the frame buffer
 *  \details        
 *
 *  \param[in]      X          x-axis coordinate
 *  \param[in]      Y          y-axis coordinate
 *  \param[in]      Z          z-axis coordinate
 *  \return         E_OK
 *                  E_NOT_OK
 *****************************************************************************************************************************************************/
stdReturnType LedCube::clearVoxel(byte X, byte Y, byte Z)
{
    if(X < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE && Y < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE && Z < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE)
    {
        bitClear(NextFrame[Y][Z], X);
        return E_OK;
    } else {
        return E_NOT_OK;
    }
} /* clearVoxel */


/******************************************************************************************************************************************************
  writeVoxel()
******************************************************************************************************************************************************/
/*! \brief          set given voxel to a given value in the frame buffer
 *  \details        
 *                  
 *  \param[in]      X          x-axis coordinate
 *  \param[in]      Y          y-axis coordinate
 *  \param[in]      Z          z-axis coordinate
 *  \param[in]      Value      voxel of value on or off
 *  \return         E_OK
 *                  E_NOT_OK
 *****************************************************************************************************************************************************/
stdReturnType LedCube::writeVoxel(byte X, byte Y, byte Z, boolean Value)
{
    if(X < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE && Y < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE && Z < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE)
    {
        bitWrite(NextFrame[Y][Z], X, Value);
        return E_OK;
    } else {
        return E_NOT_OK;
    }
} /* writeVoxel */


/******************************************************************************************************************************************************
  getVoxel()
******************************************************************************************************************************************************/
/*! \brief          get a given voxel of the frame buffer
 *  \details        
 *                  
 *  \param[in]      X          x-axis coordinate
 *  \param[in]      Y          y-axis coordinate
 *  \param[in]      Z          z-axis coordinate
 *  \param[out]     Value      voxel of value on or off
 *  \return         E_OK
 *                  E_NOT_OK
 *****************************************************************************************************************************************************/
stdReturnType LedCube::getVoxel(byte X, byte Y, byte Z, boolean* Value)
{
    if(X < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE && Y < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE && Z < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE)
    {
        *Value = bitRead(CurrentFrame[Y][Z], X);
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
 *****************************************************************************************************************************************************/
stdReturnType LedCube::setNextFrameReady()
{
    if(State == LEDCUBE_STATE_RUNNING) {
        NextFrameReady = true;
        return E_OK;
    } else {
        return E_NOT_OK;
    }
}


/******************************************************************************************************************************************************
  setNextFrameTimeElapsed()
******************************************************************************************************************************************************/
/*! \brief          set next frame time elapsed
 *  \details        
 *                  
 *  \return         E_OK
 *                  E_NOT_OK
 *****************************************************************************************************************************************************/
stdReturnType LedCube::setNextFrameTimeElapsed()
{
    if(State == LEDCUBE_STATE_RUNNING) {
        NextFrameTimeElapsed = true;
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
 *  \param[in]      Data    data (Byte) to send
 *  \return         -
 *****************************************************************************************************************************************************/
void LedCube::sendData(byte Data)
{
    for (byte i = 0; i < 8; i++) {
        // LSB First
        //digitalWrite(DataInPin, !!(Data & (1 << i)));
        // MSB First
        digitalWriteFast(LEDCUBE_DATA_IN_PIN, !!(Data & (1 << (7 - i))));
        // toggle clock pin
        digitalWriteFast(LEDCUBE_CLOCK_PIN, HIGH);
        digitalWriteFast(LEDCUBE_CLOCK_PIN, LOW);
    }
} /* sendData */


/******************************************************************************************************************************************************
  showLayer()
******************************************************************************************************************************************************/
/*! \brief          show a given layer on the cube
 *  \details        this function shows a given layer on the cube
 *                  
 *  \param[in]      Layer       layer which should be shown on the cube
 *  \return         E_OK
 *                  E_NOT_OK
 *****************************************************************************************************************************************************/
stdReturnType LedCube::showLayer(byte Layer)
{
    stdReturnType ReturnValue = E_NOT_OK;
    
    if(Layer < LEDCUBE_NUMBER_OF_LAYERS) {
        /* put on given layer */
        sendData(1 << Layer);
        /* send the layer data to the shift registers */
        for(byte Y = 0; Y < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; Y++) {
            sendData(CurrentFrame[Y][Layer]);
        }
        // toggle storage pin
        digitalWriteFast(LEDCUBE_STORAGE_PIN, HIGH);
        digitalWriteFast(LEDCUBE_STORAGE_PIN, LOW);

        ReturnValue = E_OK;
    }
    return ReturnValue;
} /* showLayer */


/******************************************************************************************************************************************************
  showNextFrame()
******************************************************************************************************************************************************/
/*! \brief          show next frame on the cube
 *  \details        this function activates the next frame only if next frame is ready
 *                  function is called from timer interrupt normally
 *  \return         E_OK
 *                  E_NOT_OK
 *****************************************************************************************************************************************************/
stdReturnType LedCube::showNextFrame()
{
    switchBufferPointer();
	return E_OK;
}


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
 