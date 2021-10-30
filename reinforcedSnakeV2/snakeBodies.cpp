#include "snakeBodies.h"
#include <bitset>
#include <iostream>

SnakeBodies::SnakeBodies(uint8_t minSnake, uint8_t maxSnake)
:mMinSnake(minSnake),mMaxSnake(maxSnake)
{
    createBodies();
}

void SnakeBodies::createBodies(){
	/*
		The snake bodies are decoded with a uint32. The configuration can be retrieved as followed from the entry in mBodies.
		[8-Bits unused| 4-Bits Length of snake | 9 x 2 Bit for snakeBodies elements | 2-Bits unused]
		snakeBodies_element are decoded ad followd :
			UP    =  0b0000,
			DOWN  =  0b0001,
			RIGHT =  0b0010,
			LEFT  =  0b0011
	*/
	// max number of snake bodies --> max_snake + min_snake
    mBodies.reserve(25000);

	// possible body directions (point of view: grid map, so up means i direction of y=0, right in directions x=15, ....)
    std::vector<std::string> baseDir = {"u","d","r","l"};
    std::vector<std::string> body1(1,"");
    std::vector<std::string> body2(1,"");
    std::vector<std::string> tmp;
    bool firstVector = true;

	//Looping over each possible snake length
    for(int i = 1; i<mMaxSnake ; i++){
        if(firstVector){
            for(auto j:body1){
                for(auto k: baseDir){
                    tmp.push_back(j+k);
                }
            }
            body2.clear();
            for(std::size_t e = 0;e<tmp.size();e++){
                uint32_t bTemp = uCV::convertStrBodyToUInt32(tmp[e]);
                if(!uCHECK::hasCollision(bTemp)){
                    body2.push_back(tmp[e]);
                }
            }

            if(i>mMinSnake-1){
                for(auto x: body2){
                    mBodies.push_back(uCV::convertStrBodyToUInt32(x));
                }
            }
            else if(i==mMinSnake-1){
                for(auto x: body2){
                    uint32_t placeHolder = uCV::convertStrBodyToUInt32(x);
                    mBodies.push_back(placeHolder);
                    mMinLengthBodies.push_back(placeHolder);
                }
            }

            tmp.clear();

        }else{

            for(auto j:body2){
                for(auto k: baseDir){
                    tmp.push_back(j+k);
                }
            }

            body1.clear();
            for(std::size_t e = 0;e<tmp.size();e++){
                uint32_t bTemp = uCV::convertStrBodyToUInt32(tmp[e]);
                if(!uCHECK::hasCollision(bTemp)){
                    body1.push_back(tmp[e]);
                }
            }

            if(i>mMinSnake-1){
                for(auto x: body1){
                    mBodies.push_back(uCV::convertStrBodyToUInt32(x));
                }
            }
            else if(i==mMinSnake-1){
                for(auto x: body1){
                    uint32_t placeHolder = uCV::convertStrBodyToUInt32(x);
                    mBodies.push_back(placeHolder);
                    mMinLengthBodies.push_back(placeHolder);
                }
            }

            tmp.clear();
        }
        firstVector=!firstVector;
    }
}

std::size_t SnakeBodies::nrOfBodies() const{
    return mBodies.size();
}

uint32_t SnakeBodies::getBodyFromPosition(std::size_t pos) const{
    if(pos > mBodies.size()){
		std::cout<<"Error: Requestet body does not exit --> bodyNr exceeds size of the body vector!!"<<std::endl;
        return 0; //error
    }
    return mBodies[pos];
}

std::size_t SnakeBodies::getPositionBody(uint32_t body) const{

    //std::cout<<"bodyInGetBodi: "<<std::bitset<32>(body)<<std::endl;


    uint32_t b = body;
    uint32_t bLen = (body>>SHIFT::LENGTH & 0xF);
    uint32_t aktShift = SHIFT::BODY;
    aktShift = aktShift - (2*bLen) +2;

    uint32_t mask = 0xFFFFFFFF;
    mask = mask << aktShift;
    b = b & mask;

    //std::cout<<"bodyInGetBodi: "<<std::bitset<32>(body)<<std::endl;


    auto it =std::find(mBodies.begin(),mBodies.end(),b);
    if(it==mBodies.end()){
        return std::numeric_limits<std::size_t>::max();
    }
    return static_cast<std::size_t>(std::distance(mBodies.begin(),it));
}

uint32_t SnakeBodies::getRandomStartBody() const{
    uint32_t body = mMinLengthBodies[rGen.getRandNumber(0,(mMinLengthBodies.size()-1))];
    return body;
}
