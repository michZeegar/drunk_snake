#pragma once

#include <cstdint>
#include <vector>
#include <array>
#include <utility>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <mpi.h>

#ifndef SNAKE_MPI_H
#define SNAKE_MPI_H


class Snake_mpi
{
private:

    //std::vector<float> &state_space;

public:
	int world_size = 0;  //!< total number of processes in the Communicator network
	int world_rank = 0; //!< rank number of the process in the Communicator network
	// Get the name of the processor
	char processor_name[MPI_MAX_PROCESSOR_NAME] = " ";
	int name_len = 0;

	int num_elements_per_proc = 0; //!< the number of elements to process per unit
    /**
     * @brief Set the number of states for the MPI class.
     *
     * @param[in] num_states Number of states in the state space.
     */
    void setNrStates(std::size_t num_states);

    /**
     * Set the refernce pointer to the state space in the MPI class.
     *
     * @param[in] refState Reference to the state space vector.
     */
    //void setRefStateSpace(std::vector<float> &refState);

    /**
     * @brief Returns the position to the start of the working section
     * @return Index of the start position of the state space
     */
    std::size_t getStartSection();
    /**
     * @brief Returning the position to the end of the working section
     * @return Index of the end position of the state space
     */
    std::size_t getEndSection();

    /**
     * @brief displayUpdateResult
     *
     * Displaying the update results of the MPI process.
     */
    void displayUpdateResult(std::vector<float> &state_space);

	/**
	 * @brief Function to start the update communication between the involved network
	 */
	void updateValueSpace(std::vector<float> &state_space, MPI_Datatype datatype, MPI_Comm communicator);

	/**
	* @brief Function to gather the state value section into the root processor. Only needed in the end, when the update function is already done.
	*/
	void gatherValueSpace(std::vector<float> &state_space,MPI_Datatype datatype, MPI_Comm communicator);

	/**
	 * @brief Finish the Communication over MPI
	 */
	void endMpiCommunication(std::vector<float> &state_space);

	/**
	*	@brief Function to save some data into a .txt file.
	*/
	void writeToFile();

    /**
     * @brief Constructor of the MPI communication class
     */
    Snake_mpi();
};

#endif // SNAKE_MPI_H
