#include "structureOfStates.h"
#include <iostream>
#include <bitset>
StructureOfStates::StructureOfStates(uint8_t feldDim, uint8_t minSnake, uint8_t maxSnake, const SnakeBodies& snake)
// Init variables of structureOfStates
:mFeldDim(feldDim),mMinSnake(minSnake),mMaxSnake(maxSnake),mSnake(snake),mNrOfBodies(mSnake.nrOfBodies()),mNrHeads(feldDim*feldDim),mNrTargets(feldDim*feldDim)
{

}


State StructureOfStates::stateFromPosition(std::size_t pos) const{
	/* Test Berechnung alle mit angenommen spielfeld von 7x7 Länge 5 min 3*/
	// Finding in which target-header section the  position is --> number between 0-2401 --> can be understood as idx of targer-header section --> xTyTxHyH * nMrofBodies = start of target-header section
    uint64_t xTyTxHyH = pos / mNrOfBodies;
	// Finding the body configuration position inside the target-header section 0-148 --> index of the position inside the target-header section --> start_targer_header_sec + bodyNr = pos
    uint64_t bodyNr = pos % mNrOfBodies;

	//  index of target position of target-header section
    uint64_t xTyT = xTyTxHyH / mNrTargets; // changed to number of target for reusabiltiy of the code
	// index of header position insede the target(!) section
	uint64_t xHyH = xTyTxHyH % mNrHeads;

    uint64_t xT = xTyT % mFeldDim;
    uint64_t yT = xTyT / mFeldDim;

    uint64_t xH = xHyH % mFeldDim;
    uint64_t yH = xHyH / mFeldDim;

    return State(mFeldDim,mMaxSnake,static_cast<uint8_t>(xT),static_cast<uint8_t>(yT),
        static_cast<uint8_t>(xH),static_cast<uint8_t>(yH),mSnake.getBodyFromPosition(bodyNr));

}

std::size_t StructureOfStates::positionFromState(const State& s) const{
	// Calc the index of the target inside the target-header section
    std::size_t xTyT = s.getYTarget() * mFeldDim + s.getXTarget();
	// Calc the index of the header position inside the target section
    std::size_t xHyH = s.getYHead()   * mFeldDim + s.getXHead();

	// Calc the index of the start of the target-header section inside the hole state space vector
    std::size_t xTyTxHyH = xTyT * mNrHeads + xHyH;

    if(mSnake.getPositionBody(s.getBody())==std::numeric_limits<std::size_t>::max()){
        std::cout<<"errorOutOfRange"<<std::endl;
        std::string tmp;
        uCV::convertUInt32toStr(s.getBody(),tmp);
        std::cout<<"xyT"<<(int)s.getYTarget()<<"-"<<(int)s.getXTarget()<<"xyH"<<(int)s.getYHead()<<"-"<<(int)s.getXHead()<<"body"<<tmp<<std::endl;
    }

	// calc the the total position inside the hole target-header section
    std::size_t pos = xTyTxHyH * mNrOfBodies + mSnake.getPositionBody(s.getBody());

    return pos;
}

std::size_t StructureOfStates::getTotalNumberOfStates() const{
    return mNrTargets*mNrTargets*mNrOfBodies;
}
