#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

	// Check for three the three parameters
	if (argc != 3) {
		printf("Usage: %s destination source", argv[0]);
		return 1;
	}

	// Check if a file already exisits at the destination
	if (access(argv[1], F_OK) == 0) {
		printf("File %s already exsits\n", argv[1]);
		return 1;
	}

	FILE *dest = fopen(argv[1], "w");
	FILE *src = fopen(argv[2], "r");

	if (src == NULL) {
		printf("Cannot access %s\n", argv[2]);
		fclose(dest);
		return 1;
	}

	char ch;
	while ((ch = fgetc(src)) != EOF) {
		fputc(ch, dest);
	}

	fclose(dest);
	fclose(src);
	return 0;
}
