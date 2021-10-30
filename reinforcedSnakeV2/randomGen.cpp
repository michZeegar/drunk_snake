#include "randomGen.h"

RandomGen rGen;

RandomGen::RandomGen():randGen(rD()){

}

std::size_t RandomGen::getRandNumber(std::size_t intervallBegin,std::size_t intervallEnd){
    std::uniform_int_distribution<std::size_t> dis(intervallBegin,intervallEnd);
    return dis(randGen);
}

