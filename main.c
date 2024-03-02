#include <stdio.h>

typedef enum {false, true} bool;

int atoi(char *string_to_convert); // String to integer
void graph_neg(int m, int b);
void graph_pos(int m, int b);
void graph_0(int b);

// This only works for the first quadrant
int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Put in 2 arguments\n");
		return -1;
	}

	int m = atoi(argv[1]); // slope
	int b = atoi(argv[2]); // offset

	if (m < 0)
		graph_neg(m, b);
	else if (m == 0)
		graph_0(b);
	else
		graph_pos(m, b);

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

void plot(int x, int y, char c) {
	for (int i = x - 1; i > 0; i--)
		putchar(c);
	printf(". (%d, %d)", x, y);
}
// draw a graph with -ve slope
void graph_neg(int m, int b) {
	int y = b; // y coordinate of the point
	int yr = y; // actual y coordinate
	int x = 0; // x coordinate of point
	int max = (b > 0)?-b/2:2 * b; // max y value

	bool xaxis = false; // Have we drawn x axis

	printf("^\n|\n"); // y axis arrow head

	// draw graph
	while (y >= max) {
		// slope
		for (; yr > y; yr--)
			printf("\n|");
		plot(x++, y, ' ');
		y += m;

		// xaxis code
		if (xaxis == false && y <= 0) {
			for (;yr > 0; yr--) // get to x axis
				printf("\n|");

			int o = x - 1;
			while (o-- > 0)
				putchar('-');

			if (y == 0) {
				plot(x++, y, 0);
				y+=m;
				printf("--->");
			}
			else
				putchar('>')

			xaxis = true;
		}
	}
	putchar('\n');
}

void graph_pos(int m, int b) {
	int x = 2 * (b > 0)?b:-b; // Initially, x is far to the right. We have taken this as 2 * b
	int y = m * x + b; // initialy y value;
	int yr = y;
	bool xaxis = false;

	printf("^"); // starting y-axis

	// We plot only the first and third quadrants
	// Todo: xaxis
	while (x > 0) {
		if (y != 0)
			for (int j = x - 1; j > 0; j--)
				printf(" ");

		printf(". (%d, %d)", x, y);
		y -= m;
		x--;

		// x axis code
		if (xaxis == false && y <= 0) {
			int o = x - 1;
			for (; yr > 0; yr--)
				printf("\n|");

			while (o-- > 0)
				putchar('-');

			xaxis = true;
		}

		for (; yr > y; yr--)
			printf("\n|");
	}
	printf("\b. (%d, %d)\n", x, y);
}

void graph_0(int b) {
	int x = (b > 0)?b:-b; // abs(b)

	printf("^\n|\n"); // print the starting yaxis
	for (int i = 0; i < 12; i++)
		printf("-");
	printf("> ");

	// if statement goes here
	if (b > 0)
		printf("y = %d\n", b);
	else
		printf("y = 0\n");

	// What to do with this ? abs(b)
	while (x-- > 0)
		printf("|\n");

	for (int i = 0; i < 12; i++)
		printf("-");
	printf("> ");

	if (b > 0)
		printf("y = 0\n");
	else
		printf("y = %d\n", b);
}
