#pragma once
#include <cstdint>
#include <vector>
#include <array>
#include <string>
#include <utility> 
#include <algorithm>
#include "enums.h"
#include "vElement.h"

class Snake{
    private:
        const uint8_t mFeldDim;
        const uint8_t mMinSnake; //mind.2 head+body
        const uint8_t mMaxSnake;
        const uint8_t mMaxSnakeBody;
        std::vector<uint32_t> mBodies;
        std::vector<uint16_t> mHeadsTargets;


        bool hasCollision(uint64_t state);
        bool equalTargetHead(uint64_t state);
        bool equalTargetHead(uint16_t stateHTPart);
        uint64_t convertStrBodyToUInt64(std::string b,uint64_t length);
        uint32_t convertStrBodyToUInt32(std::string b,uint32_t length);
        int createBodies();
        int createHeadTargets();
        
    public:
        void createVElements(std::vector<VElement>& v, double defValue);
        void move(uint64_t stateToMove, BIT move);
        void successors(uint64_t aktState,std::vector<uint64_t>& out);
        uint64_t newRandSnake();

        Snake(uint8_t feldDim, uint8_t minSnake, uint8_t maxSnake);
};

