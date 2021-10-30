#pragma once
#include <random>

class RandomGen{
    private:
        std::random_device rD;
        std::mt19937 randGen;
        

    public:
        RandomGen();
        std::size_t getRandNumber(std::size_t intervallBegin,std::size_t intervallEnd);
};

extern RandomGen rGen;