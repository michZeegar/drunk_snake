#pragma once

#include <cstdint>
#include <vector>
#include <algorithm>


#include "defEnums.h"
#include "utility.h"
#include "randomGen.h"


class SnakeBodies{
    private:
        const uint8_t mMinSnake; // min 2 head+body
        const uint8_t mMaxSnake; // max 10
           		// Vector for saving the possible body configurations
		/**
		 * @brief Init function for mBodies. Creates all possible snake bodies
		 */
        void createBodies();

    public:
		/**
		 * @brief Function to get the number of possible snake configurations
		 */
        std::vector<uint32_t> mBodies;
        std::vector<uint32_t> mMinLengthBodies; // for generating random start states, needed by learning class
        std::size_t nrOfBodies() const;
        uint32_t getBodyFromPosition(std::size_t pos) const;
        std::size_t getPositionBody(uint32_t body) const;
        uint32_t getRandomStartBody() const;

        SnakeBodies(uint8_t minSnake, uint8_t maxSnake);
};
