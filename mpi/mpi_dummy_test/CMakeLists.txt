cmake_minimum_required (VERSION 3.0)
project(mpi_dummy_test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Prevent compilation in-source
if( ${CMAKE_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR} )
  Message( "" )
  Message( FATAL_ERROR "Source and build directories are the same!")
endif()

# We need the MPI Package, it is installed in a way that you can find it via CMake
find_package(MPI REQUIRED)

# Here the include for MPI are added
include_directories(${MPI_INCLUDE_PATH})

# Create executable as usual
add_executable(${PROJECT_NAME} "main.cpp")
add_executable(scatter_gather "mpi_scatter_gather.cpp")
add_executable(mpi_traffic_test "mpi_traffic_test.cpp")
add_executable(mpi_class_test "mpi_class_tester.cpp" "snake_mpi.cpp")

# CImg uses threads -> pthread as in today's lecture
# Link against MPI Libraries
target_link_libraries(${PROJECT_NAME} ${MPI_LIBRARIES} -lpthread)
target_link_libraries(scatter_gather ${MPI_LIBRARIES} -lpthread)
target_link_libraries(mpi_traffic_test ${MPI_LIBRARIES} -lpthread)
target_link_libraries(mpi_class_test ${MPI_LIBRARIES} -lpthread)
