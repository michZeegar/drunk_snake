#include "policy.h"

Policy::Policy(const SnakeBodies& snake, const StructureOfStates& structure, const Learning& learn, const std::string& filename)
:mSnake(snake),mStructure(structure),mLearn(learn),mfilename(filename),mPol(mStructure.getTotalNumberOfStates(),'x')
{

}



MOVE Policy::getPolicy(State in){

    if(in.headOnTarget()){return MOVE::X;}
    std::array<State,3> followingStates = {in,in,in};
    std::array<SUCCESSORtyp,3> typS = {SUCCESSORtyp::NONE,SUCCESSORtyp::NONE,SUCCESSORtyp::NONE};
    std::vector<float> correctStatesV;
    std::vector<State> correctStates;
    std::vector<MOVE> correctStatesMOVE;

    followingStates[0].move(MOVE::GERADE);
    followingStates[1].move(MOVE::LINKS);
    followingStates[2].move(MOVE::RECHTS);

    //Checken ob Nachfolger
    for(int i=0; i<3;i++){
        typS[i]=followingStates[i].checkMove();
    }

    for(int i=0; i<3;i++){
        if(typS[i]==SUCCESSORtyp::COLLECT) followingStates[i].collect(mSnake.getRandomStartBody());
        typS[i]=followingStates[i].checkMove();
    }

    //alle VWerte auslesen
    for(int i=0; i<3;i++){
        if(typS[i]!=COLLISION){
            correctStates.push_back(followingStates[i]);
            switch(i){
                case 0:
                    correctStatesMOVE.push_back(MOVE::GERADE);
                    break;
                case 1:
                    correctStatesMOVE.push_back(MOVE::LINKS);
                    break;
                case 2:
                    correctStatesMOVE.push_back(MOVE::RECHTS);
                    break;
            }
        }
    }
    //checken ob alle States Kollision
    if(correctStates.empty()){
      std::cout<<"errorempty"<<std::endl;
        return MOVE::X;
    }
    else{
        //auslesen der Vwerte
        for(auto x :correctStates){
            correctStatesV.push_back(mLearn.mVValues[mStructure.positionFromState(x)]);
        }

        auto it =std::max_element(correctStatesV.begin(),correctStatesV.end());
        std::size_t pos=static_cast<std::size_t>(std::distance(correctStatesV.begin(), it));

        return correctStatesMOVE[pos];
    }
}

void Policy::calculatePolicy(){
    for(std::size_t i=0; i<mStructure.getTotalNumberOfStates(); i++){
        MOVE tmp = getPolicy(mStructure.stateFromPosition(i));
        switch(tmp){
            case MOVE::GERADE:
                mPol[i]='g';
                break;
            case MOVE::RECHTS:
                mPol[i]='r';
                break;
            case MOVE::LINKS:
                mPol[i]='l';
                break;
            default:
                mPol[i]='x';
                break;
        }
    }
}

char Policy::getAction(State in) const{
    std::size_t pos = mStructure.positionFromState(in);
    return mPol[pos];

}

void Policy::writeToFile() const{
    std::ofstream myfile;
    myfile.open (mfilename);

    for(auto x :mPol){
        myfile << x;
    }
    myfile<<std::endl;
    myfile.close();
}
