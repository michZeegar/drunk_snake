cmake_minimum_required (VERSION 3.1)
project(HPC_drunk_snake)

if( ${CMAKE_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR} )
  #Message( "" )
  Message( FATAL_ERROR "Building in soure directory!")
endif()

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "-O2 -Wall")

# We need the MPI Package, it is installed in a way that you can find it via CMake
find_package(MPI REQUIRED)

# Here the include for MPI are added
include_directories(${MPI_INCLUDE_PATH})

set(SRC_FILES_1 generate.cpp utility.cpp structureOfStates.cpp snakeBodies.cpp state.cpp randomGen.cpp policy.cpp learning.cpp)
set(SRC_FILES_2 simulate.cpp utility.cpp structureOfStates.cpp state.cpp snakeBodies.cpp randomGen.cpp game.cpp)

# mpi_dynamic main: learning with mpi communication combined
set(SRC_FILES_3 mpi_dynamic.cpp utility.cpp structureOfStates.cpp snakeBodies.cpp state.cpp randomGen.cpp policy.cpp learning.cpp ../mpi/snake_mpi.cpp)

# Create executable
add_executable(generate_policy ${SRC_FILES_1})
add_executable(simulate_policy ${SRC_FILES_2})
add_executable(${PROJECT_NAME} ${SRC_FILES_3})

# Link against MPI Libraries
target_link_libraries(${PROJECT_NAME} ${MPI_LIBRARIES} -lpthread)
