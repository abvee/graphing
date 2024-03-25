#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;
enum {MAX = 101}; // MAx length of arbritary arrays

int myatoi(char *string_to_convert); // String to integer
void graph_neg(int m, int b);
void graph_pos(int m, int b);
void graph_0(int b);

#define dprint(x) printf("\033[1;31mDEBUG\033[0m: " #x " %d\n", (x))


// This only works for the first quadrant
int main(int argc, char *argv[]) {

	if (argc != 3) {
		printf("Put in 2 arguments\n");
		return -1;
	}

	int m = myatoi(argv[1]); // slope
	int b = myatoi(argv[2]); // offset
	if (m > 100 || m < -100 || b > 100 || b < -100) {
		printf("Put in a smaller slope or offset. keep it to 100, what you're gonna scroll forever ??\n");
		return 1;
	}

	if (m < 0)
		graph_neg(m, b);
	else if (m == 0)
		graph_0(b);
	else
		graph_pos(m, b);

	return 0;
}

// change text to number
int myatoi(char *s) {
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

static char spaces[MAX] = {'\0'};
int end_x;

/*
plot regular point that's not on x axis'
*/
void plot(int x, int y) {
	int o = x;
	if (x > 0)
		printf("%s|", spaces);
	else {
	 // if we go to the 2nd or third quadrant, x is now how far from the last x value.
		x = -end_x+x + 1;
	}
	for (int i = x - 1; i > 0; i--)
		putchar(' ');
	printf(". (%d, %d)", o, y);
}

/*
Draw the x axis
*/
void draw_x(int x, int y) {
	x = -end_x + x;
	// dprint(x);
	putchar('<');
	if (y == 0) {
		for (int i = 0; i < x-1; i++)
			putchar('-');
		printf(". (%d, %d)", x + end_x, y);
	}
	for (int i = end_x * 2; i < 0; i++)
		putchar('-');
	putchar('>');
}

// draw a graph with -ve slope
void graph_neg(int m, int b) {
	int y = b; // y level of point
	int x = 0; // x level

	int yr = y; // real y level
	int max = 2 * b; // Where do we plot till
	printf("^\n|\n");

	// Plot the +ve part
	if (b > 0) {
		for (; y > 0; y += m) {
			for (; yr > y; yr--)
				printf("\n|");
			plot(x++, y); }
		max = -b;
	}

	// Plot the X axis
	for (;yr > 0; yr--)
		printf("\n|");
	if (y == 0) {
		plot(x++, y);
		y+=m;
		printf("--->");
	}
	else if (yr > 0) { // checks if offset itself is not -ve
		int o = 2 * x;
		while (o-- > 0)
			putchar('-');
		putchar('>');
	}

	// plot bellow x axis
	for (; y > max; y+=m) {
		for (; yr > y; yr--)
			printf("\n|");
		plot(x++, y);
	}
	putchar('\n');
}

void graph_pos(int m, int b) {
	// setting
	int x;
	if (b > 0) x = b; 
	else x = -b;

	end_x = -x; // end_x requires more calculations

	int y = m * x + b;
	int yr;
	for (int i = 0; i < -end_x; i++)
		spaces[i] = ' ';

	// plot above the x axis
	for (; y > 0; y-=m) {
		for (; yr > y+1; yr--)
			printf("%s|\n", spaces);
		yr = y;
		plot(x--, y);
		putchar('\n');
	}
	yr--; // newline is printed at the end, our real y value is less

	// plot x axis
	for (; yr > 0; yr--)
		printf("%s|\n", spaces);
	draw_x(x, y);
	// effectively plotted a point
	if (y == 0) {
		y -= m;
		x--;
	}
	putchar('\n');

	// plot bellow the x axis
	for (; x >= end_x; y-=m) {
		for (; yr > y+1; yr--)
			printf("%s|\n", spaces);
		yr = y;
		plot(x--, y);
		putchar('\n');
	}
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
