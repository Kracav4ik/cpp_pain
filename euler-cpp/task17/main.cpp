#include <stdio.h>
#include <string.h>
#include <math.h>

#include "utils.h"

const char* parts[1001] = {0};

#define SEP ""

void init_parts() {
    parts[1] = "one";
    parts[2] = "two";
    parts[3] = "three";
    parts[4] = "four";
    parts[5] = "five";
    parts[6] = "six";
    parts[7] = "seven";
    parts[8] = "eight";
    parts[9] = "nine";
    parts[10] = "ten";
    parts[11] = "eleven";
    parts[12] = "twelve";
    parts[13] = "thirteen";
    parts[14] = "fourteen";
    parts[15] = "fifteen";
    parts[16] = "sixteen";
    parts[17] = "seventeen";
    parts[18] = "eighteen";
    parts[19] = "nineteen";
    parts[20] = "twenty";
    parts[30] = "thirty";
    parts[40] = "forty";
    parts[50] = "fifty";
    parts[60] = "sixty";
    parts[70] = "seventy";
    parts[80] = "eighty";
    parts[90] = "ninety";
    parts[100] = "one" SEP "hundred";
    parts[200] = "two" SEP "hundred";
    parts[300] = "three" SEP "hundred";
    parts[400] = "four" SEP "hundred";
    parts[500] = "five" SEP "hundred";
    parts[600] = "six" SEP "hundred";
    parts[700] = "seven" SEP "hundred";
    parts[800] = "eight" SEP "hundred";
    parts[900] = "nine" SEP "hundred";
    parts[1000] = "one" SEP "thousand";
}

String sep(SEP);
String and("and");

String to_string_99(int n) {
    if (parts[n]) {
        return String(parts[n]);
    }
    int ten = (n/10)*10;
    int digit = n % 10;
    return String(parts[ten]) + sep + String(parts[digit]);
}

String to_string_999(int n) {
    if (parts[n]) {
        return String(parts[n]);
    }
    int hunder = (n/100)*100;
    if(!hunder) {
        return to_string_99(n);
    }
    int m = n - hunder;
    int digit = n % 10;
    return String(parts[hunder]) + sep + and + sep + to_string_99(m);
}

int main() {
    init_parts();
    int sum = 0;
    for (int i = 1; i < 1001; i += 1) {
        String s = to_string_999(i);
        sum += s.len;
        printf("%d %s\n",sum, s.str);
    }
    printf("%d\n",sum);
    return 0;
}
