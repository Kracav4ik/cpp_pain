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
	int f1 = 1;
	int f2 = 1;
	int f3;
	int sum = 0;
	while (f1 < 4000000) {
		f3 = f1 + f2;
		f1 = f2;
		f2 = f3;
		if (f3 % 2 == 0) {
			sum += f3;
		}
	}
	printf("%d",sum);
	return 0;
}
