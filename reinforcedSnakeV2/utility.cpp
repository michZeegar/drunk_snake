#include "utility.h"

bool uCHECK::hasCollision(uint32_t body){
    const uint32_t maskByte = 0xF; // takes the last 8 bit
    const uint32_t mask2Bit = 0x03; // takes the last two bits
	// read out length of the decoded snake configuration
    uint32_t len = body>>SHIFT::LENGTH & maskByte;
	// Vector for position change of body elements
    std::vector<std::pair<int,int>> bEle(len,{0,0});
    uint32_t aktShift = SHIFT::BODY;

	// Transferring the decoded snake body to a change of positions
    for(auto &e : bEle){
        switch((body>>aktShift) & mask2Bit){
            case BIT::UP :      e = { 0,-1}; break;
            case BIT::DOWN :    e = { 0, 1}; break;
            case BIT::RIGHT :   e = { 1, 0}; break;
            case BIT::LEFT :    e = {-1, 0}; break;
            default : break;
        }
        aktShift-=2;
    }

	// Calculation of the relative position of the body elements
    std::vector<std::pair<int,int>> calc(len+1,{0,0});
    std::pair<int,int> tmp = {0,0};
    for(std::size_t i = 0; i<bEle.size();i++){
        tmp.first = tmp.first   - bEle[i].first;
        tmp.second = tmp.second - bEle[i].second;
        if(std::find(calc.begin(), calc.end(), tmp) != calc.end()){
            return true;
        }
        calc[i+1]=tmp;
    }
    return false;
}

uint32_t uCV::convertStrBodyToUInt32(const std::string& in){
    uint32_t temp = static_cast<uint32_t>(in.length()) << SHIFT::LENGTH;
    uint8_t aktShift = SHIFT::BODY;
	// Parse with moves the body configuration --> OR to get right uint32 decoding
    for(auto letter : in){
        switch(letter){
            case 'u': temp |= (BIT::UP << aktShift); break;
            case 'd': temp |= (BIT::DOWN << aktShift); break;
            case 'r': temp |= (BIT::RIGHT << aktShift); break;
            case 'l': temp |= (BIT::LEFT << aktShift); break;
            default: break;
        }
        aktShift-=2;
    }
    return temp;
}

void uCV::convertUInt32toStr(uint32_t in, std::string& out){

    const uint32_t maskByte = 0xFF;
    const uint32_t mask2Bit = 0x03;

    uint32_t len = in>>SHIFT::LENGTH & maskByte;
    uint32_t aktShift = SHIFT::BODY;


    out = "";
    for(uint32_t i=0; i<len;i++){
        switch((in>>aktShift) & mask2Bit){
            case BIT::UP:       out.push_back('u'); break;
            case BIT::DOWN:     out.push_back('d'); break;
            case BIT::RIGHT:    out.push_back('r'); break;
            case BIT::LEFT:     out.push_back('l'); break;
            default:                                break;
        }
        aktShift-=2;
    }
}

MOVE uMOVE::getDrunkMove(MOVE m){
    if(m==MOVE::GERADE) return MOVE::RECHTS;
    else if(m==MOVE::RECHTS) return MOVE::RECHTS;
    else return MOVE::GERADE;
}
