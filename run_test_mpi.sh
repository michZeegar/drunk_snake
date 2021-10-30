#!/bin/bash
# Script to build and execute the newest version of the MPI test algorithm 

# Init some colors for the echo command
RED='\033[0;31m'
PURPLE='\033[1;35m'
CYAN='\033[0;36m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

echo -e "${CYAN}This script will build the newest version of mpi_dummy_test. ${NC}"

cd mpi/mpi_dummy_test

# Checking if build dir already exists, if not creating it 
if [ -d build ]; then 
	cd build
else
	mkdir build
	cd build 
fi

# Building new executable from mpi_dummy_test
cmake ..
make	
 
echo -e "${CYAN}Execution of the newest version of mpi_dummy_test!!! ${NC}"

echo -e "${GREEN}Checking if 16 processes are ready to be called !!. ${NC}"
mpirun -np 8 -hostfile ~/host_file hostname
#mpirun -np 8 -hostfile ~/host_file mpi_dummy_test
# mpirun -np 8 -hostfile ~/host_file scatter_gather
#mpirun -np 4 -hostfile ~/host_file mpi_traffic_test
echo -e "${GREEN}Testing speed with 8 processes !!! ${NC}"
#mpirun -np 8 -hostfile ~/host_file mpi_traffic_test
mpirun -np 8 -hostfile ~/host_file mpi_class_test
echo -e "${GREEN}Testing speed with 12 processes !!! ${NC}"
#mpirun -np 12 -hostfile ~/host_file mpi_traffic_test
echo -e "${GREEN}Testing speed with 16 processes !!! ${NC}"
#mpirun -np 16 -hostfile ~/host_file mpi_traffic_test

