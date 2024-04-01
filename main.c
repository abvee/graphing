#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;
enum {MAX = 101, LIMIT = 20}; // arbritrary constants

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
int end_x; // x coord of left most point

/*
plot regular point that's not on x axis
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
	x = -end_x + x; // transform x to offset from leftmost point

	if (x != 0) // edge case
		putchar('<');

	if (y == 0) {
		for (int i = 0; i < x-1; i++)
			putchar('-');
		printf(". (%d, %d)", x + end_x, y);
	}

	for (int i = (end_x == 0)?-x:end_x * 2; i < 0; i++)
		putchar('-');
	putchar('>');
}

// draw a graph with -ve slope
void graph_neg(int m, int b) {
	int x; // x level
	int max_x; // max level we set x to

	if (b > 0) {
		x = 0;
		max_x = (-b / m) * 2;
	}
	else if (b == 0){
		x = -LIMIT;
		max_x = LIMIT;
	}
	else {
		x = (-b/m) - (-b);
		max_x = 2 * -b;
	}

	end_x = x; // what ?? How did I come up with this ?

	int y = m * x + b; // y level of point
	int yr = y; // real y level
	for (int i = 0; i < -end_x; i++)
		spaces[i] = ' ';
	
	// top arrows
	printf("%s^\n%s|\n", spaces, spaces);

	// Above x axis
	for (; y > 0; y += m) {
		for (; yr > y+1; yr--)
			printf("%s|\n", spaces);
		yr = y;
		plot(x++, y);
		putchar('\n');
	}

	yr--; // newline at the end of the loop makes our real y level 1 less

	// Plot the X axis
	for (; yr > 0; yr--)
		printf("%s|\n", spaces);
	draw_x(x, y);
	if (y == 0) {
		x++;
		y+=m;
	}
	putchar('\n');

	// plot bellow x axis
	/*
	(-b/m) is x when y == 0. Double that for x coord of last point.
	you also end up with the same number of points below x axis as above
	*/
	for (; x <= max_x; y+=m) {
		for (; yr > y+1; yr--)
			printf("%s|\n", spaces);
		yr = y;
		plot(x++ ,y);
		putchar('\n');
	}
}

void graph_pos(int m, int b) {
	// setting
	int x;
	if (b > 0) x = b; 
	else if (b == 0) x = LIMIT;
	else x = -b;

	end_x = -x; // end_x requires more calculations

	int y = m * x + b;
	int yr = y; // Ensures first loop condition fails
	for (int i = 0; i < -end_x; i++)
		spaces[i] = ' ';

	// top arrows
	printf("%s^\n%s|\n", spaces, spaces);

	// plot above the x axis
	for (; y > 0; y-=m) {
		for (; yr > y+1; yr--)
			printf("%s|\n", spaces);
		yr = y;
		plot(x--, y);
		putchar('\n');
	}
	yr--; // newline is printed at the end, our real y value should be 1 less

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
	printf("%s|\n", spaces);
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
