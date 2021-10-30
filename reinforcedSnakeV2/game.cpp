#include "game.h"
#include <utility>

Game::Game(uint8_t feldDim, uint8_t minSnake, uint8_t maxSnake, const std::string & filename)
:mSnake(minSnake,maxSnake),mStructure(feldDim,minSnake,maxSnake,mSnake),mAktState(feldDim,maxSnake,0,0,0,0,0),mFile(filename),mfeldDim(feldDim),mMaxSnake(maxSnake){
    mAktState.setRandomStartState(mSnake.getRandomStartBody());
}

void Game::readInPolicy(){
    std::ifstream fileStream;
    fileStream.open(mFile);
    std::getline(fileStream,mPolicy);
    fileStream.close();
}

CONNECTgui Game::makeMove(){

    uint8_t lenOfBodyBefore = mAktState.getLenOfBody();
    char move = mPolicy[mStructure.positionFromState(mAktState)];


    MOVE m;
    switch(move)
    {
        case 'g':
            m =MOVE::GERADE;
            break;
        case 'r':
            m =MOVE::RECHTS;
            break;
        case 'l':
            m =MOVE::LINKS;
            break;
        default:
            std::cout<<"oops!!"<<std::endl;
            return {0,0,0,0,0,true,true,""};
            break;
    }



    // if(rGen.getRandNumber(0,10)<2){
    //    m = uMOVE::getDrunkMove(m);
    // }
    bool resetAfterCollect;


    mAktState.move(m);
    SUCCESSORtyp typ = mAktState.checkMove();
    std::string body = "";
    if(typ==SUCCESSORtyp::COLLECT){
        resetAfterCollect= mAktState.collect(mSnake.getRandomStartBody());
        uCV::convertUInt32toStr(mAktState.getBody(),body);

        return {mAktState.getXHead(),mAktState.getYHead(),
            mAktState.getXTarget(),mAktState.getYTarget()
            ,lenOfBodyBefore,resetAfterCollect, true,
            body};
    }
    else if(typ == SUCCESSORtyp::COLLISION){
        mAktState.setRandomStartState(mSnake.getRandomStartBody());
        uCV::convertUInt32toStr(mAktState.getBody(),body);

        return {mAktState.getXHead(),mAktState.getYHead(),
            mAktState.getXTarget(),mAktState.getYTarget()
            ,lenOfBodyBefore,true, false,
            body};
    }
    else{
        uCV::convertUInt32toStr(mAktState.getBody(),body);
        return {mAktState.getXHead(),mAktState.getYHead(),
            mAktState.getXTarget(),mAktState.getYTarget()
            ,lenOfBodyBefore,false, false,
            body};
    }
}

void Game::print_game(){
	CONNECTgui g = makeMove();

	// Conversion of the body element  into the illustration symbol
	// --> "."" for the empty field,
	std::vector<std::vector<char>> v(mfeldDim,std::vector<char>(mfeldDim,'.'));

	std::pair<int,int> e = {g.headX,g.headY};
	for(auto x : g.body){
        switch(x){
            case 'u' :      e.second -= 1; break;
            case 'd':    e.second += 1; break;
            case 'r' :   e.first += 1; break;
            case 'l' :    e.first -=1; break;
            default : break;
        }

		if(e.first<0) e.first += (mfeldDim);
		else if(e.first>=mfeldDim) e.first=e.first-mfeldDim;

		if(e.second<0) e.second += (mfeldDim);
		else if(e.second>=mfeldDim) e.second=e.second-mfeldDim;

		v[e.second][e.first]='O';
    }

	v[g.headY][g.headX]='X';
  if(v[g.targetY][g.targetX]!='O'){
    	v[g.targetY][g.targetX]='*';
  }


	for(auto &x :v){
		for(auto z:x){
			std::cout<<" "<<z<<" ";
		}
		std::cout<<std::endl;
	}

  if(g.hasCollect){
    collects++;
  }

  std::cout << "Stats:" << '\n';
  std::cout << "-------" << '\n';
	std::cout<<"Mean LENGTH: "<< mean_length<< std::endl;
	std::cout << "Victories: " << victories << std::endl;
  std::cout << "collects: " << collects <<std::endl;
	std::cout << "Deads:" << deads << std::endl;
  std::cout << "----------------------------------------------------------------" << '\n';


	// for(int i=0; i < mfeldDim; i++){
	// 	for(int j=0; j < mfeldDim; j++){
	// 		//TODO Snake configuration
	// 		std::cout << " ." ;
	// 	}
	// 	std::cout << std::endl;
	// }
}
