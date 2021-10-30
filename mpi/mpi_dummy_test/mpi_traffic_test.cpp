// Script to simulate the traffic load and get the communication time
#include <iostream>
#include <fstream>
#include <vector>
#include <mpi.h>

void writeToFile(){
    std::ofstream myfile;
    const char *filepath="/var/tmp/ga45yeh/test.txt";
    //std::string filepath = "/var/tmp/ga45yeh/test.txt";
    myfile.open(filepath);

    if(myfile.is_open()){
        std::cout<<"The file is open !!!"<<std::endl;
    }
    else{
        std::cout<<"Error: couldn't open file!!"<<std::endl;
    }

    for(std::size_t i = 0; i<500000000;i++){
        myfile<<'a'<<std::endl;
    }

    myfile.close();
};

int main(int argc, char** argv)
{
  //writeToFile();
  // starting time measurement of the overall algorithm
  int t0_0 = MPI_Wtime();
  std::vector<float> test(3,99);

  // Initialize the MPI environment
  MPI_Init(NULL, NULL);

  // Find out rank and size
  int world_rank, world_size;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Get the name of the processor
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

  // Generating dummy data to send around
  int dummy_size= 1294380000 ;
  dummy_size = 80;
  std::vector<float> dummy_data(dummy_size,99);

  // Define how much data pre processor --> defines for how much data each processor is responsible
  int num_elements_per_proc = dummy_size/world_size;

  // Creating Dummy buffer --> for receiving the data and be able to handle the incomming size
//  std::vector<float> buffer_dummy(num_elements_per_proc, 0);

    // Print out the size of the dummy data
   if(world_rank == 0){
        std::cout<<"Hello I am the MPI traffic tester !!!!"<<std::endl;
        std::cout << "Process is 0 broadcasting data: " << std::endl;
        std::cout<< num_elements_per_proc * sizeof(float) / 1000000  << " MB transmitted form the root broadcaster!!" << std::endl;
    }

    // Starting time measurement of the communication
    int t1 = MPI_Wtime();

    // Scatter the data with MPI to all systems
//    MPI_Scatter(/*void*        send_data =     */ &dummy_data[0],
//                /*int          send_count =    */ num_elements_per_proc,
//                /*MPI_Datatype send_datatype = */ MPI_FLOAT,
//                /*void*        recv_data =     */ &buffer_dummy[0],
//                /*int          recv_count =    */ num_elements_per_proc,
//                /*MPI_Datatype recv_datatype = */ MPI_FLOAT,
//                /*int          root =          */ 0,
//                /*MPI_Comm     communicator =  */ MPI_COMM_WORLD);
    // Init phase: Sending the complete state-value space to each processer
    //MPI_Bcast(&dummy_data[0], dummy_data.size(), MPI_FLOAT, 0, MPI_COMM_WORLD);


    // Start time measurement of the actuall work process
    int t1_1 = MPI_Wtime();

    // Multiplikation of the dummy_data with the processor rank
        int counter = 0;
        while(counter < num_elements_per_proc){
            dummy_data[world_rank * num_elements_per_proc + counter] = world_rank;
            //std::cout << dummy_data[world_rank * num_elements_per_proc + counter] << std::endl;
            counter++;
        }

    // End time measurement of the actuall work process
    int t2_1 = MPI_Wtime();

    //Gathering all the informations
//    MPI_Gather(/*void*        send_data =     */ &dummy_data[world_rank * num_elements_per_proc], // maybe shifting it + 1
//               /*int          send_count =    */ num_elements_per_proc,
//               /*MPI_Datatype send_datatype = */ MPI_FLOAT,
//               /*void*        recv_data =     */ &dummy_data[0],
//               /*int          recv_count =    */ num_elements_per_proc,
//               /*MPI_Datatype recv_datatype = */ MPI_FLOAT,
//               /*int          root =          */ 0,
//               /*MPI_Comm     communicator =  */ MPI_COMM_WORLD);

    MPI_Allgather(/*void*        send_data =     */ &dummy_data[world_rank * num_elements_per_proc], // maybe shifting it + 1
               /*int          send_count =    */ num_elements_per_proc,
               /*MPI_Datatype send_datatype = */ MPI_FLOAT,
               /*void*        recv_data =     */ &dummy_data[0],
               /*int          recv_count =    */ num_elements_per_proc,
               /*MPI_Datatype recv_datatype = */ MPI_FLOAT,
               /*MPI_Comm     communicator =  */ MPI_COMM_WORLD);

    // Waiting for every process to finish his communication --> just a saftey step, probably not needed
    MPI_Barrier(MPI_COMM_WORLD);

    // End time measurement communication
    int t2 = MPI_Wtime();

    // Printing the time needed for each section
    std::cout << "Process " << world_rank << "  of  " << processor_name <<" needed time to finish:  "<< t2-t1 <<
                 "with "<< t1 <<" and "<< t2<< std::endl;
    std::cout << "Process " << world_rank << " needed time to calculate:  "<< t2_1-t1_1 <<std::endl;
    std::cout << "Process " << world_rank << " needed time for communication:  "<< (t2-t1)-(t2_1-t1_1) <<std::endl;
    std::cout << "Process " << world_rank << "  of  " << processor_name <<" test vector data:  "<< &test << std::endl;
    int count_test = 0;
    while(count_test < 3){
       std::cout << test[count_test] <<std::endl;
       count_test += 1;
    }

    // Displaying the received data to check the sending process
    if(world_rank == 0){
        std::cout
          << "Process " << world_rank
          << " received data:  " << std::endl;
        int count = 0;
        while(count < dummy_size){
           std::cout << dummy_data[count + num_elements_per_proc -1] << ' '<< " from root process!" << "Inspected element is "<<
                count<<std::endl;
           // adding elements pre process to count --> jumping to data from the next processor
           count = count + num_elements_per_proc;
    }
    }


    // Clean up
    dummy_data.clear();
//    buffer_dummy.clear();

    // Wait for all to ensure proper deleting
    MPI_Barrier(MPI_COMM_WORLD);


  // Finalize the MPI environment. No more MPI calls can be made after this
  MPI_Finalize();

  // End time measurment total
  int t0_2 = MPI_Wtime();
  if(world_rank == 0){
  std::cout << "Totatl runtime: "<< t0_2-t0_0<<std::endl;
  writeToFile();
  }

}
