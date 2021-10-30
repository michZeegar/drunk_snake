// Script to test the mpi communicator class
#include <iostream>
#include <fstream>
#include <vector>
#include "snake_mpi.h"

// helper function to save some output
void writeToFile(std::vector<float> &refV, size_t count){
    std::ofstream myfile;
    const char *filepath="/var/tmp/ga45yeh/test.txt";
    //std::string filepath = "/var/tmp/ga45yeh/test.txt";
    myfile.open(filepath);

	// Checking if the function was able to open a file in the filepath
    if(myfile.is_open()){
        std::cout<<"The file is open !!!"<<std::endl;
    }
    else{
        std::cout<<"Error: couldn't open file!!"<<std::endl;
    }

    for(std::size_t i = 0; i<count;i++){
        myfile<<refV[i]<<std::endl;
    }

    myfile.close();
};

int main(int argc, char** argv)
{
  // Starting time measurement of the overall algorithm
  int t0_0 = MPI_Wtime();

  // Initialize the MPI environment
  Snake_mpi mpi;

  // Generating dummy data to send around
  int dummy_size= 1294380000 ;
  dummy_size = 80;
  std::vector<float> dummy_data(dummy_size,99);

  // Giving information about the recieving data
	mpi.setNrStates(dummy_size);
	//mpi.setRefStateSpace(dummy_data);

	// Getting responible working section for each worker
	std::size_t start_sec = mpi.getStartSection();
	std::size_t end_sec = mpi.getEndSection();
	// Displaying each working section
	std::cout << "Working section for processor "<< mpi.processor_name << "with rank "<< mpi.world_rank<< " von "<< start_sec<< " bis "<< end_sec << '\n';


	// some dummy work to see if the gathering is working
	// Multiplikation of the dummy_data with the processor rank
	int counter = 0;
	while(counter < mpi.num_elements_per_proc){
		dummy_data[mpi.world_rank * mpi.num_elements_per_proc + counter] = mpi.world_rank;
		//std::cout << dummy_data[world_rank * num_elements_per_proc + counter] << std::endl;
		counter++;
	}

    // Print out the size of the dummy data
   if(mpi.world_rank == 0){
        std::cout<<"Hello I am the MPI class tester !!!!"<<std::endl;
        std::cout << "Process is 0 broadcasting data: " << std::endl;
        std::cout<< mpi.num_elements_per_proc * sizeof(float) / 1000000  << " MB transmitted form the root broadcaster!!" << std::endl;
		std::cout << "Process is 0 receiving data: " << std::endl;
		std::cout<< mpi.num_elements_per_proc * sizeof(float) * (mpi.world_size - 1) / 1000000  << " MB are transmitted to  the root broadcaster!!" << std::endl;
    }

    // Starting time measurement of the communication
    int t1 = MPI_Wtime();

	// update the dummy data in each processor
	mpi.updateValueSpace(dummy_data, MPI_FLOAT, MPI_COMM_WORLD);

    // END time measurement for the communication
    int t1_1 = MPI_Wtime();


    // Printing the time needed for each section
    std::cout << "Process " << mpi.world_rank << "  of  " << mpi.processor_name <<" needed time to finish:  "<< t1_1-t1 << std::endl;

	//Displaying the resulting vector in the root process
	if (mpi.world_rank == 0){
	    std::cout << "Process " << mpi.world_rank << "  of  " << mpi.processor_name <<" state vector data:  "<< dummy_data[mpi.world_rank * mpi.num_elements_per_proc] << std::endl;
	    int count_test = 0;
	    while(count_test < 8){
	       std::cout << dummy_data[count_test*11] <<std::endl;
	       count_test += 1;
	    }
	}

	// Finish MPI communication and clear memory space in the other processors
	mpi.endMpiCommunication(dummy_data);

  // End time measurment total
  int t0_2 = MPI_Wtime();
  if(mpi.world_rank == 0){
  std::cout << "Totatl runtime: "<< t0_2-t0_0<<std::endl;
  }

}
