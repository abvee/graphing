#include <stdio.h>

enum {MAX = 100};
int atoi(char *string_to_convert); // String to integer
void graph_neg(int m, int b);
void graph_pos(int m, int b);

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

void graph_neg(int m, int b) {
	m = abs(m);
	int y = b;
	int x = 0; // how many spaces to the right we are
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < x; j++)
			printf(" ");
		x++;
		printf("-");
		for (int j = 0; j < m; j++)
			printf("\n");
	}
}

void graph_pos(int m, int b) {}
