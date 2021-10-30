#include <iostream>
#include <bitset>
#include "../snakeBodies.h"
#include "../utility.h"


int main(){
	// Init variables
	int min_snake = 3;
	int max_snake = 10;

	SnakeBodies snake(min_snake, max_snake);
	std::size_t nr_snake_bodies = snake.nrOfBodies();
	for(auto x:snake.mMinLengthBodies){
		std::string tmp;
		uCV::convertUInt32toStr(x,tmp);
		std::cout<<tmp<<",";
	}
	std::cout<<std::endl;
	std::cout<<"Anzahl an Snake Congiuration possiblities: "<< nr_snake_bodies<< std::endl;

}
