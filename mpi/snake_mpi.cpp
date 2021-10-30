#include "snake_mpi.h"


Snake_mpi::Snake_mpi()
{
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Find out rank and size
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the name of the processor
    MPI_Get_processor_name(processor_name, &name_len);

    // Define how much data pre processor --> defines for how much data each processor is responsible
    // num_elements_per_proc = num_states/world_size;

}

void Snake_mpi::setNrStates(std::size_t num_states){
    // Define how much data pre processor --> defines for how much data each processor is responsible
    num_elements_per_proc = num_states/world_size;
}

// void Snake_mpi::setRefStateSpace(std::vector<float> &refState){
//     state_space = refState;
// }

std::size_t Snake_mpi::getStartSection(){
    return num_elements_per_proc * world_rank;
}

std::size_t Snake_mpi::getEndSection(){
    return (num_elements_per_proc * (world_rank + 1)) -1;
}

void Snake_mpi::updateValueSpace(std::vector<float> &state_space, MPI_Datatype datatype, MPI_Comm communicator){
    MPI_Allgather(/*void*        send_data =     */ &state_space[world_rank * num_elements_per_proc], // maybe shifting it + 1
               /*int          send_count =    */ num_elements_per_proc,
               /*MPI_Datatype send_datatype = */ datatype,
               /*void*        recv_data =     */ &state_space[0],
               /*int          recv_count =    */ num_elements_per_proc,
               /*MPI_Datatype recv_datatype = */ datatype,
               /*MPI_Comm     communicator =  */ communicator);
    // Waiting for every process to finish his communication --> just a saftey step, probably not needed
    MPI_Barrier(communicator);
}

void Snake_mpi::gatherValueSpace(std::vector<float> &state_space,MPI_Datatype datatype, MPI_Comm communicator){
	// Waiting for every process to finish his calculation --> just a saftey step, probably not needed
    MPI_Barrier(communicator);
	//Gathering all the informations
   MPI_Gather(/*void*        send_data =     */ &state_space[world_rank * num_elements_per_proc], // maybe shifting it + 1
              /*int          send_count =    */ num_elements_per_proc,
              /*MPI_Datatype send_datatype = */ datatype,
              /*void*        recv_data =     */ &state_space[0],
              /*int          recv_count =    */ num_elements_per_proc,
              /*MPI_Datatype recv_datatype = */ datatype,
              /*int          root =          */ 0,
              /*MPI_Comm     communicator =  */ communicator);

}

void Snake_mpi::endMpiCommunication(std::vector<float> &state_space){
	// Gathering all information to root process
	//Snake_mpi::gatherValueSpace(std::vector<float> &state_space,MPI_FLOAT, MPI_COMM_WORLD);
	// Clean up  --> state space only needed in the root process after the final gathering.
	if(world_rank != 0){
	state_space.clear();
	}
    // Wait for all to ensure proper deleting
    MPI_Barrier(MPI_COMM_WORLD);
    // Finalize the MPI environment. No more MPI calls can be made after this
    MPI_Finalize();
}

void Snake_mpi::displayUpdateResult(std::vector<float> &state_space){
	// not used so foar --> doesnt work just for completion
    // Displaying the received data to check the sending process
    if(world_rank == 0){
        std::cout << "Process " << world_rank << " running on  "<< processor_name<< " received data:  " << std::endl;

        int count = 0; // ToDo: Change count and while loop into a more fancy solution !!
        while(count < num_elements_per_proc){
           // displaying the last element in each section
           std::cout << state_space[count + num_elements_per_proc -1] << ' '<< " from root process!" << "Inspected element is "<<
                count<<std::endl;
           // adding elements pre process to count --> jumping to data from the next processor
           count = count + num_elements_per_proc;
        }
    }

}

// void Snake_mpi::writeToFile(){
//     std::ofstream myfile();
//     std::string filepath = "/tmp/test.txt";
//     myfile.open(filepath);
//
//     for(std::size_t i = 0; i<100000000;i++){
//         myfile<<'a'<<std::endl;
//     }
//
//     myfile.close();
// }
