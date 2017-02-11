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
/**     \file       Transformation.c
 *      \brief      Main file of Transformation library
 *
 *      \details    Arduino Transformation library for 8x8x8 LED Cube
 *                  
 *
 *****************************************************************************************************************************************************/
#define _TRANSFORMATION_SOURCE_

/******************************************************************************************************************************************************
 * INCLUDES
 *****************************************************************************************************************************************************/
#include "Transformation.h"


/******************************************************************************************************************************************************
 * P U B L I C   F U N C T I O N S
 *****************************************************************************************************************************************************/

/******************************************************************************************************************************************************
  CONSTRUCTOR OF Transformation
******************************************************************************************************************************************************/
/*! \brief          
 *  \details        
 *
 *  \param[in]      
 *  \param[in]      
 *  \param[in]      
 *  \return         -
 *****************************************************************************************************************************************************/
Transformation::Transformation()
{

} /* Transformation */


/******************************************************************************************************************************************************
  DESTRUCTOR OF Transformation
******************************************************************************************************************************************************/
Transformation::~Transformation()
{

} /* ~Transformation */


/******************************************************************************************************************************************************
  shiftForward()
******************************************************************************************************************************************************/
/*! \brief          
 *  \details        
 *                  
 *  \return         -
 *****************************************************************************************************************************************************/
void Transformation::shiftForward(LedCube* Cube, boolean Rotate)
{
	for (byte Z = 0; Z < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; Z++) {
		for(byte X = 0; X < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - 1; X++) {
			Cube->setVoxelsYFast(X, Z, Cube->getVoxelsYFast(X + 1, Z));
		}
		if(Rotate) Cube->setVoxelsYFast(LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - 1, Z, Cube->getVoxelsYFast(0, Z));
		else Cube->setVoxelsYFast(LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - 1, Z, 0);
	}
} /* shiftForward */


/******************************************************************************************************************************************************
  shiftBackward()
******************************************************************************************************************************************************/
/*! \brief          
 *  \details        
 *                  
 *  \return         -
 *****************************************************************************************************************************************************/
void Transformation::shiftBackward(LedCube* Cube, boolean Rotate)
{
	for (byte Z = 0; Z < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; Z++) {
		for(byte X = 1; X < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; X++) {
			Cube->setVoxelsYFast(X, Z, Cube->getVoxelsYFast(X - 1, Z));
		}
		if(Rotate) Cube->setVoxelsYFast(0, Z, Cube->getVoxelsYFast(LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - 1, Z));
		else Cube->setVoxelsYFast(0, Z, 0);
	}
} /* shiftBackward */


/******************************************************************************************************************************************************
  shiftUpward()
******************************************************************************************************************************************************/
/*! \brief          
 *  \details        
 *                  
 *  \return         -
 *****************************************************************************************************************************************************/
void Transformation::shiftUpward(LedCube* Cube, boolean Rotate)
{
	for(byte Y = 0; Y < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; Y++) {
		for (byte Z = 1; Z < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; Z++) {
			Cube->setVoxelsXFast(Y, Z, Cube->getVoxelsXFast(Y, Z - 1));
		}
		if(Rotate) Cube->setVoxelsXFast(Y, 0, Cube->getVoxelsXFast(Y, LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - 1));
		else Cube->setVoxelsXFast(Y, 0, 0);
	}
} /* shiftUpward */


/******************************************************************************************************************************************************
  shiftDownward()
******************************************************************************************************************************************************/
/*! \brief          
 *  \details        
 *                  
 *  \return         -
 *****************************************************************************************************************************************************/
void Transformation::shiftDownward(LedCube* Cube, boolean Rotate)
{
	for(byte Y = 0; Y < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - 1; Y++) {
		for (byte Z = 0; Z < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; Z++) {
			Cube->setVoxelsXFast(Y, Z, Cube->getVoxelsXFast(Y, Z + 1));
		}
		if(Rotate) Cube->setVoxelsXFast(Y, LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - 1, Cube->getVoxelsXFast(Y, 0));
		else Cube->setVoxelsXFast(Y, LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - 1, 0);
	}
} /* shiftDownward */


/******************************************************************************************************************************************************
  shiftLeft()
******************************************************************************************************************************************************/
/*! \brief          
 *  \details        
 *                  
 *  \return         -
 *****************************************************************************************************************************************************/
void Transformation::shiftLeft(LedCube* Cube, boolean Rotate)
{
	for (byte Z = 0; Z < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; Z++) {
		for(byte Y = 0; Y < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - 1; Y++) {
			Cube->setVoxelsXFast(Y, Z, Cube->getVoxelsXFast(Y + 1, Z));
		}
		if(Rotate) Cube->setVoxelsXFast(LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - 1, Z, Cube->getVoxelsXFast(0, Z));
		else Cube->setVoxelsXFast(LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - 1, Z, 0);
	}
} /* shiftLeft */


/******************************************************************************************************************************************************
  shiftRight()
******************************************************************************************************************************************************/
/*! \brief          
 *  \details        
 *                  
 *  \return         -
 *****************************************************************************************************************************************************/
