#include "main.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	for(unsigned int i = 0; i < (unsigned int)argc; i++)
		printf("Argument %ld : %s \n", i + 1, argv[i]);

	(myScene = unique_ptr<Scene>(new Scene("Anthony Sébert 1705851", 1000, 600)))->mainLoop();

	SDL_Quit();
	getchar();

	return 0;
}