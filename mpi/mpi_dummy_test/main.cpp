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
  // Initialize the MPI environment
  MPI_Init(NULL, NULL);

  // This time only the rank is required
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // Generating dummy data to send around
  int dummy_size = 50000000 ;
  std::vector<uint64_t> dummy_data(dummy_size,0);

  // Process zero sends
  if (world_rank == 0)
  {
    // Generating some dummy data to transmit
    for (auto& i: dummy_data)
        i = i + 1;
    std::cout << "Process is 0 broadcasting data: " << std::endl;
//    for (auto& i: dummy_data)
//      std::cout << i << ' ';
    std::cout<< dummy_data.size() * sizeof(uint64_t) / 1000000  << " MB transmitted form the root broadcaster!!" << std::endl;

// MPI Bcast ist much fast than the function my_bcast !!!
//    my_bcast(&dummy_data[0], dummy_data.size(), MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);
    MPI_Bcast(&dummy_data[0], dummy_data.size(), MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);
  }

  // The rest listens
  else
  {
      // MPI Bcast ist much fast than the function my_bcast !!!
//    my_bcast(&dummy_data[0], dummy_data.size(), MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);
    MPI_Bcast(&dummy_data[0], dummy_data.size(), MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);

    std::cout
      << "Process " << world_rank
      << " received data:  " << dummy_data[10000]<< std::endl;
//    for (auto& i: dummy_data)
//       std::cout << i << ' ';
    std::cout << " from root process!" << std::endl;

// Multiplikation of the dummy_data with the processor rank
    for (auto& i: dummy_data)
        i = i * world_rank;




  }

  // Finalize the MPI environment. No more MPI calls can be made after this
  MPI_Finalize();
}
