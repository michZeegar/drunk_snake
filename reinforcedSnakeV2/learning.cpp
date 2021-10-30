#include "learning.h"
#include <iostream>
#include <bitset>
Learning::Learning(uint8_t feldDim, uint8_t minSnake, uint8_t maxSnake,uint nrOfUpdates,const SnakeBodies& snake,const StructureOfStates& structure)
:mDiscountFactor(0.2),mProbabiltyCorrectMove(0.8),mProbabiltyDrunkMove(0.2),mCostCollision(-100.0),mCostCollection((float)maxSnake*10),mMinLength(minSnake),mMaxLength(maxSnake),mFeldDim(feldDim)
,mAverageStartSuccessorValue(0.0),mSnake(snake),mStructure(structure),mVValues(mStructure.getTotalNumberOfStates(),0.0)
{
  calculatePositionsOfStartStates();
  calculateAverageStartSuccessorValue();
}

void Learning::calculatePositionsOfStartStates(void){
  //idea: create all States and calculate their position

  std::vector<std::pair<uint8_t,uint8_t>> allXYPositions;
  allXYPositions.reserve(mFeldDim*mFeldDim);
  for(uint8_t x = 0; x < mFeldDim; x++){
      for(uint8_t y = 0; y < mFeldDim; y++){
          allXYPositions.emplace_back(x,y);
      }
  }

  for(auto targetXY : allXYPositions){
    for(auto headXY : allXYPositions){
        if(targetXY == headXY) break; // we dont allow state with head on target
        for(auto body : mSnake.mMinLengthBodies){
              std::string tmp;
              uCV::convertUInt32toStr(body,tmp);

              State s(mFeldDim, mMaxLength,targetXY.first,targetXY.second,headXY.first,headXY.second,body);
              positionsOfStartStates.push_back(mStructure.positionFromState(s));
        }
    }
  }
}

void Learning::calculateAverageStartSuccessorValue(void){
  float tmp = 0.0;
  for(auto x: positionsOfStartStates){
    tmp += mVValues[x];
  }
  mAverageStartSuccessorValue = tmp / positionsOfStartStates.size();
}

float Learning::calculateAverageNewTargetValue(std::vector<std::size_t>& v){
    float tmp = 0.0;
    for(auto x: v){
      tmp += mVValues[x];
    }
    return tmp / v.size();
}

void Learning::printTyp(SUCCESSORtyp x) const{
  switch(x){
    case SUCCESSORtyp::COLLISION:std::cout<<"COLLISION Typ"<<std::endl; break;
    case SUCCESSORtyp::COLLECT:std::cout<<"COLLECT Typ"<<std::endl;break;
    case SUCCESSORtyp::NONE: std::cout<<"NONE Typ"<<std::endl;break;
  }
}


float Learning::calCost(SUCCESSORtyp s, uint8_t laenge) const{
    // if(s == SUCCESSORtyp::COLLECT) return mCostCollection;
    // else if(s == SUCCESSORtyp::COLLISION){
    //   return mCostCollision;
    // }else{
    //   return -10;
    // }
    if(s==SUCCESSORtyp::COLLECT) return mCostCollection;
    return -1 * static_cast<float>(laenge);

}


