#include <stdio.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "hashes.h"

int count_of_digits(LongInt l1, LongInt l2){
	List<LongInt> list_div;
	
	while (true) {
		LongInt l = l1%l2;
		if(list_div.in(l)){
			printf("list of div "); print(list_div);
			return list_div.size() - list_div.find(l);
		}
		
		if (l == 0){
			break;
		}
		list_div.append(l);
		l1 = l;
		l1*=10;
	}
	return list_div.size();
}

int main() {
    clear();
	LongInt one = 1;
	int max_size=0;
	int max_div=0;
	for (int i = 2; i < 1000; i += 1){
		printf("divisor %d\n",i);
		int c = count_of_digits(one, i);
		printf("size %d\n\n", c);
		if (max_size < c){
			max_size = c;
			max_div = i;
		}
	}
    printf("size is %d\n divisor is $%d", max_size, max_div);
	return 0;
}
