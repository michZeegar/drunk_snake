#pragma once

#include <vector>
#include <array>
#include <algorithm>
#include <iostream>

#include "defEnums.h"
#include "snakeBodies.h"
#include "structureOfStates.h"


// Learning class contains the Algorithm and Methods to calculate the V-Values,
// but it doesn't calculate the Policy out of this Values
/**
 * @brief The Learning class
 *
 *  Learning class contains the Algorithm and Methods to calculate the V-Values,
 *  but it doesn't calculate the Policy out of this Values
 *
 */
class Learning{
    private:
        const float mDiscountFactor; //!< contains the discount factor, set in constructor
        const float mProbabiltyCorrectMove; //!< contains the probabilty of a Making the Move according to action
        const float mProbabiltyDrunkMove; //!< contains the probabilty of a Making the Drunk Move
        const float mCostCollision; //!< contains the cost of a collision
        const float mCostCollection; //!< contains the cost of a collection
        const uint8_t mMinLength; //!< contains the minimal length of a snake
        const uint8_t mMaxLength; //!< contains the maximal length of a snake
        const uint8_t mFeldDim; //!< contains the field dimension

        float mAverageStartSuccessorValue;

        const SnakeBodies& mSnake; //!< Reference on a SnakeBodies Object
        const StructureOfStates& mStructure;  //!< Reference on a StructureOfStates Object

        std::vector<std::size_t> positionsOfStartStates; //!< positions of the VValues of the StartStates, used to calculate VValues after Collision and Collect at maxLength
        /**
         * @brief calculates the cost of a Move, bigger is better
         * cost are smaller zero for collision or no collect, positve for collect
         * @param s type of state resulting of a move  (for example collision)
         * @param lenOfState contains the length of the state resulting of a move
         * @return cost of a move
         */
        float calCost(SUCCESSORtyp s, uint8_t laenge) const; //length aus succ state
    public:
        /**
         * @brief updates the VValue of a single State stored at Position of the mVValues vector
         * @param pos Position of the State to calculate in the mVValues vector
         */
        void updateVElement(std::size_t pos);
        /**
         * @brief calculates all Positions of the StartStates needed for VValue update
         */
        void calculatePositionsOfStartStates(void);


    public:
        std::vector<float> mVValues; //!< cotains all VValues for existing states

        /**
         * @brief calculates average VValue of all StartStates
         */
        void calculateAverageStartSuccessorValue(void);

        /**
         * @brief  calculates the Average VValue of all possible Target Positions for the State
         * @param vector containing the positions of the State with possible Target Positions
         * @return average value
         */
        float calculateAverageNewTargetValue(std::vector<std::size_t>& v);
        /**
         * @brief updates a segment of the VValues vector
         * @param position of mVValues, where the updates should begin
         * @param position of mVValues, where the updates should end (including position)
         */
        void updateVVector(std::size_t begin, std::size_t end);


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
