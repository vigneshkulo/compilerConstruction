#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int N = 0;
	int SQRT = 0;

	scanf("%d", &N);
	SQRT = 0;

	while (SQRT * SQRT <= N) {
           	SQRT = SQRT + 1;
	}
	SQRT = SQRT - 1;

	printf("%d\n", SQRT);

return 0;
}