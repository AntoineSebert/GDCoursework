#include "main.h"

using namespace std;

int main(int argc, char* argv[]) {
	// print command line arguments (for testing purposes)
	for(unsigned int i = 0; i < (unsigned int)argc; i++)
		printf("Argument %ld : %s \n", i + 1, argv[i]);
	// print content of the current directory (for testing purposes)
	string path = ".";
	for(const auto& p : std::experimental::filesystem::directory_iterator(path))
		cout << p << endl;
	// create and run scene
	(myScene = unique_ptr<Scene>(new Scene("Anthony Sébert 1705851", 600, 1000)))->mainLoop();

	SDL_Quit();

	return 0;
}