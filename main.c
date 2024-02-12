#include <stdio.h>

enum {MAX = 100};
int atoi(char *string_to_convert); // String to integer
void graph_neg(int m, int b);
void graph_pos(int m, int b);

// This only works for the first quadrant
int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Put in 2 arguments\n");
		return -1;
	}

	int m = atoi(argv[1]); // slope
	int b = atoi(argv[2]); // offset

	void (*graph)(int m, int b);

	if (m < 0)
		graph = graph_neg;
	else
		graph = graph_pos;

	(*graph)(m, b);

	return 0;
}

// change text to number
int atoi(char *s) {
	while (*s == ' ' || *s == '+')
		s++;

	int neg = 1;
	if (*s == '-') {
		neg = -1;
		s++;
	}

	int x = 0;
	for (;*s >= '0' && *s <= '9'; s++)
		x = x * 10 + *s - '0';
	return neg * x;
}

int abs(int x) {
	if (x < 0)
		return -x;
	return x;
}

// draw a graph with -ve slope
void graph_neg(int m, int b) {
	m = abs(m);
	int y = b;
	int x = 0; // how many spaces to the right we are of y axis

	printf("^\n|\n"); // y axis arrow head

	// start at y intercept, go till y = 0
	for (; y > 0; y -= m) {


		/*
		How many spaces we are from y-axis. (our x coordinate)

		note that x is number of spaces from left of terminal, not from y axis.

		Since drawing the y-axis takes a character's space, we go x-1 units
		from the left of the terminal.
		*/
		for (int j = 0; j < x - 1; j++)
			printf(" ");
		x++;
		printf("."); // point

		// y decreases by slope units each time x increases by 1.
		for (int j = 0; j < m; j++)
			printf("\n|");
	}

	// Print the x axis
	x *= 2; // Make the x axis twice as long as the farthest x point
	while (x-- > 0)
		printf("-");
	printf(">\n");
}

void graph_pos(int m, int b) {
}
