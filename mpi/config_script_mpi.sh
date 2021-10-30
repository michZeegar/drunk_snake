#!/bin/bash
# Script for the configuration of the MPI communication 

# Init some colors for the echo command
RED='\033[0;31m'
PURPLE='\033[1;35m'
CYAN='\033[0;36m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

echo -e "${CYAN}This script will set up the configuration for the MPI communication. ${NC}"
echo -e "${CYAN}Enter your login credentials for the HPC systems!!! \n ${NC}"
echo -n "USERNAME: "; read user
# echo -n "PASSWORD: "; stty -echo; read pw; stty echo; echo

# Copying the current hostfile to the home directory
cp -r config/host_file ~/

# Getting original config file 
cp -r config/ssh_config_for_students .

# Replace the dummy username with actually username of the current session
dummy_user='ga12abc'
sed -i -e "s/$dummy_user/$user/g" 'ssh_config_for_students' 

# Copying the configuration file to the .shh directory
cp -i ssh_config_for_students ~/.ssh/

# Remove temportal ssh_config file 
rm ssh_config_for_students

# Testing current MPI configurations
echo -e "${CYAN}Testing current MPI configurations!!! ${NC}"
echo -e "${CYAN}Following systems(each system gets two jobs) are answering:  \n ${NC}"
mpirun -np 8 -hostfile ~/host_file hostname


# deleting password
# pw=

echo -e "${GREEN} \n Done!! ${NC}"
