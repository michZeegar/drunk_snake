#pragma once

#include <cstdint>
#include <iostream>
#include "enums.h"

class VElement{
    public: 
        const uint64_t mStateId;
        double mVvalue;
        MOVE mAction;

    public:
        VElement(uint64_t stateId=0,double vValue=0.0):mStateId(stateId),mVvalue(vValue),mAction(F){
        };

        inline bool operator==(const VElement& valueToCmp){
            std::cout<<"a"<<std::endl;
            return this->mStateId==valueToCmp.mStateId;
        };
        inline bool operator==(const uint64_t& valueToCmp){
            std::cout<<"b"<<std::endl;
            return this->mStateId==valueToCmp;
        };
};
