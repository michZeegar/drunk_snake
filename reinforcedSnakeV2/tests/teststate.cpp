#include "../state.h"
#include <iostream>
#include <bitset>

void printUINT32(uint32_t v){
  std::cout<<std::bitset<32>(v)<<std::endl;
  //std::cout<<"            "<<std::bitset<20>(v)<<std::endl;
}

int main(){

  uint8_t dim=5;
  uint32_t bodyA = uCV::convertStrBodyToUInt32("uuu");
  State s(dim,4,0,1,2,3,bodyA);


  for(uint8_t i= 0; i < dim; i++){
    std::cout<<"ADD"<<(int)i<<":"<<(int)s.addKoord(i)<<std::endl;
  }
  for(uint8_t i= 0; i < dim; i++){
    std::cout<<"SUB"<<(int)i<<":"<<(int)s.subKoord(i)<<std::endl;
  }

  s.printState();

  std::cout<<std::endl;
  std::cout<<"Ziel"<<"x: "<< int(s.getXTarget()) <<"y: "<<int(s.getYTarget());
  std::cout<<" Kopf"<<"x: "<< int(s.getXHead()) <<"y: "<<int(s.getYHead());

  std::string t;
  uCV::convertUInt32toStr(s.getBody(),t);
  std::cout<<" Body: "<<t<<" l: "<<(int)s.getLenOfBody()<<std::endl;


  std::cout<<std::endl;
  uint32_t bodyb = uCV::convertStrBodyToUInt32("uuuuuuuuu");
  State s2(15,10,0,1,2,3,bodyb);
  std::string t2;
  uCV::convertUInt32toStr(s2.getBody(),t);
  std::cout<<" Body: "<<t2<<" l: "<<(int)s2.getLenOfBody()<<std::endl;

  std::cout<<std::endl;
  uint32_t bodyc = uCV::convertStrBodyToUInt32("uuuuu");
  State s3(15,10,0,1,2,3,bodyc);
  std::string t3;
  uCV::convertUInt32toStr(s3.getBody(),t);
  std::cout<<" Body: "<<t3<<" l: "<<(int)s3.getLenOfBody()<<std::endl;


  uint8_t DIM = 10;
  uint8_t MAX = 6;
  //test Move
  uint32_t startbody = uCV::convertStrBodyToUInt32("uuuuu");
  uint32_t startbody2 = uCV::convertStrBodyToUInt32("ddddd");
  uint32_t startbody3 = uCV::convertStrBodyToUInt32("rrrrr");
  uint32_t startbody4 = uCV::convertStrBodyToUInt32("lllll");

  State rechtsBefore(DIM,MAX,1,1,1,4,startbody);
  State geradeBefore(DIM,MAX,1,1,1,4,startbody);
  State linksBefore(DIM,MAX,1,1,1,4,startbody);


  std::cout<<"Moves: uu"<<std::endl;

  geradeBefore.printState();
  std::cout<<"Move: gerade"<<std::endl;
  geradeBefore.move(MOVE::GERADE);
  geradeBefore.printState();
  std::cout<<"Move: rechts"<<std::endl;
  rechtsBefore.move(MOVE::RECHTS);
  rechtsBefore.printState();
  std::cout<<"Move: links"<<std::endl;
  linksBefore.move(MOVE::LINKS);
  linksBefore.printState();

  std::cout<<std::endl<<std::endl;

  State rechtsBefore2(DIM,MAX,1,1,1,4,startbody2);
  State geradeBefore2(DIM,MAX,1,1,1,4,startbody2);
  State linksBefore2(DIM,MAX,1,1,1,4,startbody2);


  std::cout<<"Moves: dd"<<std::endl;

  geradeBefore2.printState();
  std::cout<<"Move: gerade"<<std::endl;
  geradeBefore2.move(MOVE::GERADE);
  geradeBefore2.printState();
  std::cout<<"Move: rechts"<<std::endl;
  rechtsBefore2.move(MOVE::RECHTS);
  rechtsBefore2.printState();
  std::cout<<"Move: links"<<std::endl;
  linksBefore2.move(MOVE::LINKS);
  linksBefore2.printState();


  std::cout<<std::endl<<std::endl;
  State rechtsBefore3(DIM,MAX,1,1,1,4,startbody3);
  State geradeBefore3(DIM,MAX,1,1,1,4,startbody3);
  State linksBefore3(DIM,MAX,1,1,1,4,startbody3);


  std::cout<<"Moves: rr"<<std::endl;

  geradeBefore3.printState();
  std::cout<<"Move: gerade"<<std::endl;
  geradeBefore3.move(MOVE::GERADE);
  geradeBefore3.printState();
  std::cout<<"Move: rechts"<<std::endl;
  rechtsBefore3.move(MOVE::RECHTS);
  rechtsBefore3.printState();
  std::cout<<"Move: links"<<std::endl;
  linksBefore3.move(MOVE::LINKS);
  linksBefore3.printState();

std::cout<<std::endl<<std::endl;
  State rechtsBefore4(DIM,MAX,1,1,1,4,startbody4);
  State geradeBefore4(DIM,MAX,1,1,1,4,startbody4);
  State linksBefore4(DIM,MAX,1,1,1,4,startbody4);


  std::cout<<"Moves: ll"<<std::endl;

  geradeBefore4.printState();
  std::cout<<"Move: gerade"<<std::endl;
  geradeBefore4.move(MOVE::GERADE);
  geradeBefore4.printState();
  std::cout<<"Move: rechts"<<std::endl;
  rechtsBefore4.move(MOVE::RECHTS);
  rechtsBefore4.printState();
  std::cout<<"Move: links"<<std::endl;
  linksBefore4.move(MOVE::LINKS);
  linksBefore4.printState();

  uint32_t bodyReset = uCV::convertStrBodyToUInt32("uuuuu");
  uint32_t start = uCV::convertStrBodyToUInt32("lll");
  uint32_t bodyCollision = uCV::convertStrBodyToUInt32("rdlluu");
  uint32_t bodyCollect = uCV::convertStrBodyToUInt32("llll");


  std::cout<<std::endl<<std::endl<<"Collect"<<std::endl;
  State geradeBeforeCollect(DIM,MAX,1,1,0,1,bodyCollect);
  geradeBeforeCollect.printState();
  geradeBeforeCollect.move(MOVE::GERADE);
  geradeBeforeCollect.printState();

  SUCCESSORtyp tmp = geradeBeforeCollect.checkMove();
  switch(tmp){
    case SUCCESSORtyp::COLLECT : std::cout<<"collect"<<std::endl;break;
    case SUCCESSORtyp::NONE : std::cout<<"none"<<std::endl;break;
    case SUCCESSORtyp::COLLISION : std::cout<<"collision"<<std::endl;break;
  }

  bool a =geradeBeforeCollect.collect(start);
  std::cout<<"collect if "<<a<<std::endl;
  geradeBeforeCollect.printState();


  State geradeBeforeCollectReset(DIM,MAX,1,1,1,0,bodyReset);

  geradeBeforeCollectReset.printState();
  geradeBeforeCollectReset.move(MOVE::GERADE);
  geradeBeforeCollectReset.printState();

 tmp = geradeBeforeCollectReset.checkMove();
  switch(tmp){
    case SUCCESSORtyp::COLLECT : std::cout<<"collect"<<std::endl;break;
    case SUCCESSORtyp::NONE : std::cout<<"none"<<std::endl;break;
    case SUCCESSORtyp::COLLISION : std::cout<<"collision"<<std::endl;break;
  }

  bool b = geradeBeforeCollectReset.collect(start);
  std::cout<<"collect if"<<b<<std::endl;
  geradeBeforeCollectReset.printState();





  State geradeBeforeNone(DIM,MAX,1,1,0,0,start);
  geradeBeforeNone.printState();
  geradeBeforeNone.move(MOVE::GERADE);
  geradeBeforeNone.printState();

  tmp = geradeBeforeNone.checkMove();
   switch(tmp){
     case SUCCESSORtyp::COLLECT : std::cout<<"collect"<<std::endl;break;
     case SUCCESSORtyp::NONE : std::cout<<"none"<<std::endl;break;
     case SUCCESSORtyp::COLLISION : std::cout<<"collision"<<std::endl;break;
   }

  State geradeBeforeCollision(DIM,MAX,1,1,0,0,bodyCollision);
  geradeBeforeCollision.printState();
  geradeBeforeCollision.move(MOVE::GERADE);
  geradeBeforeCollision.printState();

  tmp = geradeBeforeCollision.checkMove();
   switch(tmp){
     case SUCCESSORtyp::COLLECT : std::cout<<"collect"<<std::endl;break;
     case SUCCESSORtyp::NONE : std::cout<<"none"<<std::endl;break;
     case SUCCESSORtyp::COLLISION : std::cout<<"collision"<<std::endl;break;
   }












  return 0;
}
