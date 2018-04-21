#include "main.hpp"

int main(int argc, char* argv[]) {
	for (unsigned int i = 0; i < (unsigned int)argc; i++)
		printf("Argument %ld : %s \n", i + 1, argv[i]);

	getchar();
	return 0;
}