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
/**     \file       Transformation.h
 *      \brief      Main header file of LedCube Transformation library
 *
 *      \details    Arduino Animation library for 8x8x8 LED Cube
 *                  
 *
 *****************************************************************************************************************************************************/
#ifndef _TRANSFORMATION_H_
#define _TRANSFORMATION_H_

/******************************************************************************************************************************************************
 * INCLUDES
 *****************************************************************************************************************************************************/
#include "StandardTypes.h"
#include "LedCube.h"

/******************************************************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *****************************************************************************************************************************************************/


/******************************************************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *****************************************************************************************************************************************************/


/******************************************************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *****************************************************************************************************************************************************/
/* type which describes rotation in degrees */
typedef enum {
	TRANSFORMATION_ROTATION_DEGREE_0,
	TRANSFORMATION_ROTATION_DEGREE_90,
	TRANSFORMATION_ROTATION_DEGREE_180,
	TRANSFORMATION_ROTATION_DEGREE_270
} TransformationRotationDegreeType;

/* type which describes direction of rotation */
typedef enum {
	TRANSFORMATION_ROTATION_CLOCKWISE,
	TRANSFORMATION_ROTATION_COUNTERCLOCKWISE
} TransformationRotationDirectionType;


/******************************************************************************************************************************************************
 *  CLASS  LedCube
 *****************************************************************************************************************************************************/
class Transformation
{
  private:
   
  public:
    Transformation();
    ~Transformation();

	void rotate(LedCube&, LedCubeAxisType ShiftAxis, TransformationRotationDegreeType Degrees);
	stdReturnType rotateWithShift(LedCube*, LedCubeAxisType ShiftAxis, TransformationRotationDirectionType Direction, byte Clock);
	void shiftForward(LedCube*, boolean = false);
	void shiftBackward(LedCube*, boolean = false);
	void shiftUpward(LedCube*, boolean = false);
	void shiftDownward(LedCube*, boolean = false);
	void shiftLeft(LedCube*, boolean = false);
	void shiftRight(LedCube*, boolean = false);

	void shiftForwardFast(LedCube*, boolean = false);
	void shiftBackwardFast(LedCube*, boolean = false);
};

#endif

/******************************************************************************************************************************************************
 *  E N D   O F   F I L E
 *****************************************************************************************************************************************************/