#include "../utility.h"
#include <iostream>
#include <bitset>

void printUINT32(uint32_t v){
  std::cout<<std::bitset<32>(v)<<std::endl;
  std::cout<<"            "<<std::bitset<20>(v)<<std::endl;
}

int main(){

  std::vector<std::string> bodies = {"rdlu","dddd","rrrr","llll","uuud","uuuuuuuuu","u","uruuul","ud","rl","uuud","dddddrul","lllllllll"};
  std::vector<uint32_t> bodiesUINT;
  std::vector<std::string> bodiesR;

  //conversion
  for(auto b :bodies){
    std::cout<<b<<" L:"<<b.length()<<","<<std::bitset<4>(b.length())<<std::endl;
    uint32_t tmp =uCV::convertStrBodyToUInt32(b);
    printUINT32(tmp);
    bodiesUINT.push_back(tmp);
  }

  std::cout<<"back:"<<std::endl;
  for(auto b: bodiesUINT){
    std::string tmp;
    uCV::convertUInt32toStr(b,tmp);
    bodiesR.push_back(tmp);
    printUINT32(b);
    std::cout<<tmp<<std::endl;
  }

  if(bodies==bodiesR){
    std::cout<<"reconvert gleich ursprung"<<std::endl;
  }


  //getDrunkMove
  std::vector<MOVE> v;
  v.push_back(uMOVE::getDrunkMove(MOVE::GERADE));
  v.push_back(uMOVE::getDrunkMove(MOVE::RECHTS));
  v.push_back(uMOVE::getDrunkMove(MOVE::LINKS));

  int element = 0;
  for(auto x:v){

    switch(x){
      case MOVE::GERADE: std::cout<< "E"<<element<<":gerade"<<std::endl; break;
      case MOVE::RECHTS: std::cout<< "E"<<element<<":rechts"<<std::endl;break;
      case MOVE::LINKS:  std::cout<< "E"<<element<<":links"<<std::endl;break;
      default :  std::cout<< "E"<<element<< " error"<<std::endl;break;
    }
    element++;
  }

  //COLLISION
  for(uint i=0; i<bodies.size();++i){
    std::cout<<bodies[i]<<" COLLISION: ";
    if(uCHECK::hasCollision(bodiesUINT[i])==true){
      std::cout<<"true"<<std::endl;
    }else{
      std::cout<<"false"<<std::endl;
    }
}
  return 0;
}
