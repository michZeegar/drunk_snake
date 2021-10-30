#pragma once
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdint>
#include <string>

#include "defEnums.h"

namespace uCHECK{
	/**
	 * @brief Function to check if a body configuration would result into selfCollision
	 */
    bool hasCollision(uint32_t body);
}

namespace uCV{
	/**
	 * @brief Function to convert a string with snake moves to an uint32_t with the corresponding moves.
	 */
    uint32_t convertStrBodyToUInt32(const std::string& in);
	/**
	 * @brief Function to convert an uint32_t with the corresponding moves of a snake to a string containing the same moves.
	 */
    void convertUInt32toStr(uint32_t in, std::string& out);
}

namespace uMOVE{
    MOVE getDrunkMove(MOVE m);
}
