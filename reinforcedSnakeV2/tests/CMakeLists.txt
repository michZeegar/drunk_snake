cmake_minimum_required (VERSION 3.1)
project(tests)

if( ${CMAKE_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR} )
  #Message( "" )
  Message( FATAL_ERROR "Building in soure directory!")
endif()

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "-O0 -Wall")


#testing SRC
set(SRC_FILES_UTIL testutil.cpp ../utility.cpp)
set(SRC_FILES_RAND testrandom.cpp ../randomGen.cpp)
set(SRC_FILES_SNAKE testSnakeBodies.cpp ../utility.cpp ../randomGen.cpp ../snakeBodies.cpp)
set(SRC_FILES_STATE teststate.cpp ../utility.cpp ../state.cpp ../randomGen.cpp)
set(SRC_FILES_STRUCTSTATE testStruct.cpp)
set(SRC_FILES_CREATE test_create_bodies.cpp ../utility.cpp ../randomGen.cpp ../snakeBodies.cpp)
set(SRC_FILES_STRUCT testStructWithBodies.cpp ../utility.cpp ../randomGen.cpp ../snakeBodies.cpp ../structureOfStates.cpp ../state.cpp)


# Create executable
add_executable(tUTIL ${SRC_FILES_UTIL})
add_executable(tRAND ${SRC_FILES_RAND})
add_executable(tSNAKE ${SRC_FILES_SNAKE})
add_executable(tSTATE ${SRC_FILES_STATE})
add_executable(tSTRUCT ${SRC_FILES_STRUCT})
add_executable(tSTRUCTSTATE ${SRC_FILES_STRUCTSTATE})
add_executable(tCREATE ${SRC_FILES_CREATE})
