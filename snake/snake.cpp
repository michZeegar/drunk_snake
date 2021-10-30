#include "snake.h"
#include <iostream>


bool Snake::hasCollision(uint64_t state){
    const uint64_t maskByte = 0xFF;
    const uint64_t mask2Bit = 0x03;
    uint64_t len = state>>SHIFT::LENGTH & maskByte;

    std::vector<std::pair<int,int>> bEle(len,{0,0});
    uint64_t aktShift = SHIFT::BODY;
    for(auto &e : bEle){
        switch((state>>aktShift) & mask2Bit){
            case BIT::UP :      e = { 0,-1}; break;
            case BIT::DOWN :    e = { 0, 1}; break;
            case BIT::RIGHT :   e = { 1, 0}; break;
            case BIT::LEFT :    e = {-1, 0}; break;
            default : break;
        }
        aktShift-=2;
    }

    std::vector<std::pair<int,int>> calc(len+1,{0,0});
    std::pair<int,int> tmp = {0,0};
    for(uint64_t i = 0; i<bEle.size();i++){
        tmp.first = tmp.first   - bEle[i].first;
        tmp.second = tmp.second - bEle[i].second;
        if(std::find(calc.begin(), calc.end(), tmp) != calc.end()){
            return true;
        }
        calc[i+1]=tmp;
    }
    return false;
}

bool Snake::equalTargetHead(uint64_t state){
    const uint64_t mask = 0xFF;
    uint64_t target = state>>SHIFT::TARGET & mask;
    uint64_t head   = state>>SHIFT::HEAD   & mask;
    if(target==head){
        return true;
    }
    else{
        return false;
    }
}

bool Snake::equalTargetHead(uint16_t stateHTPart){
    const uint16_t mask = 0xFF;
    uint16_t target = stateHTPart>>SHIFT::XY;
    uint16_t head   = stateHTPart & mask;
    if(target==head){
        return true;
    }
    else{
        return false;
    }
}

uint64_t Snake::convertStrBodyToUInt64(std::string b,uint64_t length){
    uint64_t temp = length << SHIFT::LENGTH;
    uint8_t aktShift = SHIFT::BODY;
    for(auto letter : b){
        switch(letter){
            case 'u': temp |= (BIT::UP << aktShift); break;
            case 'd': temp |= (BIT::DOWN << aktShift); break;
            case 'r': temp |= (BIT::RIGHT << aktShift); break;
            case 'l': temp |= (BIT::LEFT << aktShift); break;
            default: std::cout<<"WHOOPS!!!"<<std::endl; break;
        }
        aktShift-=2;
    }
    return temp;
}

uint32_t Snake::convertStrBodyToUInt32(std::string b,uint32_t length){
    uint32_t temp = length << SHIFT::LENGTH;
    uint8_t aktShift = SHIFT::BODY;
    for(auto letter : b){
        switch(letter){
            case 'u': temp |= (BIT::UP << aktShift); break;
            case 'd': temp |= (BIT::DOWN << aktShift); break;
            case 'r': temp |= (BIT::RIGHT << aktShift); break;
            case 'l': temp |= (BIT::LEFT << aktShift); break;
            default: std::cout<<"WHOOPS!!!"<<std::endl; break;
        }
        aktShift-=2;
    }
    return temp;
}


int Snake::createBodies(){
    mBodies.reserve(25000);

    std::vector<std::string> baseDir = {"u","d","r","l"};
    std::vector<std::vector<std::string>> allBodies(1,baseDir);

    for(std::size_t i = 0; i<mMaxSnakeBody;i++){
        std::vector<std::string> temp;
        for(auto v: allBodies[i]){
            for(auto e: baseDir){
                temp.push_back(v+e);
            }
        }  
        allBodies.push_back(temp);
    }

    //not interested in snakeBodies smaller 2 (1 head )
    for(uint32_t i = (mMinSnake-2); i<mMaxSnakeBody;i++){
        for(auto e : allBodies[i]){
            uint32_t bTemp = convertStrBodyToUInt32(e,i);
            if(!hasCollision(bTemp)){
                mBodies.push_back(bTemp);
            }
        }
    }

    mBodies.shrink_to_fit();
    return mBodies.size();
}

int Snake::createHeadTargets(){
    mHeadsTargets.reserve(mFeldDim*mFeldDim*mFeldDim*mFeldDim);
    for(uint xt = 0; xt<mFeldDim; xt++){
        for(uint yt = 0; yt<mFeldDim; yt++){
            for(uint xh = 0; xh<mFeldDim; xh++){
                for(uint yh = 0; yh<mFeldDim; yh++){
                        uint16_t target = static_cast<uint16_t>(xt)<<SHIFT::COORD 
                                            | static_cast<uint16_t>(yt);
                        uint16_t head = static_cast<uint16_t>(xh)<<SHIFT::COORD 
                                            | static_cast<uint16_t>(yh);
                        uint16_t statePart = target <<SHIFT::XY | head ;
                        mHeadsTargets.push_back(statePart);                        
                }   
            }
        }   
    }
    mHeadsTargets.shrink_to_fit();
    return mHeadsTargets.size();
}

void Snake::createVElements(std::vector<VElement>& v, double defValue){
    v.reserve(mHeadsTargets.size()*mBodies.size());
    for(auto targetHead:mHeadsTargets){
        for(auto body : mBodies){
            v.emplace_back(static_cast<uint64_t>(targetHead)<<SHIFT::HEAD 
                                | static_cast<uint64_t>(body),defValue);
        }
    }

}


void Snake::move(uint64_t stateToMove, BIT move){

}

void Snake::successors(uint64_t aktState,std::vector<uint64_t>& out){

}

uint64_t Snake::newRandSnake(){
    return 0;
}


Snake::Snake(uint8_t feldDim, uint8_t minSnake, uint8_t maxSnake)
:mFeldDim(feldDim),mMinSnake(minSnake),mMaxSnake(maxSnake),mMaxSnakeBody(maxSnake-1){
    createBodies();
    createHeadTargets();
}