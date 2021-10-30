#include "learning.h"
#include <iostream>
#include <bitset>
Learning::Learning(uint8_t feldDim, uint8_t minSnake, uint8_t maxSnake,uint nrOfUpdates,const SnakeBodies& snake,const StructureOfStates& structure)
:mNrOfUpdates(nrOfUpdates),mDiscount(0.9),mW(0.8),mWnot(0.2),mCostCollision(-1000.0),mCostCollection(50.0),mMinLength(minSnake)
,mSnake(snake),mStructure(structure),mVValues(mStructure.getTotalNumberOfStates(),0.0)
{
	mCostStep = -minSnake;
 	v(max_nr_successor,0.0)
    //updateVVector();
}

float Learning::getMoveCost(SUCCESSORtyp s) {
    if(s == SUCCESSORtyp::COLLISION) return mCostCollision;
    else if(s == SUCCESSORtyp::COLLECT) return mCostCollection;
    else return -static_cast<float>(len);
}

void Learning::updateCostMove(){
	// Set Moving cost to current snake length
	mCostStep = -len_snake;
	mCostCollection = 10 * len_snake;
}

void Learning::printTyp(SUCCESSORtyp x) const{
  switch(x){
    case SUCCESSORtyp::COLLISION:std::cout<<"COLLISION Typ"<<std::endl; break;
    case SUCCESSORtyp::COLLECT:std::cout<<"COLLECT Typ"<<std::endl;break;
    case SUCCESSORtyp::NONE: std::cout<<"NONE Typ"<<std::endl;break;
  }
}

void Learning::update_len_snake(bool reset){
	if reset{
		len_snake = mMinLength;
	} else {
		len_snake++;
	}
	updateCostMove();
}


void Learning::updateVElement(int idx_state_space){
	// Getting State to update
	State akt_state = mStructure.stateFromPosition(idx_state_space);
	// Init vector with following States
	std::array<State,3> following_states = {aktState,aktState,aktState};
	std::array<std::size_t,3> idx_fState = {0,0,0};

	// Init Vector with Succesor states typ --> like: Collison, Collect, None/Step
    std::array<SUCCESSORtyp,3> typS = {SUCCESSORtyp::NONE,SUCCESSORtyp::NONE,SUCCESSORtyp::NONE};
	// will contain the average values of following states after collect
	std::array<float,3> averageNewTargetValue = {0.0,0.0,0.0};
	// will contain the check if reset occurs through collect at maxLength or Collision or Collision after Collect  --> 0 => no reset ; 1 => Collection; 2 => Collision
	std::array<int,3> resetOccured = {0,0,0};

	//state mit head und ziel auf gleicher Position auslassen
	if(aktState.headOnTarget()) return;

	// Getting succesor of states  --> TODO: checking Move function
	followingStates[0].move(MOVE::GERADE);
	followingStates[1].move(MOVE::LINKS);
	followingStates[2].move(MOVE::RECHTS);

	// filling the successor typs of all 3 possibles moves
	std::array<SUCCESSORtyp,3> typ_succesor = {following_states[0].checkMove()
									  ,following_states[1].checkMove()
									  ,following_states[2].checkMove()};



	// retrieving snake body length from state index
	int snake_body_length = aktState.getLenOfBody();

	for(int i=0; i<3; i++) {
		// Checking if one of the possible states would result into a collision
		if(typ_succesor[i] == SUCCESSORtyp::COLLISION){
			resetOccured[i] =  2;
			update_len_snake(reset=true);
		}
		if(typ_succesor[i] == SUCCESSORtyp::COLLECT){
			if(len_snake == mMaxLength)
				resetOccured[i] = 1;
			if following_states


		}
	}
}
