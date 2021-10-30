#include "algorithm.h"
#include "enums.h"

std::vector<VElement>::iterator Algorithm::findVIter(uint64_t state){
    return std::find(mV.begin(),mV.end(),state);
}

float Algorithm::calculateCost(uint64_t succState){//length aus succ state
    return 0.0;
}

void Algorithm::updateVElement(std::vector<VElement>::iterator it){
    std::vector<uint64_t> sucStates(3,0); //links, gerade, rechts
    std::vector<std::vector<VElement>::iterator> sucIt;
    std::vector<float> sucCost;
    sucCost.reserve(3);
    sucIt.reserve(3);
    std::vector<float> vCalc(3,0.0);

    //nachfolger berechnen
    mS.successors(it->mStateId,sucStates);

    //iteratoren der nachfolger bestimmen
    for(auto x : sucStates){
        sucIt.emplace_back(findVIter(x));
    }

    //Kosten berechnen
    for(auto x : sucStates){
        sucCost.emplace_back(calculateCost(x));
    }

    //Mögliche Collisionen führen zu neuem iter
    for(auto& x: sucIt){
        if(x==mV.end()){
            x = findVIter(mS.newRandSnake());
        }
    }

    vCalc[0] =      mW * (sucCost[0] + mDiscount * (sucIt[0]->mVvalue)
                +   mWnot * (sucCost[1]) + mDiscount * (sucIt[1]->mVvalue));

    vCalc[1] =  mW * (sucCost[1] + mDiscount * (sucIt[1]->mVvalue)
                +   mWnot * (sucCost[2]) + mDiscount * (sucIt[2]->mVvalue));

    vCalc[2] = (sucCost[2] + mDiscount * (sucIt[2]->mVvalue));
}

void Algorithm::updateV(){ 
    for(uint ctr = 0; ctr<mNrOfUpdates;ctr++){ 
        for(auto it=mV.begin();it!=mV.end();it++){
            updateVElement(it);
        }
    }
} 

void Algorithm::calculateActions(){//final step
    for(auto& x : mV){
        std::vector<uint64_t> sucStates(3,0); 
        std::vector<std::vector<VElement>::iterator> sucIt;
        std::vector<float> vValues;
        uint minV = 0;
        mS.successors(x.mStateId,sucStates);


        for(auto z: sucStates){
            sucIt.emplace_back(findVIter(z));
        }

        for(auto z: sucIt){
            vValues.push_back(z->mVvalue);
        }

        auto it = std::min_element(vValues.begin(),vValues.end());
        auto it2 = vValues.begin();
        while(it2!=it){
            it2++;
            minV++;
        }
        switch(minV){
            case 0: x.mAction = L;
            case 1: x.mAction = G;
            case 2: x.mAction = R;
            default: std::cout<<"ERROR"<<std::endl;
        }
    }
} 

MOVE Algorithm::getAction(uint64_t state){
    auto it = std::find(mV.begin(),mV.end(),state);
    if(it!=mV.end()){
        return it->mAction;
    }
    return F;
}

Algorithm::Algorithm(uint NrOfUpdates,uint8_t feldDim, uint8_t minSnake, uint8_t maxSnake)
: mNrOfUpdates(NrOfUpdates),mDiscount(0.9),mW(0.8),mWnot(0.2),mCostCollision(10.0),mS(feldDim,minSnake,maxSnake)
{   
    mS.createVElements(mV,1.0);
    updateV();
    calculateActions();
} 
         