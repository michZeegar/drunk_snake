#pragma once
#include <cstdint>

#include "utility.h"
#include "defEnums.h"
#include "snakeBodies.h"

class State{
    private:

        const uint8_t mFeldDim;
        const uint8_t mMaxSnake;
        uint8_t mXTarget;
        uint8_t mYTarget;
        uint8_t mXHead;
        uint8_t mYHead;
        uint32_t mBody;





    public:

        uint8_t addKoord(uint8_t val) const;
        uint8_t subKoord(uint8_t val) const;

        uint8_t getXTarget() const;
        uint8_t getYTarget() const;
        uint8_t getXHead() const;
        uint8_t getYHead() const;
        uint32_t getBody() const;
        uint8_t getLenOfBody() const;

        void printState() const;

        bool headOnTarget() const;
        SUCCESSORtyp checkMove() const;

        void setTarget(uint8_t x, uint8_t y);

        void setRandomStartState(uint32_t startBody);
        void setNewTarget();


        void move(MOVE m);
        bool collect(uint32_t startBody);
        bool collectLearning();

        State(uint8_t FeldDim, uint8_t MaxSnake,uint8_t XTarget,
                uint8_t YTarget, uint8_t XHead, uint8_t YHead,uint32_t Body);
};
