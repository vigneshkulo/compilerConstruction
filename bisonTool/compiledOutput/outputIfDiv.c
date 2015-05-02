#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int SMALLER = 0;
	int BIGGER = 0;
	int TEMP = 0;

	scanf("%d", &BIGGER);


	if(0 == TEMP) {
           	printf("runtime error: division by zero: 'BIGGER div TEMP '\n");
	}
	else {
           	if (SMALLER > (BIGGER / TEMP)) {
                       	scanf("%d", &SMALLER);
           	}
	}

	printf("%d\n", BIGGER);

return 0;
}