#include "state.h"
#include <iostream>
#include <bitset>

uint8_t State::addKoord(uint8_t val) const{
    if(val == (mFeldDim-1)) return 0;
    else return ++val;

}

uint8_t State::subKoord(uint8_t val) const{
    if(val == 0) return mFeldDim-1;
    else return --val;
}

uint8_t State::getLenOfBody() const{
    return static_cast<uint8_t>((mBody>>SHIFT::LENGTH & 0xF));
}

uint8_t State::getXTarget() const{
    return mXTarget;
}

uint8_t State::getYTarget() const{
    return mYTarget;
}

uint8_t State::getXHead() const{
    return mXHead;
}

uint8_t State::getYHead() const{
    return mYHead;
}

uint32_t State::getBody() const{
    return mBody;
}


bool State::headOnTarget() const{
    if((mXHead==mXTarget) && (mYHead == mYTarget)) return true;
    else return false;
}

SUCCESSORtyp State::checkMove() const{
    if(uCHECK::hasCollision(mBody)) return SUCCESSORtyp::COLLISION;
    else if(headOnTarget()) return SUCCESSORtyp::COLLECT;
    else return SUCCESSORtyp::NONE;
}

void State::setTarget(uint8_t x, uint8_t y){
    mXTarget = x;
    mYTarget = y;
}

void State::setRandomStartState(uint32_t startBody){

    mXHead = rGen.getRandNumber(0,mFeldDim-1);
    mYHead = rGen.getRandNumber(0,mFeldDim-1);

    do{
        mXTarget = rGen.getRandNumber(0,mFeldDim-1);
        mYTarget = rGen.getRandNumber(0,mFeldDim-1);
    }while(mXHead == mXTarget && mYHead == mYTarget);

    mBody = startBody;
}

void State::setNewTarget(){
   do{
       mXTarget = rGen.getRandNumber(0,mFeldDim-1);
       mYTarget = rGen.getRandNumber(0,mFeldDim-1);
   }while(mXHead == mXTarget && mYHead == mYTarget);
}

void State::move(MOVE m){
   uint32_t b = mBody & 0xFFFFF;
   uint32_t len = mBody & 0xF00000;
   b = b >> 2;
   //letzes element vergessen
   switch((mBody>>SHIFT::BODY)&0x03){
       case BIT::UP:
               switch(m){
                    case MOVE::GERADE:
                        mYHead = addKoord(mYHead);
                        b = b | (BIT::UP << SHIFT::BODY);
                        break;
                    case MOVE::LINKS:
                        mXHead = addKoord(mXHead);
                        b = b | (BIT::LEFT << SHIFT::BODY);
                        break;
                    case MOVE::RECHTS:
                        mXHead = subKoord(mXHead);
                        b = b | (BIT::RIGHT << SHIFT::BODY);
                        break;
                    default:
                        break;
               }
               break;
       case BIT::DOWN:
               switch(m){
                    case MOVE::GERADE:
                        mYHead = subKoord(mYHead);
                        b = b | (BIT::DOWN << SHIFT::BODY);
                        break;
                    case MOVE::LINKS:
                        b = b | (BIT::RIGHT << SHIFT::BODY);
                        mXHead = subKoord(mXHead);
                        break;
                    case MOVE::RECHTS:
                        mXHead = addKoord(mXHead);
                        b = b | (BIT::LEFT << SHIFT::BODY);
                        break;
                    default:
                        break;
               }

               break;
       case BIT::LEFT:
               switch(m){
                    case MOVE::GERADE:
                        mXHead = addKoord(mXHead);
                        b = b| (BIT::LEFT << SHIFT::BODY);
                        break;
                    case MOVE::LINKS:
                        mYHead = subKoord(mYHead);
                        b = b | (BIT::DOWN << SHIFT::BODY);
                        break;
                    case MOVE::RECHTS:
                        mYHead = addKoord(mYHead);
                        b = b | (BIT::UP << SHIFT::BODY);
                        break;
                    default:
                        break;
               }
               break;
       case BIT::RIGHT:
               switch(m){
                    case MOVE::GERADE:
                        mXHead = subKoord(mXHead);
                        b = b | (BIT::RIGHT << SHIFT::BODY);
                        break;
                    case MOVE::LINKS:
                        mYHead = addKoord(mYHead);
                        b = b | (BIT::UP << SHIFT::BODY);
                        break;
                    case MOVE::RECHTS:
                        mYHead = subKoord(mYHead);
                        b = b | (BIT::DOWN << SHIFT::BODY);
                        break;
                    default:
                        break;
               }
               break;
       default:
       std::cout <<"default"<<std::endl;break;//error
   }
   mBody = b | len;

}

bool State::collect(uint32_t startBody){
    uint32_t len = getLenOfBody();
    if(len==(mMaxSnake)){
        setRandomStartState(startBody);
        return true;
    }
    else{
        len++;
        setNewTarget();
        mBody = mBody & 0xFFFFF;
        mBody |= len  << SHIFT::LENGTH;
        return false;
    }
}

bool State::collectLearning(){
    uint32_t len = getLenOfBody();
    if(len==mMaxSnake){
        return true;
    }
    else{
        len++;
        mBody = mBody & 0xFFFFF;
        mBody |= len  << SHIFT::LENGTH;
        return false;
    }
}

State::State(uint8_t FeldDim, uint8_t MaxSnake, uint8_t XTarget, uint8_t YTarget, uint8_t XHead, uint8_t YHead, uint32_t Body)
:mFeldDim(FeldDim),mMaxSnake(MaxSnake-1),mXTarget(XTarget),mYTarget(YTarget),mXHead(XHead),mYHead(YHead),mBody(Body)
{

}

void State::printState() const{
    std::cout<<"Ziel x: "<< int(mXTarget) <<" y: "<<int(mYTarget)<<" ";
    std::cout<<"Kopf x: "<< int(mXHead) <<" y: "<<int(mYHead);

    std::string t;
    uCV::convertUInt32toStr(mBody,t);
    std::cout<<" Body: "<<std::bitset<32>(mBody)<< "|" <<t<<std::endl;
}
