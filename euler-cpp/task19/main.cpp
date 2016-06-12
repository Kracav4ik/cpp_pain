#include <stdio.h>
#include <string.h>
#include <math.h>

int is_leap(int year) {
	if (year % 100 == 0) {
		return year % 400 == 0;
	} else{
		return year % 4 == 0;
	}
}

int days_count [12] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};

int main() {
	int i = 0;
	int s_count = 0;
	for(int year = 1900; year < 2001; year += 1) {
		for(int j = 0; j < 12; j += 1) {
			int count = days_count[j];
			if (is_leap(year) && count == 28) {
				count += 1;
			}
			i = (i + count) % 7;
			if (year != 1900 && i ==6) {
				s_count += 1;
			}
		}
	}
	
	printf("%d", s_count);
	
	return 0;
}
