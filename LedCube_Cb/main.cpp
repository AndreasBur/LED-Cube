#include <iostream>
#include <stdio.h>

#define LEDCUBE_NUMBER_OF_LEDS_PER_SIDE     8

using namespace std;


// constant macros
/* Bit setzen */
#define setBit(Var, Bit) \
((Var) |= (1 << (Bit)))

/* Bit lˆschen */
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
void setVoxelFastStart(byte X, byte Y, byte Z) { bitSet(CubeBuffer1[Y][Z], X); }
void setVoxelFast(byte X, byte Y, byte Z) { bitSet(CubeBuffer2[Y][Z], X); }
void clearVoxelFast(byte X, byte Y, byte Z) { bitClear(CubeBuffer2[Y][Z], X); }
void writeVoxelFast(byte X, byte Y, byte Z, bool Value) { bitWrite(CubeBuffer2[Y][Z], X, Value); }
byte getVoxelFast(byte X, byte Y, byte Z) { return bitRead(CubeBuffer1[Y][Z], X); }

byte getVoxelFastAusgabe(byte X, byte Y, byte Z) { return bitRead(CubeBuffer2[Y][Z], X); }


char Voxel;

int main()
{
    setVoxelFastStart(1,5,0);
    setVoxelFastStart(6,5,0);
    setVoxelFastStart(1,1,0);
    setVoxelFastStart(0,0,0);
    setVoxelFastStart(7,7,0);

    setVoxelFastStart(3,2,0);
    setVoxelFastStart(3,3,0);

    // original
    cout << "original" << endl;
    for(int X = 0; X < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; X++) {
        for(int Y = 0; Y < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; Y++) {
            Voxel = getVoxelFast(LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - X - 1, Y, 0);
             printf("%d,", Voxel);
        }
        printf("\n");
    }

    // ‰uﬂerer Kreis
    for(int a = 0; a <= 6; a++)
    {
        writeVoxelFast(0, a, 0, getVoxelFast(0, a+1, 0));
        //array_trans[0][a] = array[0][a+1];
        writeVoxelFast(a, 7, 0, getVoxelFast(a+1, 7, 0));
        //array_trans[a][7] = array[a+1][7];
    }

    for(int a = 7; a > 0; a--)
    {
        writeVoxelFast(7, a, 0, getVoxelFast(7, a-1, 0));
        //array_trans[7][a] = array[7][a-1];
        writeVoxelFast(a, 0, 0, getVoxelFast(a-1, 0, 0));
        //array_trans[a][0] = array[a-1][0];
    }
    // 2 ‰uﬂerer Kreis
    for(int a = 1; a <= 5; a++)
    {
        writeVoxelFast(1, a, 0, getVoxelFast(1, a+1, 0));
        //array_trans[0][a] = array[0][a+1];
        writeVoxelFast(a, 6, 0, getVoxelFast(a+1, 6, 0));
        //array_trans[a][7] = array[a+1][7];
    }

    for(int a = 6; a > 1; a--)
    {
        writeVoxelFast(6, a, 0, getVoxelFast(6, a-1, 0));
        //array_trans[7][a] = array[7][a-1];
        writeVoxelFast(a, 1, 0, getVoxelFast(a-1, 1, 0));
        //array_trans[a][0] = array[a-1][0];
    }
    // 3 ‰uﬂerer Kreis
    for(int a = 2; a <= 4; a++)
    {
        writeVoxelFast(2, a, 0, getVoxelFast(2, a+1, 0));
        //array_trans[0][a] = array[0][a+1];
        writeVoxelFast(a, 4, 0, getVoxelFast(a+1, 4, 0));
        //array_trans[a][7] = array[a+1][7];
    }

    for(int a = 5; a > 2; a--)
    {
        writeVoxelFast(5, a, 0, getVoxelFast(5, a-1, 0));
        //array_trans[7][a] = array[7][a-1];
        writeVoxelFast(a, 2, 0, getVoxelFast(a-1, 2, 0));
        //array_trans[a][0] = array[a-1][0];
    }
    // 4 ‰uﬂerer Kreis
    for(int a = 3; a <= 3; a++)
    {
        writeVoxelFast(3, a, 0, getVoxelFast(3, a+1, 0));
        //array_trans[0][a] = array[0][a+1];
        writeVoxelFast(a, 3, 0, getVoxelFast(a+1, 3, 0));
        //array_trans[a][7] = array[a+1][7];
    }

    for(int a = 4; a > 3; a--)
    {
        writeVoxelFast(4, a, 0, getVoxelFast(4, a-1, 0));
        //array_trans[7][a] = array[7][a-1];
        writeVoxelFast(a, 3, 0, getVoxelFast(a-1, 3, 0));
        //array_trans[a][0] = array[a-1][0];
    }

    cout << endl;
    cout << "transform" << endl;
    for(int X = 0; X < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; X++) {
        for(int Y = 0; Y < LEDCUBE_NUMBER_OF_LEDS_PER_SIDE; Y++) {
            Voxel = getVoxelFastAusgabe(LEDCUBE_NUMBER_OF_LEDS_PER_SIDE - X - 1, Y, 0);
             printf("%d,", Voxel);
        }
        printf("\n");
    }

    return 0;
}
