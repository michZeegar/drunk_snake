#include <iostream>
#include <bitset>
#include "../snakeBodies.h"
#include "../utility.h"


int main(){

    SnakeBodies s(2,4);
    std::cout<<"nrBodies"<<s.nrOfBodies()<<std::endl;

    for(uint i = 0;i<s.nrOfBodies();i++){
        std::cout<<std::bitset<24>(s.getBodyFromPosition(i))<<std::endl;
    }

    return 0;
}
