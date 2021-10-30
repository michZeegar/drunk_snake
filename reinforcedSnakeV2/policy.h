#pragma once

#include <vector>
#include <array>
#include <algorithm>
#include <fstream>

#include "defEnums.h"
#include "snakeBodies.h"
#include "structureOfStates.h"
#include "learning.h"

class Policy{
    private:
        const SnakeBodies& mSnake;
        const StructureOfStates& mStructure;
        const Learning& mLearn;
        std::string mfilename;

        std::vector<char> mPol;

    

    public:
        MOVE getPolicy(State in);
        void calculatePolicy();
        char getAction(State in) const; 
        void writeToFile() const;


        Policy(const SnakeBodies& snake, const StructureOfStates& structure, const Learning& learn, const std::string& filename);
};