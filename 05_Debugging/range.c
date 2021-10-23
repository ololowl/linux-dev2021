#include <stdio.h>
#include <stdlib.h>

void PrintHelp() {
	printf("usage:\n");
	printf("* ./prog - for help\n");
	printf("* ./prog N - for range [0, N)\n");
	printf("* ./prog M N - for range [M, N)\n");
	printf("* ./prog M N S - for range [M, N) with step S\n");
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		PrintHelp();
		return 0;
	}

	int start = 0;
	int stop = atoi(argv[1]);
	int step = 1;

	if (argc >= 3) {
		start = stop;
		stop = atoi(argv[2]);
	}
	if (argc >= 4) {
		step = atoi(argv[3]);
	}

	for (int i = start; i < stop; i += step) {
		printf("%d\n", i);
	}

	return 0;
}