void Transformation::shiftRight(LedCube* Cube, boolean Rotate)
{
	for (byte Z = 0; Z < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; Z++) {
		for(byte Y = 1; Y < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; Y++) {
			Cube->setVoxelsXFast(Y, Z, Cube->getVoxelsXFast(Y - 1, Z));
		}
		if(Rotate) Cube->setVoxelsXFast(0, Z, Cube->getVoxelsXFast(LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - 1, Z));
		else Cube->setVoxelsXFast(0, Z, 0);
	}
} /* shiftRight */


/******************************************************************************************************************************************************
  shiftForwardFast()
******************************************************************************************************************************************************/
/*! \brief          
 *  \details        
 *                  
 *  \return         -
 *****************************************************************************************************************************************************/
void Transformation::shiftForwardFast(LedCube* Cube, boolean Rotate)
{
	for (byte Z = 0; Z < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; Z++) {
		for(byte Y = 0; Y < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; Y++) {
			Cube->setVoxelsXFast(Y, Z, Cube->getVoxelsXFast(Y, Z) >> 1);
			if(Rotate) Cube->writeVoxelFast(LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - 1, Y, Z, Cube->getVoxelFast(0, Y, Z));
		}
	}
} /* shiftForwardFast */


/******************************************************************************************************************************************************
  shiftBackwardFast()
******************************************************************************************************************************************************/
/*! \brief          
 *  \details        
 *                  
 *  \return         -
 *****************************************************************************************************************************************************/
void Transformation::shiftBackwardFast(LedCube* Cube, boolean Rotate)
{
	for (byte Z = 0; Z < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; Z++) {
		for(byte Y = 0; Y < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; Y++) {
			Cube->setVoxelsXFast(Y, Z, Cube->getVoxelsXFast(Y, Z) << 1);
			if(Rotate) Cube->writeVoxelFast(0, Y, Z, Cube->getVoxelFast(LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - 1, Y, Z));
		}
	}
} /* shiftBackwardFast */


/******************************************************************************************************************************************************
 * P R I V A T E   F U N C T I O N S
 *****************************************************************************************************************************************************/

/******************************************************************************************************************************************************
  shiftCircle()
******************************************************************************************************************************************************/
/*! \brief          
 *  \details        
 *                  
 *  \return         -
 *****************************************************************************************************************************************************/
stdReturnType Transformation::shiftCircle(LedCube* Cube, LedCubeAxisType ShiftAxis, TransformationRotationDirectionType Direction, byte Circle)
{	
	const byte LEDs = LEDCUBE_NUMBER_OF_LEDS_PER_SIDE;

	if(Circle > 0 && Circle <= LEDs / 2) {
		Circle--;
		if(TRANSFORMATION_ROTATION_CLOCKWISE == Direction) {
			if(LEDCUBE_AXIS_Z == ShiftAxis) {
				for(byte Z = 0; Z < LEDs; Z++) {
					/* shift front, right, back, left */
					for(int8_t Y = Circle; Y < LEDs-1-Circle; Y++) Cube->writeVoxelFast(Circle, Y, Z, Cube->getVoxelFast(Circle, Y+1, Z));
					for(int8_t X = Circle; X < LEDs-1-Circle; X++) Cube->writeVoxelFast(X, LEDs-1-Circle, Z, Cube->getVoxelFast(X+1, LEDs-1-Circle, Z));
					for(int8_t Y = LEDs-1-Circle; Y > Circle; Y--) Cube->writeVoxelFast(LEDs-1-Circle, Y, Z, Cube->getVoxelFast(LEDs-1-Circle, Y-1, Z));
					for(int8_t X = LEDs-1-Circle; X > Circle; X--) Cube->writeVoxelFast(X, Circle, Z, Cube->getVoxelFast(X-1, Circle, Z));
				}
			}
		}
		if(TRANSFORMATION_ROTATION_COUNTERCLOCKWISE == Direction) {
			if(LEDCUBE_AXIS_Z == ShiftAxis) {
				for(byte Z = 0; Z < LEDs; Z++) {
					/* shift left, back, right, front */
					for(int8_t X = Circle; X < LEDs-1-Circle; X++) Cube->writeVoxelFast(X, Circle, Z, Cube->getVoxelFast(X+1, Circle, Z));
					for(int8_t Y = Circle; Y < LEDs-1-Circle; Y++) Cube->writeVoxelFast(LEDs-1-Circle, Y, Z, Cube->getVoxelFast(LEDs-1-Circle, Y+1, Z));
					for(int8_t X = LEDs-1-Circle; X > Circle; X--) Cube->writeVoxelFast(X, LEDs-1-Circle, Z, Cube->getVoxelFast(X-1, LEDs-1-Circle, Z));
					for(int8_t Y = LEDs-1-Circle; Y > Circle; Y--) Cube->writeVoxelFast(Circle, Y, Z, Cube->getVoxelFast(Circle, Y-1, Z));
				}
			}
		}
		return E_OK;
	} 
	else { 
		return E_NOT_OK;
	}
} /* rotateWithShift */

/******************************************************************************************************************************************************
 *  E N D   O F   F I L E
 *****************************************************************************************************************************************************/
 