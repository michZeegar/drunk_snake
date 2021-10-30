#pragma once
#include "snake.h"

#include <array>

class Algorithm{
    private:
        
        const uint  mNrOfUpdates;
        const float mDiscount;
        const float mW;
        const float mWnot;
        const float mCostCollision;
        Snake mS;
        std::vector<VElement> mV;
        
        std::vector<VElement>::iterator findVIter(uint64_t state);
        float calculateCost(uint64_t succState); //length aus succ state
        void updateVElement(std::vector<VElement>::iterator it);

        void updateV(); //nrOfUpdates beachten
        void calculateActions(); //final step

    public:
        MOVE getAction(uint64_t state);
        Algorithm(uint NrOfUpdates,uint8_t feldDim, uint8_t minSnake, uint8_t maxSnake); //initV uodateV calculateActions()   
};