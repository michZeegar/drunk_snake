#include "utility.h"
#include "snakeBodies.h"
#include "structureOfStates.h"
#include "learning.h"
#include "policy.h"

#include <bitset>
#include <chrono>

MOVE blub(char x){
  if(x=='g') return MOVE::GERADE;
  else if(x=='r') return MOVE::RECHTS;
  else if(x=='l') return MOVE::LINKS;
  else return MOVE::X;
}


int main(){
    // Init snake config
    uint8_t dim =15;
    uint8_t min = 3;
    uint8_t max = 8;

    // Generation of the possible snakeBodies for the settings
    SnakeBodies body(min,max);
    for(int i=0; i<20; i++){
  		std::string tmp;
  		uCV::convertUInt32toStr(body.mBodies[i],tmp);
  		std::cout<<tmp<<",";
  	}
    std::cout<<"body erstellt: "<< body.nrOfBodies()<< " Elememte"<<std::endl;

    // Generation of the state space vector
    StructureOfStates states(dim,min,max,body);
    std::cout<<"structure erstellt: "<< states.getTotalNumberOfStates()<< " Elememte"<<std::endl;


    // initalize the state space
    Learning learning(dim,min,max,0,body,states);
    std::cout<<"learning erstellt. Beginne Lernen"<<std::endl;

    // Setting the element to update in the state vale space to the complete space
    std::size_t elements=states.getTotalNumberOfStates()-1;

    // Start measuring the time of the learning iteration
    auto start=std::chrono::steady_clock::now();

    // Updating value-state vector i-times
    int nr_iterations = 100;
    for(int i = 0; i<nr_iterations;i++){
        std::cout<<"."<<std::flush;
        learning.updateVVector(0,elements);
        learning.calculatePositionsOfStartStates();

    }
    //learning.updateVElement(24651);
    std::cout<<std::endl;

    // End of the time measurement
    auto duration=std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::steady_clock::now()-start);

    std::cout<<nr_iterations<<" Iterationen geupdated !!"<< std::endl
    << " benötigte Zeit: "<<duration.count()<<"Sekunden."<<std::endl;

    // Displaying the learning time for the Policy
    std::cout<<"lernen fertig"<<std::endl;


    std::cout<<std::endl;
    // Convert state value space to policy --> change filename to your username
    Policy pol(body,states,learning,"/var/tmp/ga45yeh/test.txt");
    pol.calculatePolicy();

    // Testing the policy for one case
    std::string b = "uu";
    // std::cout<<"Target is on position (1,1), header starts at position (3,2)!!!"<<std::endl;
    // State s1(dim,max,1,1,3,2,uCV::convertStrBodyToUInt32(b));
    // s1.printState();
    // std::cout<<"Policy:"<<pol.getAction(s1)<<std::endl;
    // s1.move(blub(pol.getAction(s1)));
    // s1.printState();
    // std::cout<<"Policy:"<<pol.getAction(s1)<<std::endl;
    // s1.move(blub(pol.getAction(s1)));
    // s1.printState();
    // std::cout<<"Policy:"<<pol.getAction(s1)<<std::endl;
    // s1.move(blub(pol.getAction(s1)));
    // s1.printState();
    // std::cout<<"Policy:"<<pol.getAction(s1)<<std::endl;
    // s1.move(blub(pol.getAction(s1)));
    // s1.printState();
    // std::cout<<"Policy:"<<pol.getAction(s1)<<std::endl;
    // s1.move(blub(pol.getAction(s1)));
    // s1.printState();


    // State s2_1(dim,max,1,1,3,1,uCV::convertStrBodyToUInt32(b));
    // std::cout<<"Policy for second state in (3,1): "<<pol.getAction(s2_1)<<std::endl;
    // State s2_2(dim,max,1,1,2,2,uCV::convertStrBodyToUInt32(b));
    // std::cout<<"Policy for second state in (2,2): "<<pol.getAction(s2_2)<<std::endl;
    // State s3_1(dim,max,1,1,2,1,uCV::convertStrBodyToUInt32(b));
    // std::cout<<"Policy for third state in (2,1): "<<pol.getAction(s3_1)<<std::endl;
    // State s3_2(dim,max,1,1,3,0,uCV::convertStrBodyToUInt32(b));
    // std::cout<<"Policy for third state in (3,0): "<<pol.getAction(s3_2)<<std::endl;
    // State s3_3(dim,max,1,1,1,2,uCV::convertStrBodyToUInt32(b));
    // std::cout<<"Policy for third state in (1,2): "<<pol.getAction(s3_3)<<std::endl;
    // State s4(dim,max,1,1,2,0,uCV::convertStrBodyToUInt32(b));
    // std::cout<<"Policy for 4. state in (2,0): "<<pol.getAction(s4)<<std::endl;
    // State s4_1(dim,max,1,1,0,2,uCV::convertStrBodyToUInt32(b));
    // std::cout<<"Policy for 4. state in (0,2): "<<pol.getAction(s4_1)<<std::endl;
    // State s5(dim,max,1,1,1,0,uCV::convertStrBodyToUInt32(b));
    // std::cout<<"Policy for 5. state in (1,0): "<<pol.getAction(s5)<<std::endl;
    // State s5_1(dim,max,1,1,0,1,uCV::convertStrBodyToUInt32(b));
    // std::cout<<"Policy for 5. state in (0,1): "<<pol.getAction(s5_1)<<std::endl;


    // Exporting policy to a .txt file
    pol.writeToFile();

    return 0;
}
