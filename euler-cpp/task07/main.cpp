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

int list[10001];
int len = 0;

bool is_prime(int x) {
	for (int i = 0; i < len; i += 1) {
		if (x % list[i] == 0) {
			return false;
		}
	}
	return true;

}

void add(int x) {
	list[len] = x;
	len += 1;
}
int main() {
	for(int i = 2; len < 10001; i += 1) {
		if (is_prime(i)) {
		add(i);
		}
	}
	printf("%d\n", list[10000]);
	return 0;
}

void trash() {
	// char s[10];
	// sprintf(s, "%d", 105);
	// long pal = -1;
	// for (int i = 100; i < 1000; i += 1) {
		// for (int j = 100; j < 1000; j += 1) {
			// if (is_palindrome(i*j) && pal < i*j) {
				// pal = i*j;
			// }
		// }
	// // }
	// // printf("%d", 16*9*5*7*11*13*17*19);
	// printf("%d\n", strlen(s));
	// s[3] = 34;
	// s[4] = 32;
	// s[5] = 33;	
		// int sum=0;
	// int sum2=0;
	// for (int i = 1; i < 101;i += 1) {
		// sum += i*i;
		// sum2 += i;
	// }

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
