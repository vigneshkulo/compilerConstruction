#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int N1 = 0;
	int N2 = 0;
	int NEXT = 0;
	int MAX = 0;

	scanf("%d", &MAX);
	N1 = 0;
	N2 = 1;

	printf("%d\n", N1);

	while (N2 < MAX) {

           	printf("%d\n", N2);
           	NEXT = N1 + N2;
           	N1 = N2;
           	N2 = NEXT;
	}

return 0;
}