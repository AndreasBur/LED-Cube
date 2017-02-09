#include <iostream>
#include <stdio.h>

#define LEDCUBE_NUMBER_OF_LEDS_PER_SIDE     8

using namespace std;


// constant macros
/* Bit setzen */
#define setBit(Var, Bit) \
((Var) |= (1 << (Bit)))

/* Bit löschen */
#define clearBit(Var, Bit) \
((Var) &= (unsigned)~(1 << (Bit)))

/* Bit togglen */
#define toggleBit(Var, Bit) \
((Var) ^= (1 << (Bit)))

/* Bit Operationen */
#define readBit(Var, Bit) \
(((Var) & (1 << (Bit))) >> Bit)

#define writeBit(Var, Bit, Value) \
(Value ? setBit(Var, Bit) : clearBit(Var, Bit))

#define isBitSet(Var, Bit) \
((Var) & (1 << (Bit)))

#define isBitCleared(Var, Bit) \
!isBitSet(Var, Bit)

/* Bit Gruppen abfragen */
#define readRegisterBitGroup(Register, BitGroupMask, BitGroupPosition) \
((Register & ((uint8_t)BitGroupMask)) >> BitGroupPosition)

/* Bit Gruppen setzen */
#define writeRegisterBitGroup(Register, BitGroupMask, BitGroupPosition, Value) \
(Register = ((Register & ~((uint8_t)BitGroupMask)) | ((Value << BitGroupPosition) & ((uint8_t)BitGroupMask))))

// arduino macros
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))


#define B(x) ( \
  (0##x >>  0 & 0001) | \
  (0##x >>  2 & 0002) | \
  (0##x >>  4 & 0004) | \
  (0##x >>  6 & 0010) | \
  (0##x >>  8 & 0020) | \
  (0##x >> 10 & 0040) | \
  (0##x >> 12 & 0100) | \
  (0##x >> 14 & 0200) )


// type definition
typedef char byte;

// variable declaration
byte CubeBuffer1[LEDCUBE_NUMBER_OF_LEDS_PER_SIDE][LEDCUBE_NUMBER_OF_LEDS_PER_SIDE];
byte CubeBuffer2[LEDCUBE_NUMBER_OF_LEDS_PER_SIDE][LEDCUBE_NUMBER_OF_LEDS_PER_SIDE];

// function declaration
void setVoxelFast(byte X, byte Y, byte Z) { bitSet(CubeBuffer2[Y][Z], X); }
void clearVoxelFast(byte X, byte Y, byte Z) { bitClear(CubeBuffer2[Y][Z], X); }
void writeVoxelFast(byte X, byte Y, byte Z, bool Value) { bitWrite(CubeBuffer2[Y][Z], X, Value); }
byte getVoxelFast(byte X, byte Y, byte Z) { return bitRead(CubeBuffer1[Y][Z], X); }

byte getVoxelFastAusgabe(byte X, byte Y, byte Z) { return bitRead(CubeBuffer2[Y][Z], X); }


char Voxel;

int main()
{
    setVoxelFast(1,5,0);

    for(int X = 0; X < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; X++) {
        for(int Y = 0; Y < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; Y++) {
            Voxel = getVoxelFastAusgabe(LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - X - 1, Y, 0);
             printf("%d,", Voxel);
        }
        printf("\n");
    }

    return 0;
}
