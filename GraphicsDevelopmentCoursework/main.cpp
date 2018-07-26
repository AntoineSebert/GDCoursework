#include "main.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	for(unsigned int i = 0; i < (unsigned int)argc; i++)
		printf("Argument %ld : %s \n", i + 1, argv[i]);
	string path = ".";
	for(const auto& p : std::experimental::filesystem::directory_iterator(path))
		cout << p << endl;

	(myScene = unique_ptr<Scene>(new Scene("Anthony Sébert 1705851", 600, 1000)))->mainLoop();

	SDL_Quit();

	return 0;
}