#pragma once
#include <fstream>
#include <iostream>

#include "state.h"
#include "structureOfStates.h"
#include "randomGen.h"
#include "snakeBodies.h"
#include "utility.h"

struct CONNECTgui{
    uint8_t headX;
    uint8_t headY;
    uint8_t targetX;
    uint8_t targetY;
    uint8_t lengthBefore;
    bool hasCollision;
    bool hasCollect;
    std::string body;
};

class Game{
    private:
        SnakeBodies mSnake;
        StructureOfStates mStructure;
        State mAktState;
        std::string mFile;
        std::string mPolicy;
		uint8_t mfeldDim;
    uint8_t mMaxSnake;

		// Init print game
		float mean_length = 0;
    int collects = 0;
		int victories = 0;
		int deads = 0;

    public:
        void readInPolicy();
        CONNECTgui makeMove(void);

        Game(uint8_t feldDim, uint8_t minSnake, uint8_t maxSnake, const std::string & filename);

		void print_game();

};
