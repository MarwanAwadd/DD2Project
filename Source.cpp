#include "MazeRouter.h"

int main() {
	
	MazeRouter mazeRounter;	
	mazeRounter.readFile();
	mazeRounter.getAllMinimumDistances();

	system("pause");
	return 0;
}