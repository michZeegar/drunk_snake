#pragma once
#include <vector>
#include <utility>
#include <cstdint>

enum SHIFT: uint64_t{
    COORD = 4,
    XY = 8,
    BODY = 16,
    LENGTH = 18,
    HEAD = 22,
    TARGET = 30        
};

enum BIT: uint64_t {
    UP    =  0b0000,
    DOWN  =  0b0001,
    RIGHT =  0b0010,
    LEFT  =  0b0011
};

enum MOVE:uint8_t{
    L,
    G,
    R,
    F
};
       


