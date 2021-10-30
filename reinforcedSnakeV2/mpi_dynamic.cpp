#include "utility.h"
#include "snakeBodies.h"
#include "structureOfStates.h"
#include "learning.h"
#include "policy.h"
#include "../mpi/snake_mpi.h"

#include <bitset>
#include <chrono>


int main(){
	// Starting time measurement of the overall algorithm
	int t_start= MPI_Wtime();

	// Initialize the MPI environment
	Snake_mpi mpi;

    // Init snake config
    uint8_t dim = 5;
    uint8_t min = 2;
    uint8_t max = 5;

    // Generation of the possible snakeBodies for the settings
    SnakeBodies body(min,max);
    std::cout<<"body erstellt: "<< body.nrOfBodies()<< " Elememte"<<std::endl;

    // Generation of the state space vector
    StructureOfStates states(dim,min,max,body);
    std::cout<<"structure erstellt: "<< states.getTotalNumberOfStates()<< " Elememte"<<std::endl;

    // TODO: What dows it do ???
    Learning learning(dim,min,max,0,body,states);
    std::cout<<"learning erstellt. Beginne Lernen"<<std::endl;

    // Setting the element to update in the state vale space to the complete space
    //learning.updateVElement(25439);
    std::size_t elements=states.getTotalNumberOfStates()-1;

	// Giving information about the recieving data
	  mpi.setNrStates(elements);

	  // Getting responible working section for each worker
	  std::size_t start_sec = mpi.getStartSection();
	  std::size_t end_sec = mpi.getEndSection();
	  // Displaying each working section
	  std::cout << "Working section for processor "<< mpi.processor_name << "with rank "<< mpi.world_rank<< " von "<< start_sec<< " bis "<< end_sec << '\n';

    // Start measuring the time of the learning iteration
    auto time_learning_start = MPI_Wtime();
	int t1 = 0;
	int t1_1 = 0;
    // Updating value-state vector i-times
    int nr_iterations = 10000;
    for(int i = 0; i<nr_iterations;i++){
        learning.updateVVector(start_sec,end_sec);
		// Starting time measurement of the communication
	    t1 += MPI_Wtime();

		// update the dummy data in each processor
		mpi.updateValueSpace(learning.mVValues, MPI_FLOAT, MPI_COMM_WORLD);

	    // END time measurement for the communication
	    t1_1 += MPI_Wtime();
    }

    // End of the time measurement
    auto duration=MPI_Wtime() - time_learning_start;

    std::cout<<nr_iterations<<" Iterationen geupdated !!"<< std::endl
    << " benötigte Zeit: "<<duration<<std::endl;
	std::cout<< "'Average communication time per iteration ': "<<t1_1 - t1<<std::endl;

    // Displaying the learning time for the Policy
    std::cout<<"lernen fertig"<<std::endl;

	mpi.endMpiCommunication(learning.mVValues);
    // Convert state value space to policy
	if (mpi.world_rank == 0){
		Policy pol(body,states,learning,"test.txt");
		pol.calculatePolicy();
		// Testing the policy for one case
		std::string b = "u";
		std::cout<<"Target is on position (1,1), header starts at position (3,2)!!!"<<std::endl;
		State s1(dim,max,1,1,3,2,uCV::convertStrBodyToUInt32(b));
		std::cout<<"Policy for inital state in (3,2): "<<pol.getAction(s1)<<std::endl;
		State s2_1(dim,max,1,1,3,1,uCV::convertStrBodyToUInt32(b));
		std::cout<<"Policy for second state in (3,1): "<<pol.getAction(s2_1)<<std::endl;
		State s2_2(dim,max,1,1,2,2,uCV::convertStrBodyToUInt32(b));
		std::cout<<"Policy for second state in (2,2): "<<pol.getAction(s2_2)<<std::endl;
		State s3_1(dim,max,1,1,2,1,uCV::convertStrBodyToUInt32(b));
		std::cout<<"Policy for third state in (2,1): "<<pol.getAction(s3_1)<<std::endl;
		State s3_2(dim,max,1,1,3,0,uCV::convertStrBodyToUInt32(b));
		std::cout<<"Policy for third state in (3,0): "<<pol.getAction(s3_2)<<std::endl;
		State s3_3(dim,max,1,1,1,2,uCV::convertStrBodyToUInt32(b));
		std::cout<<"Policy for third state in (1,2): "<<pol.getAction(s3_3)<<std::endl;
		State s4(dim,max,1,1,2,0,uCV::convertStrBodyToUInt32(b));
		std::cout<<"Policy for 4. state in (2,0): "<<pol.getAction(s4)<<std::endl;
		State s4_1(dim,max,1,1,0,2,uCV::convertStrBodyToUInt32(b));
		std::cout<<"Policy for 4. state in (0,2): "<<pol.getAction(s4_1)<<std::endl;
		State s5(dim,max,1,1,1,0,uCV::convertStrBodyToUInt32(b));
		std::cout<<"Policy for 5. state in (1,0): "<<pol.getAction(s5)<<std::endl;
		State s5_1(dim,max,1,1,0,1,uCV::convertStrBodyToUInt32(b));
		std::cout<<"Policy for 5. state in (0,1): "<<pol.getAction(s5_1)<<std::endl;


		// Exporting policy to a .txt file
		pol.writeToFile();
		std::cout << "Totatl runtime: "<< MPI_Wtime() - t_start<<std::endl;
	}
    return 0;
}
