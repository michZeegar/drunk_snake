#pragma once

#include <vector>
#include <array>
#include <algorithm>
#include <iostream>

#include "defEnums.h"
#include "snakeBodies.h"
#include "structureOfStates.h"



class Learning{
    private:
        int  mNrOfUpdates;
        float mDiscount;
        float mW;
        float mWnot;

		// Rewards for Value Iteration
        float mCostCollision;
        float mCostCollection;
		float mCostStep;

		// minmum length of a snake
        int mMinLength;

		int mMaxLength; //!< contains the maximal length of a snake
		int mFeldDim; //!< contains the field dimension


		// length of the current snake
		int len_snake;

		// maximale number of successor typS
		int max_nr_successor;

		// references to Snake bodies class and structure class
        const SnakeBodies& mSnake;
        const StructureOfStates& mStructure;

		// successor states
		std::vector<float> v;

		// Update length of the snake body
		void update_len_snake(bool reset);

		//updating the cost of the moving
		void updateCostMove();
		// Give Back the current moving cost/reward
        float getMoveCost(SUCCESSORtyp s); //length aus succ state
    public:
		/**
		*		Value Iteration update step --> privat fucntion
		*/
        void updateVElement(std::size_t pos);

		// state-space vector
        std::vector<float> mVValues;#

		// updating state vector in section btw begin and end
        void updateVVector(std::size_t begin, std::size_t end); //nrOfUpdates beachten

		// printing typ of successor ---> just for debbuging
		void printTyp(SUCCESSORtyp x) const;
        /**
         * @brief Constructor of Learning class
         * @param feldDim  dimension of field
         * @param minSnake minimal snake length
         * @param maxSnake maximal snake length (not used)
         * @param nrOfUpdates number of times updates should be executed (notUsed)
         * @param snake reference to SankeBodies Object
         * @param structure reference to StructureOfStates Object
         */
        Learning(uint8_t feldDim, uint8_t minSnake, uint8_t maxSnake,uint nrOfUpdates,const SnakeBodies& snake, const StructureOfStates& structure); //initV uodateV calculateActions()
};
