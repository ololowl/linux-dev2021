#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sysexits.h>
#include <stdlib.h>

void PerrorHelp() {
	fprintf(stderr, 
	 	    "Wrong format of program argumets.\n"
	 	    "Usage: ./main input-file-path output-file-path\n"
	        "\tinput-file-path: relative path to input file to copy\n"
	        "\toutput-file-path: relative path to output file to create\n");
}

void CloseFile(FILE* f, char* filename) {
	if (fclose(f) == EOF) {
		fprintf(stderr, "can't close file %s\n", filename);
		exit(EX_OSFILE);
	}
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		PerrorHelp();
		exit(EX_USAGE);
	}

	FILE *fin = fopen(argv[1], "rb");
	if (fin == NULL) {
		fprintf(stderr, "fin is null, errno=%d\n", errno);
		return errno;
	}

	FILE* fout = fopen(argv[2], "wb");
	if (fout == NULL) {
		fprintf(stderr, "fout is null, errno=%d\n", errno);
		CloseFile(fin, argv[1]);
		return errno;
	}

	char ch = fgetc(fin);
	while (ch != EOF) {
		int result = fputc(ch, fout);
		
		if (result == EOF) {
			CloseFile(fin, argv[1]);
			CloseFile(fout, argv[2]);
			
			int result = remove(argv[2]);
			if (result) {
				fprintf(stderr, "can't remove output file");
				exit(EX_OSFILE);
			}

			fprintf(stderr, "can't write to outfile, errno=%d\n", errno);
			return errno;
		}

		ch = fgetc(fin);
	}

	CloseFile(fout, argv[2]);
	CloseFile(fin, argv[1]);

	int result = remove(argv[1]);
	if (result) {
		fprintf(stderr, "can't remove input file");
		exit(EX_OSFILE);
	}
	
	return 0;
}