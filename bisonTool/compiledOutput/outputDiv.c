#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int X = 0;
	int Y = 0;
	int Z = 0;

	Z = 55;
	Y = 0;

	if(0 == 0) {
           	printf("runtime error: division by zero: 'Z div 0 '\n");
	}
	else {
           	X = Z / 0;
	}

	printf("%d\n", X);

	if(0 == Y) {
           	printf("runtime error: division by zero: 'Z div Y '\n");
	}
	else {
           	X = Z / Y;
	}

	if(0 == Z) {
           	printf("runtime error: division by zero: 'Y div Z '\n");
	}
	else {

           	if(0 == (Y / Z)) {
                       	printf("runtime error: division by zero: 'X div ( Y div Z ) '\n");
           	}
           	else {
                       	X = Z + (X / (Y / Z));
           	}
	}

return 0;
}