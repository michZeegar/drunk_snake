#pragma once
#include <cstdint>

enum SHIFT: uint64_t{
    COORD = 4,
    XY = 8,
    BODY = 18,
    LENGTH = 20        
};

enum BIT: uint32_t {
    UP    =  0b0000,
    DOWN  =  0b0001,
    RIGHT =  0b0010,
    LEFT  =  0b0011
};

enum MOVE:uint8_t{
    LINKS,
    GERADE,
    RECHTS,
    X
};

enum SUCCESSORtyp: uint8_t{
    COLLISION,
    COLLECT,
    NONE
};
