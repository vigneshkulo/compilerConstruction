#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int SMALLER = 0;
	int BIGGER = 0;
	int TEMP = 0;

	scanf("%d", &BIGGER);
	scanf("%d", &SMALLER);

	if (SMALLER > BIGGER) {
           	TEMP = SMALLER;
           	SMALLER = BIGGER;
           	BIGGER = TEMP;
	}

	while (SMALLER > 0) {
           	BIGGER = BIGGER - SMALLER;

           	if (SMALLER > BIGGER) {
                       	TEMP = SMALLER;
                       	SMALLER = BIGGER;
                       	BIGGER = TEMP;
           	}
	}

	printf("%d\n", BIGGER);

return 0;
}