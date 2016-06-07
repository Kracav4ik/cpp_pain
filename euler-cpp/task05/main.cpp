#include <stdio.h>
#include <string.h>

struct Vec2d {
	float x;
	float y;
};

struct AABB {
	Vec2d bbl;
	Vec2d fur;
};

void f(int x) {
	printf("x\n");
}

void f() {
	for (int i = 0; i < 10; i += 1) {
		printf("%d\n", i);
	}
}

bool is_palindrome(int number) {
	char list[10];
	int div = 100000;
	for (int i = 0 ; i < 6; i += 1) {
		list[i] = number / div;
		number -= list[i] * div;
		div /= 10;
	}
	if (list[0] == list[5] && list[1] == list[4] && list[2] == list[3]) {
		return true;
	}
	return false;
	
}

int main() {
	// char s[10];
	// sprintf(s, "%d", 105);
	// long pal = -1;
	// for (int i = 100; i < 1000; i += 1) {
		// for (int j = 100; j < 1000; j += 1) {
			// if (is_palindrome(i*j) && pal < i*j) {
				// pal = i*j;
			// }
		// }
	// }
	printf("%d", 16*9*5*7*11*13*17*19);
	// printf("%d\n", strlen(s));
	// s[3] = 34;
	// s[4] = 32;
	// s[5] = 33;
	// printf("%d\n", strlen(s));
	return 0;
}
