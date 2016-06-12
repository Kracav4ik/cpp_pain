#include <stdio.h>
#include <string.h>
#include <math.h>

int max(int x1, int x2) {
	if (x1 > x2) {
		return x1;
	}
	return x2;
}


int convert(char c) {
	return c - '0';
}

char convert_to_str(int c) {
	return c + '0';
}

const int LEN = 400;

void add_arrays(int *m, int *n, int size) {
	int carry = 0;
	for(int i = 0; i < size; i +=1) {
		int product = m[i] + n[i] + carry;
		m[i] = product % 10;
		carry = product / 10;
	}
}

struct LongInt100 {
	int digits[LEN];
	
	LongInt100(const char* s) {
		int len_s = strlen(s);
		for (int i = 0; i < LEN; i += 1) {
			if (i < len_s){
				digits[i] = convert(s[len_s - (i+1)]);
			} else {
				digits[i] = 0;
			}
		}
	}
	
	void add(LongInt100 x) {
		add_arrays(digits, x.digits, LEN);
	}
	
	void to_string(char* s) {
		int i = 0;
		bool b = false;
		for (int j = LEN-1; j > -1; j -= 1) {
			if (digits[j] != 0 || b) {
				s[i] = convert_to_str(digits[j]);
				i += 1;
				b = true;
			}
		}
		if (i == 0) {
			s[i] = convert_to_str(0);
			i += 1;
		}
		s[i] = 0;
	}
	
	void mul(LongInt100 x) {
		int result_offset = 0;
		int result [LEN];
		int subresult [LEN];
		for (int i = 0; i < LEN; i += 1) {
			result[i] = 0;
			subresult[i] = 0;
		}
		for (int i = 0; i < LEN; i += 1) {
			int subresult_carry = 0;
			for (int j = 0; j < LEN; j += 1) {
				int product = digits[i] * x.digits[j] + subresult_carry;
				subresult[j] += product % 10;
				subresult_carry = product / 10;
				// printf("digits[%2d] * x.digits[%2d] = %d * %d = product = %2d; carry = %d; add[%d] = %d \n", i, j, 
				// digits[i], x.digits[j], product, subresult_carry, j, subresult[j]);
			}
			// printf(" result\n") ;
			add_arrays(result + result_offset, subresult, LEN);
			for (int j = 0; j < LEN; j += 1) {
				subresult[j] = 0;
				// printf("add[%d] = %d \n",j, result[j]);
			}
			result_offset += 1;
		}
		for (int i = 0; i < LEN; i += 1) {
			digits[i] = result[i];
		}
		
	}
	
};

int main() {
	LongInt100 num("1");
	LongInt100 ini("1");
	LongInt100 j("1");
	int sum = 0;
	for(int i = 1; i < 101; i += 1) {
		num.mul(ini);
		ini.add(j);
	}
	
	for(int i = 0; i < LEN; i += 1) {
		sum += num.digits[i];
	}
	
	printf("%d", sum);
	
	return 0;
}
