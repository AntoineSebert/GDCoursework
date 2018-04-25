#include "main.hpp"

using namespace std;
namespace fs = std::experimental::filesystem;

int main(int argc, char* argv[]) {
	for(unsigned int i = 0; i < (unsigned int)argc; i++)
		printf("Argument %ld : %s \n", i + 1, argv[i]);
	/*
	std::string path = ".";
	for(auto & p : fs::directory_iterator(path))
		std::cout << p << std::endl;
	*/

	(myScene = unique_ptr<Scene>(new Scene("Anthony Sébert 1705851", 1000, 600)))->mainLoop();

	SDL_Quit();
	getchar();

	return 0;
}