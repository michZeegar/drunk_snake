#include "game.h"
int main(){
	//Get a game with 7,3,5
	uint8_t dim = 7;
	uint8_t min = 3;
	uint8_t max = 5;

	Game g(dim,min,max,"test.txt");
	// Reading in a policy from a text file
	g.readInPolicy();

	// Simulate 20 moves
	for(auto i = 0; i < 40; i++){
		std::cout << "Move Number "<< i << '\n';
		g.print_game();
	}

    return 0;
}
