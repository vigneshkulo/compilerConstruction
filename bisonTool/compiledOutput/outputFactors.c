#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int N = 0;
	int I = 0;

	scanf("%d", &N);
	I = 2;

	while (I <= N) {

           	while (N % I == 0) {

                       	if(0 == I) {
                                   	printf("runtime error: division by zero: 'N div I '\n");
                       	}
                       	else {
                                   	N = N / I;
                       	}

                       	printf("%d\n", I);
           	}
           	I = I + 1;
	}

return 0;
}