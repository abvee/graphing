#include <stdio.h>

typedef enum {false, true} bool;

int atoi(char *string_to_convert); // String to integer
void graph_neg(int m, int b);
void graph_pos(int m, int b);
void graph_0(int m, int b);

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
	else if (m == 0)
		graph = graph_0;
	else
		graph = graph_pos;

	graph(m, b);

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

// draw a graph with -ve slope
void graph_neg(int m, int b) {
	int y = b; // the y coordinate of the point
	int yr; // the actual y coordinate
	int x = 0; // how many spaces to the right we are of y axis
	int max = (b > 0)?-b/2:2 * b; // Till what y value should we go ?
	bool xaxis = false; // Have we drawn an xaxis ?

	printf("^\n|\n"); // y axis arrow head

	// start at y intercept, go till y = 0 (recall m is -ve)
	// TODO: possible optimisation
	while (y >= max) {
		yr = y; // Our real y coordinate is y

		if (y != 0)
			for (int j = x - 1; j > 0; j--)
				printf(" ");

		printf(". (%d, %d)", x, y);
		x++;
		y += m;

		// Broken x axis code
		if (xaxis == false && y <= 0) {
			int o = x - 1;

			for (; yr > 0; yr--)
				printf("\n|");

			while (o-- > 0)
				printf("-");

			xaxis = true;
		}

		// y decreases by slope amount for x += 1. so print (m) \n
		//printf("yr: %d y: %d\n", yr, y);

		for (int j = yr; j > y; j--)
			printf("\n|");
	}
}

void graph_pos(int m, int b) {
	int x = 2 * (b > 0)?b:-b; // Initially, x is far to the right. We have taken this as 2 * b
	int y = m * x + b; // initialy y value;

	printf("^"); // starting y-axis

	// We plot only the first and third quadrants
	// Todo: xaxis
	while (x > 0) {

		for (int j = x - 1; j > 0; j--)
			printf(" ");

		printf(". (%d, %d)", x, y);
		y -= m;
		x--;

		for (int i = m; i > 0; i--)
			printf("\n|");
	}
	printf("\b. (%d %d)\n", x, y);
}

void graph_0(int m, int b) {
	printf("^\n|\n"); // print the starting yaxis
	for (int i = 0; i < 12; i++)
		printf("-");
	printf(">\n");

	// if statement goes here

	// What to do with this ? abs(b)
	while (b-- > 0)
		printf("|\n");

	for (int i = 0; i < 12; i++)
		printf("-");
	printf(">\n");
}
