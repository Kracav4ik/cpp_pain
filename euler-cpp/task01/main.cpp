#include <stdio.h>

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

int main() {
	int sum = 0;
	for (int i = 0; i < 1000; i += 1) {
		if (i % 3 == 0 || i % 5 == 0) {
			sum += i;
		}
	}
	printf("%d",sum);
	return 0;
}
