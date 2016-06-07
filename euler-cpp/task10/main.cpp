#include <stdio.h>
#include <string.h>
#include <math.h>

struct Vec2d {
	float x;
	float y;
};

struct AABB {
	Vec2d bbl;
	Vec2d fur;
};

int list[1000000];
int len = 0;

bool is_prime(int x) {
	float x_2 = sqrt(x);
	for (int i = 0; i < len; i += 1) {
		if (list[i] > x_2) {
			return true;
		}
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

int pif(){
	for(int a = 0; a < 1000; a += 1){
		for(int b = 0; b < a; b += 1){
			int c = 1000 - a - b;
			if (c*c == a*a + b*b) {
				printf("%d, a=> %d, b=> %d, c=> %d\n", a*b*c, a, b, c);
				return a*b*c;
			}
		}
	}
	return -1;
}



const char* MEGA_STRING = 
	"96983520312774506326239578318016984801869478851843"
	"73167176531330624919225119674426574742355349194934"
	"85861560789112949495459501737958331952853208805511"
	"12540698747158523863050715693290963295227443043557"
	"66896648950445244523161731856403098711121722383113"
	"62229893423380308135336276614282806444486645238749"
	"30358907296290491560440772390713810515859307960866"
	"70172427121883998797908792274921901699720888093776"
	"65727333001053367881220235421809751254540594752243"
	"52584907711670556013604839586446706324415722155397"
	"53697817977846174064955149290862569321978468622482"
	"83972241375657056057490261407972968652414535100474"
	"82166370484403199890008895243450658541227588666881"
	"16427171479924442928230863465674813919123162824586"
	"17866458359124566529476545682848912883142607690042"
	"24219022671055626321111109370544217506941658960408"
	"07198403850962455444362981230987879927244284909188"
	"84580156166097919133875499200524063689912560717606"
	"71636269561882670428252483600823257530420752963450"
	"05886116467109405077541002256983155200055935729725"
	"71636269561882670428252483600823257530420752963450"

;

int convert(char c) {
	return c - '0';
}

long long mul(const char* s) {
	long long result = 1;
	for (int i = 0; i < 13; i += 1) {
		result *= convert(s[i]);
	}
	return result;
}
int main() {
	add(2);
	long long sum =2;
	for (int i = 3; i < 2000000; i += 2){
		if (is_prime(i)){
			add(i);
			sum += i;
		}
	}
	printf("result %lli\n", sum);
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
	// }
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
		// for(int i = 2; len < 10001; i += 1) {
		// if (is_prime(i)) {
		// add(i);
		// }
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
