#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int SMALLER = 0;
	int BIGGER = 0;
	int TEMP = 0;

	scanf("%d", &BIGGER);
	scanf("%d", &SMALLER);


	if(0 == TEMP) {
           	printf("runtime error: division by zero: 'BIGGER div TEMP '\n");
	}
	else {

           	if(0 == (BIGGER / TEMP)) {
                       	printf("runtime error: division by zero: 'SMALLER div ( BIGGER div TEMP ) '\n");
           	}
           	else {
                       	while ((BIGGER > (SMALLER / (BIGGER / TEMP)))) {
                                   	BIGGER = BIGGER - SMALLER;
                       	}
           	}
	}


	if(0 == TEMP) {
           	printf("runtime error: division by zero: 'BIGGER div TEMP '\n");
	}
	else {

           	if(0 == (BIGGER / TEMP)) {
                       	printf("runtime error: division by zero: 'SMALLER div ( BIGGER div TEMP ) '\n");
           	}
           	else {
                       	printf("%d\n", (BIGGER + (SMALLER / (BIGGER / TEMP))));
           	}
	}

return 0;
}
