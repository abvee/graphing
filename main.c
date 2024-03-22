#include <stdio.h>

typedef enum {false, true} bool;

int atoi(char *string_to_convert); // String to integer
void graph_neg(int m, int b);
void graph_pos(int m, int b);
void graph_0(int b);

#define printd(x) printf("\033[1;31mDEBUG\033[0m: " #x " %d\n", (x))


// This only works for the first quadrant
int main(int argc, char *argv[]) {
	// printf("\033[1;31mDEBUG:\033[0m %d\n", (12));
	// return 0;

	if (argc != 3) {
		printf("Put in 2 arguments\n");
		return -1;
	}

	int m = atoi(argv[1]); // slope
	int b = atoi(argv[2]); // offset
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
			plot(x++, y, ' ');
		}
		max = -b;
	}

	// Plot the X axis
	for (;yr > 0; yr--)
		printf("\n|");
	if (y == 0) {
		plot(x++, y, '-');
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
		plot(x++, y, ' ');
	}
	putchar('\n');
}

void graph_pos(int m, int b) {
	int x;
	int x_0; // x of point that is just above x-axis 
	int end_x;
	// printd(x_0);

	x_0 = (-b / m);
	/*
	m * (x_0) is always <= b
	Thus, x_0 is the (x) coord just on or bellow the x axis if b < 0
	x_0 is the (x) coord just on or above the x axis if b > 0
	*/
	if (b > 0) {
		x = b; 
		if (b % m == 0) // x_0 on the xaxis, move it one up
			x_0 += 1;
	}
	else {
		x = -b;
		x_0 += 1;
	}
	end_x = -x; // we plot as much above as we do bellow
	char spaces[end_x];
	for (int i = end_x; i > 0; i++)
		spaces[end_x] = ' ';
	printf("DEBUG: %s\n", spaces);

	printd(x_0);
	// printd(end_x);
	int y = m * x + b;
	int yr = y; // real y level

	printf("^\n|");

	// plot above the x axis
	for (; y > 0; y-=m) {
		for (; yr > y; yr--)
			printf("\n|");
		plot(x--, y, ' ');
	}

	// plot x axis
	for (; yr > 0; yr--)
		printf("\n|");

	if (y == 0) {
		plot(x--, y, '-');
		y-=m;
		printf("--->");
	}
	else {
		int o = 2 * x;
		while (o-- > 0)
			putchar('-');
		putchar('>');
	}

	// plot bellow the x axis
	/*
	The x > 0 condition is just wrong.
	Take m = 2, b = 8. x becomes < 0 before the first loop is even over
	*/
	for (; x > 0; x--) {
		for (; yr > y; yr--)
			printf("\n|");
		plot(x, y, ' ');
		y -= m;
	}
	putchar('\n');
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
