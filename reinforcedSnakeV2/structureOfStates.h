#pragma once

#include <cstdint>
#include <array>

#include "state.h"
#include "snakeBodies.h"


class StructureOfStates{
    private:
        const uint8_t mFeldDim;  	// size of the snake game grid
        const uint8_t mMinSnake; 	//min 2 head+body
        const uint8_t mMaxSnake; 	//max 10
        const SnakeBodies& mSnake;

        std::size_t mNrOfBodies;	// Number of different snake configurations ~25.000
        std::size_t mNrHeads;	    // Number of different heads position  ~255
        std::size_t mNrTargets;		// Number of different target position ~255

    public:
		/**
		 * @brief Function to give back the target and header and snake-body configuration for a
 					index of the state space
		   @return State class object
		 */
        State stateFromPosition(std::size_t pos) const;
		/**
		 * @brief Function to give back a index of the state space  for a specific State obj
			( contains the global the target and header postition in the world and belonging
				snake-body configuration)
		   @return index of for the state space vector
		 */
        std::size_t positionFromState(const State& s) const;
		/**
		 * @brief Function to give back the total number of all possible states
					--> size of state space vector
		 */
        std::size_t getTotalNumberOfStates() const;
		/**
		 * @brief Constructor of the class which is responsible for transferring global grid snake
 					positions
		 */
        StructureOfStates(uint8_t feldDim, uint8_t minSnake, uint8_t maxSnake, const SnakeBodies& snake);
};
