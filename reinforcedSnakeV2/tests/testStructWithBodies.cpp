#include "../utility.h"
#include "../snakeBodies.h"
#include "../structureOfStates.h"

#include <vector>
#include <string>
#include <iostream>

int main(){
    // Init snake config
    uint8_t dim = 7;
    uint8_t min = 3;
    uint8_t max = 6;

    // Generation of the possible snakeBodies for the settings
    SnakeBodies body(min,max);
    for(int i=0; i<20; i++){
  		std::string tmp;
  		uCV::convertUInt32toStr(body.mBodies[i],tmp);
  		std::cout<<tmp<<",";
  	}
    std::cout<<"body erstellt: "<< body.nrOfBodies()<< " Elememte"<<std::endl;

    // Generation of the state space vector
    StructureOfStates states(dim,min,max,body);
    std::cout<<"structure erstellt: "<< states.getTotalNumberOfStates()<< " Elememte"<<std::endl;

    std::vector<std::pair<uint8_t,uint8_t>> allXYPositions;
    allXYPositions.reserve(dim*dim);
    for(uint8_t x = 0; x < dim; x++){
        for(uint8_t y = 0; y < dim; y++){
            allXYPositions.emplace_back(x,y);
        }
    }

    for(auto targetXY : allXYPositions){
      for(auto headXY : allXYPositions){
          if(targetXY == headXY) break; // we dont allow state with head on target
          for(auto b : body.mBodies){
                State s(dim, max,targetXY.first,targetXY.second,headXY.first,headXY.second,b);
                states.positionFromState(s);
          }
      }
    }


    return 0;
  }
