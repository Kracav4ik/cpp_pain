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
	long long div = 600851475143 ;
	int fac = 1;
	while (fac < 1000000) {
		if (div % fac == 0) {
			div /= fac;
		}
		if (div==1){
			break;
		}
		fac += 1;
	}
	printf("%d",fac);
	return 0;
}
