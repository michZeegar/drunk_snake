#!/bin/bash
# Script to build and execute the newest version of the HPC Drunk Snake 

# Init some colors for the echo command
RED='\033[0;31m'
PURPLE='\033[1;35m'
CYAN='\033[0;36m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

echo -e "${CYAN}This script will build the newest version of HPC drunk snake and excute it. ${NC}"

# Saving current directory
dir=$(pwd)

echo -e "${CYAN}Checking if local file directory for saving output policy exists !!! ${NC}"
cd /var/tmp
if [ -d ga45yeh ]; then 
	cd ${dir}
else	
	echo -e "${PURPLE}Created new file directory for tempory storing the calculated policy (for LRZ: named with TUM-ID) !!! ${NC}"
	echo -n "USERNAME: "; read user	
	mkdir ${user}
	cd  ${dir}
fi




cd reinforcedSnakeV2

# Checking if build dir already exists, if not creating it 
if [ -d build ]; then 
	cd build
else
	mkdir build
	cd build 
fi

# Building new executable from mpi_dummy_test
echo -e "${CYAN}Build the newest version of HPC DrunkSnake from the source files!!! ${NC}"
cmake ..
make	

echo -e "${PURPLE}Select number of active workers for solving the dynamic programming problem !!! ${NC}"
echo -n "Number of Worker: "; read nr_worker

echo -e "${CYAN}Execution of the newest version of HPC DrunkSnake!!! ${NC}"

echo -e "${GREEN}Checking if  processes are ready to be called !!. ${NC}"
mpirun -np ${nr_worker} -hostfile ~/projects/host_file hostname
echo -e "${GREEN}Start HPC Drunken Snake with 8 processes !!! ${NC}"
mpirun -np ${nr_worker} -hostfile ~/projects/host_file HPC_drunk_snake