void Learning::updateVElement(std::size_t pos){
  // State needed to be able to calculate States after move
  State aktState = mStructure.stateFromPosition(pos);

  //ignore state with head and target on same position
  if(aktState.headOnTarget()) return;

  // copy aktState three times to be able to make three moves changing the state
  std::array<State,3> followingStates = {aktState,aktState,aktState};
  // calculating the successor States
  followingStates[0].move(MOVE::GERADE);
  followingStates[1].move(MOVE::LINKS);
  followingStates[2].move(MOVE::RECHTS);

  // contains the SUCCESSORtyp of all three moves
  std::array<SUCCESSORtyp,3> typS = {followingStates[0].checkMove()
                                    ,followingStates[1].checkMove()
                                    ,followingStates[2].checkMove()};

  // will contain the Position of the VValue of a State with type NONE
  std::array<std::size_t,3> posFState = {0,0,0};

  // will contain the check if reset occurs through collect at maxLength or Collision or Collision after Collect
  std::array<bool,3> resetOccured = {false,false,false};

  std::array<uint8_t,3> laenge;

  // will contain the average values of following states after collect
  std::array<float,3> averageNewTargetValue = {0.0,0.0,0.0};

  // for all three MOVE possibilities and followingStates
  for(uint64_t i=0; i<3;i++){
    // first check for Collision
    if(typS[i]==SUCCESSORtyp::COLLISION){
      resetOccured[i] = true;
      laenge[i] = mMinLength;
    }
    else if(typS[i]==SUCCESSORtyp::COLLECT){
      // collect needs startBody in case of collect at maxLength (also used for playing), returns true if this happend
      resetOccured[i] = followingStates[i].collectLearning();
      // check if state has collision now
      // if not we have to calculate average VValue of all possible Target Positions for the State
      if(followingStates[i].checkMove()==SUCCESSORtyp::COLLISION){
          typS[i] = SUCCESSORtyp::COLLISION;
          resetOccured[i] = true;
          laenge[i]= mMinLength;
      }
      // if collect doesn't result in reset through maxLengthCollect or collisionAfterCollect or Collision
      else if(!resetOccured[i]){
        State tmp = followingStates[i];
        const uint8_t xHeadTmp = tmp.getXHead();
        const uint8_t yHeadTmp = tmp.getYHead();
        std::vector<std::size_t> positionsOfAllFollowingStates(mFeldDim*mFeldDim,0);
        for(uint8_t xTarget = 0; xTarget < mFeldDim; xTarget++){
          for(uint8_t yTarget = 0; yTarget < mFeldDim; yTarget++){
            // we dont allow head on target
            if(xTarget == xHeadTmp && yTarget == yHeadTmp) break;
            positionsOfAllFollowingStates[xTarget*mFeldDim+yTarget]=mStructure.positionFromState(tmp);
          }
        }
        averageNewTargetValue[i] = calculateAverageNewTargetValue(positionsOfAllFollowingStates);
        laenge[i]=followingStates[i].getLenOfBody();
      }
    }
    else if(typS[i]==SUCCESSORtyp::NONE){
      posFState[i] = mStructure.positionFromState(followingStates[i]);
      laenge[i] = followingStates[i].getLenOfBody();
    }
  }


  // will contain the three different VValues resulting of the three different moves
  std::array<float,3> vCalc;

  //berechnen der möglichen VWerte
  vCalc[0] =      mProbabiltyCorrectMove * (calCost(typS[0],laenge[0])
    +   mDiscountFactor * ((resetOccured[0]) ? mAverageStartSuccessorValue : (typS[0]==SUCCESSORtyp::COLLECT) ? averageNewTargetValue[0] : mVValues[posFState[0]]))
    +   mProbabiltyDrunkMove * (calCost(typS[1],laenge[1])
    + mDiscountFactor * ((resetOccured[1]) ? mAverageStartSuccessorValue : (typS[1]==SUCCESSORtyp::COLLECT) ? averageNewTargetValue[1] : mVValues[posFState[1]]));

  vCalc[1] =  mProbabiltyCorrectMove * (calCost(typS[1],laenge[1])
    + mDiscountFactor * ((resetOccured[1]) ? mAverageStartSuccessorValue : (typS[1]==SUCCESSORtyp::COLLECT) ? averageNewTargetValue[1] : mVValues[posFState[1]]))
    +   mProbabiltyDrunkMove * (calCost(typS[2],laenge[2])
    + mDiscountFactor * ((resetOccured[2]) ? mAverageStartSuccessorValue : (typS[2]==SUCCESSORtyp::COLLECT) ? averageNewTargetValue[2] : mVValues[posFState[2]]));

  vCalc[2] = calCost(typS[2],laenge[2])
    + mDiscountFactor * ((resetOccured[2]) ? mAverageStartSuccessorValue : (typS[2]==SUCCESSORtyp::COLLECT) ? averageNewTargetValue[2] : mVValues[posFState[2]]);



  //größter Vwert wird V da max Kosten
  mVValues[pos]=*std::max_element(vCalc.begin(),vCalc.end());

}

void Learning::updateVVector(std::size_t begin, std::size_t end){
    if(end>mStructure.getTotalNumberOfStates()){
        std::cout<<"errorV"<<std::endl;
    }
    for(std::size_t i = begin; i<= end;i++){
        updateVElement(i);
    }
}
