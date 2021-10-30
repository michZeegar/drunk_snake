#include <iostream>
#include <vector>


#include <mpi.h>

void my_bcast(void* data, int count,
              MPI_Datatype datatype, int root,
              MPI_Comm communicator)
{
  int world_rank, world_size;
  MPI_Comm_rank(communicator, &world_rank);
  MPI_Comm_size(communicator, &world_size);

  // If we are the root process, send our data to everyone
  if (world_rank == root)
  {
    for (int i = 0; i < world_size; i++)
    {
      if (i != world_rank)
        MPI_Send(data, count, datatype, i, 0, communicator);
    }
  }

  // If we are a receiver process, receive the data from the root
  else
  {
    MPI_Recv(data, count, datatype, root, 0, communicator, MPI_STATUS_IGNORE);
  }
}


int main(int argc, char** argv)
{
  int t0_1 = MPI_Wtime();
  // Initialize the MPI environment
  MPI_Init(NULL, NULL);

  // Find out rank and size
  int world_rank, world_size;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Generating dummy data to send around
  int dummy_size = 800000000 ;
  std::vector<float> dummy_data(dummy_size,0);
  // Setting the values to 1
    for (auto& i: dummy_data)
        i = i + 1;

  // Define how much data pre processor
  int num_elements_per_proc = dummy_size/world_size;

  // Creating Dummy buffer
  std::vector<float> buffer_dummy(num_elements_per_proc, 0);

    // Print out the size of the dummy data
    std::cout << "Process is 0 broadcasting data: " << std::endl;
    std::cout<< dummy_data.size() * sizeof(uint64_t) / 1000000  << " MB transmitted form the root broadcaster!!" << std::endl;

    int t1 = MPI_Wtime();

    // Scatter the data with MPI to all systems
    MPI_Scatter(/*void*        send_data =     */ &dummy_data[0],
                /*int          send_count =    */ num_elements_per_proc,
                /*MPI_Datatype send_datatype = */ MPI_FLOAT,
                /*void*        recv_data =     */ &buffer_dummy[0],
                /*int          recv_count =    */ num_elements_per_proc,
                /*MPI_Datatype recv_datatype = */ MPI_FLOAT,
                /*int          root =          */ 0,
                /*MPI_Comm     communicator =  */ MPI_COMM_WORLD);
    int t1_1 = MPI_Wtime();
    // Multiplikation of the dummy_data with the processor rank
        for (auto& i: buffer_dummy){
            i = (i * world_rank) / 0.0003;
            i = i * 0.0003 ;}
        // calculating faculty to increase complexity of calculation
        for (auto& i: buffer_dummy){
            int counter = i;
            while(counter > 0){
                i = i * counter;
                counter--;
            }
        }
    int t2_1 = MPI_Wtime();
    //Gathering all the informations
    MPI_Gather(/*void*        send_data =     */ &buffer_dummy[0],
               /*int          send_count =    */ num_elements_per_proc,
               /*MPI_Datatype send_datatype = */ MPI_FLOAT,
               /*void*        recv_data =     */ &dummy_data[0],
               /*int          recv_count =    */ num_elements_per_proc,
               /*MPI_Datatype recv_datatype = */ MPI_FLOAT,
               /*int          root =          */ 0,
               /*MPI_Comm     communicator =  */ MPI_COMM_WORLD);
// Printing array after the MPI procress
//    if(world_rank == 0){
//        std::cout
//          << "Process " << world_rank
//          << " received data:  " << std::endl;
//        for (auto& i: dummy_data)
//           std::cout << i << ' ';
//        std::cout << " from root process!" << std::endl;
//    }


    // Clean up
    if (world_rank == 0)
    {
        dummy_data.clear();
    }
    buffer_dummy.clear();

    // Measuring time differences of the different processes
    int t2 = MPI_Wtime();
    std::cout << "Process " << world_rank << " needed time to finish:  "<< t2-t1 <<
                 "with "<< t1 <<" and "<< t2<< std::endl;
    std::cout << "Process " << world_rank << " needed time to calculate:  "<< t2_1-t1_1 <<std::endl;
    std::cout << "Process " << world_rank << " needed time for communication:  "<< (t2-t1)-(t2_1-t1_1) <<std::endl;

    // Wait for all to ensure proper deleting
    MPI_Barrier(MPI_COMM_WORLD);


  // Finalize the MPI environment. No more MPI calls can be made after this
  MPI_Finalize();

  int t0_2 = MPI_Wtime();
  std::cout << "Totatl runtime: "<< t0_2-t0_1<<std::endl; 
}
