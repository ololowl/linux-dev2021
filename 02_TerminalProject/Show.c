#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

const size_t DX = 3;
const size_t MAX_LINE_LEN = 200;
const char SPACE_KEY = 32;

void PrintUsage() {
    printf("Usage: ./show <filename>\nWhere filename is the path to file to show.\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        PrintUsage();
        return 0;
    }

	initscr();

    size_t windowW = 100;//COLS - 2 * DX;
    size_t windowH = 30;//LINES - 2 * DX;

    char** lines;
    int* linesSize;
    size_t nLines = 10;

    lines = (char**)malloc(nLines * sizeof(char*));
	linesSize = (int*)malloc(nLines * sizeof(int));
	size_t readLines = 0;

	{ // read file into lines
	    FILE *file = fopen(argv[1], "r");
	
		char* buf = (char*)malloc(MAX_LINE_LEN * sizeof(char));
	
	    size_t maxLen = MAX_LINE_LEN;
		size_t lineLen = getline(&buf, &maxLen, file);
		while (lineLen != -1) {
	    	if (readLines >= nLines) {
				nLines *= 2;
				lines = (char**)realloc(lines, nLines * sizeof(char*));
				linesSize = (int*)realloc(linesSize, nLines * sizeof(int)); ////////////////////////////////////////////////////////////////////
			}
	
			lines[readLines] = (char*)malloc(lineLen * sizeof(char));
			memcpy(lines[readLines], buf, lineLen * sizeof(char));
			linesSize[readLines] = lineLen;
			++readLines;
	
			lineLen = getline(&buf, &maxLen, file);
		}

		fclose(file);
	}

	WINDOW *win;
	int c = 0;

	curs_set(0);
	noecho();
	cbreak();
	printw(argv[1]);
	refresh();

	win = newwin(windowH, windowW, DX, DX);
	keypad(win, TRUE);
	scrollok (win, TRUE);
	box(win, 0, 0); 
	wmove(win, 1, 0); 

	size_t startLine = 0;

	do {
		if (c == SPACE_KEY) {
			if (startLine < readLines - windowH + 1 + DX) {
				++startLine;
			}
		}

		//werase(win);
		for (size_t i = 0; i < windowH - DX - 1 && startLine + i < readLines; ++i) {
			mvwprintw(win, i + 1 + DX, 1, "%4d  %s\n", startLine + i + 1, lines[startLine + i]);
		}
		//wprintw(win, "  Key: %d, Name: %s\n", c, keyname(c));
		box(win, 0, 0); 
		wrefresh(win);
	} while((c = wgetch(win)) != 27);
	
	endwin();

	for (size_t i = 0; i < nLines; ++i) {
		free(lines[i]);
	}
	free(linesSize);
	free(lines);
	return 0;
}