#include <iostream>
#include <bitset>
#include <vector>
#include <string>

class StructureOfStates{
    private:
        const uint8_t mFeldDim = 4;
        const uint8_t mMinSnake = 1;
        const uint8_t mMaxSnake = 1;
        std::vector<std::string> body = {"a","b"};


        std::size_t mNrOfBodies = 2;
        std::size_t mNrHeads = 16;
        std::size_t mNrTargets = 16;

    public:

        std::vector<std::string> v;
        StructureOfStates() = default;
        void stateFromPosition(std::size_t pos) const;
        std::size_t positionFromState(uint xT, uint yT, uint xH, uint yH, std::string body) const;
        std::size_t getTotalNumberOfStates() const;
        void createV();
        //StructureOfStates(uint8_t feldDim, uint8_t minSnake, uint8_t maxSnake, const SnakeBodies& snake);
};



void StructureOfStates::createV(){
      for(int x1 = 0; x1<mFeldDim;x1++){
        for(int y1 = 0; y1<mFeldDim;y1++){
          for(int x2 = 0; x2<mFeldDim;x2++){
            for(int y2 = 0; y2<mFeldDim;y2++){
                v.push_back(body[0]+","+std::to_string(x1)+","+std::to_string(y1)+","+std::to_string(x2)+","+std::to_string(y2));
                v.push_back(body[1]+","+std::to_string(x1)+","+std::to_string(y1)+","+std::to_string(x2)+","+std::to_string(y2));

            }
          }
        }
      }
}


void StructureOfStates::stateFromPosition(std::size_t pos) const{
	/* Test Berechnung alle mit angenommen spielfeld von 7x7 Länge 5 min 3*/
	// Finding in which target-header section the  position is --> number between 0-2401 --> can be understood as idx of targer-header section --> xTyTxHyH * nMrofBodies = start of target-header section
    uint64_t xTyTxHyH = pos / mNrOfBodies;
	// Finding the body configuration position inside the target-header section 0-148 --> index of the position inside the target-header section --> start_targer_header_sec + bodyNr = pos
    uint64_t bodyNr = pos % mNrOfBodies;

	//  index of target position of target-header section
    uint64_t xTyT = xTyTxHyH / mNrTargets; // changed to number of target for reusabiltiy of the code
	// index of header position insede the target(!) section
	uint64_t xHyH = xTyTxHyH % mNrHeads;

    uint64_t xT = xTyT / mFeldDim;
    uint64_t yT = xTyT % mFeldDim;

    uint64_t xH = xHyH / mFeldDim;
    uint64_t yH = xHyH % mFeldDim;

    std::cout<<"From Pos "<<pos<<" calculated: "<<xT<<","<<yT<<","<<xH<<","<<yH<<","<<body[bodyNr]<<std::endl;

}

std::size_t StructureOfStates::positionFromState(uint xT, uint yT, uint xH, uint yH, std::string body) const{
	// Calc the index of the target inside the target-header section
    std::size_t xTyT = yT + mFeldDim * xT;
	// Calc the index of the header position inside the target section
    std::size_t xHyH = yH   + mFeldDim * xH;

	// Calc the index of the start of the target-header section inside the hole state space vector
    std::size_t xTyTxHyH = xTyT * mNrHeads + xHyH;

    uint x = 2;
    if(body== "a"){
      x = 0;
    }else{
      x = 1;
    }

	// calc the the total position inside the hole target-header section
    std::size_t pos = xTyTxHyH * mNrOfBodies + x;

    return pos;
}

int main(){
  StructureOfStates s;
  s.createV();
  int y= 0;
for (auto x: s.v){
    std::cout<<x<<std::endl;
    s.stateFromPosition(y);
    y++;
}
std::cout<<std::endl;
  auto z=s.positionFromState(0,1,0,1,"a");
  std::cout<<s.v[z]<<std::endl;

  return 0;
}
