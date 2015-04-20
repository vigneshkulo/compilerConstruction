#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int X = 0;
	int Y = 0;
	int Z = 0;

	Z = 55;
	Y = 0;
	X = Z / 0;
	X = Z / Y;

	printf("%d\n", X);

return 0;
}
