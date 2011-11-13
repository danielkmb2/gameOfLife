#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

typedef char cell;
enum {height=23, width=80};
/* 1 is live, 0 is dead */
cell cells[height][width];

void display_cells() {
	int i, j;
	printf("\e[0H");
	for (i = 0; i != height; i++) {
		for (j = 0; j != width; j++) {
			putchar(" #"[(int)cells[i][j]]);
		}
		putchar('\n');
	}
	putchar('\n');
}

/* each cell in dest gets the number of live cells in its three-cell
 * horizontal neighborhood.  We're using dead edges -- cells off the
 * edge count as dead.  It might be a better idea to eliminate the
 * special cases by having a buffer zone around the edge, the way I did
 * for that lattice-gas automaton. */
void scan_line(int n, cell dest[]) {
	int acc, i;
	cell *row = cells[n];

	/* fprintf(stderr, "entering scan_line %d\n", n); */
	acc = row[0] + row[1];
	dest[0] = acc;
	for (i = 1; i < width-1; i++) {
		/* fprintf(stderr, "computing cell %d\n", i); */
		acc += row[i+1];
		dest[i] = acc;
		acc -= row[i-1];
	}
	dest[width-1] = acc;
}

/* first coord is current state, second coord is number of live
 * neighbors including self, result is new state */

cell state_table[2][10] = {
	{0, 0, 0, 1, 0,  0, 0, 0, 0, 0},
	{0, 0, 0, 1, 1,  0, 0, 0, 0, 0}
};

/* more special cases, ick */
void update_cells() {
	static cell buffer[3][width];
	cell *last_line = buffer[0];
	cell *cur_line = buffer[1];
	cell *next_line = buffer[2];
	int i, j;

	/* fprintf(stderr, "entering update_cells\n"); */

	/* simulate scanning row -1 */
	for (i = 0; i != width; i++) {
		cur_line[i] = 0;
	}
	scan_line(0, next_line);
	
	/* fprintf(stderr, "scanned first line\n"); */
	/* compute each line */
	for (i = 0; i < height - 1; i++) {
		/* shift */
		cell *tmp;
		tmp = last_line; last_line = cur_line; 
		cur_line = next_line; next_line = tmp;

		scan_line(i + 1, next_line);
		/* fprintf(stderr, "scanned line %d\n", i+1); */

		/* compute this line */
		for (j = 0; j != width; j++) {
			cells[i][j] = state_table[(int)cells[i][j]]
				[last_line[j]+cur_line[j]+next_line[j]];
		}
	}
	/* fprintf(stderr, "scanned thing\n"); */


	/* compute last line */
	for (j = 0; j != width; j++) {
		cells[height-1][j] = state_table[(int)cells[height-1][j]]
			[cur_line[j] + next_line[j]];
	}
	/* fprintf(stderr, "scanned last line\n"); */
}

int main(int argc, char **argv) {
	/* +2 to permit a newline and a null */
	char inbuf[width+2];
	int i, row, usecs = 100000;
	float fps;

	if (argc != 1) {
		fps = atof(argv[1]);
		if (fps != 0.0) {
			usecs = 1000000/fps;
		}
	}

	printf(
"Enter initial state.  Blanks are spaces; other characters are live\n"
"cells.  Hit control-D to end input.  Width is %d; height is %d.\n",
		width, height);
	row = 0;
	while (fgets(inbuf, width+2, stdin)) {
		if (inbuf[strlen(inbuf)-1] != '\n') {
			fprintf(stderr, "Line too long or not terminated: %s\n", inbuf);
			return -1;
		} 

		for (i = 0; i != width; i++) {
			if (inbuf[i] == '\n') {
				/* rest of line is already 0 because
				 * global */
				break;
			} else if (inbuf[i] == ' ') {
				cells[row][i] = 0;
			} else {
				cells[row][i] = 1;
			}
		}
		row++;
		if (row == height) {
			break;
		}
	}
	printf("ok\n");
	/* rest of array already 0 because global */

	for (;;) {
		display_cells();
		usleep(usecs);
		/* fprintf(stderr, "gonna update_cells\n"); */
		update_cells();
	}
	/* can't happen */
	return -1;
}
