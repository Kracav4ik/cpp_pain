#include <stdio.h>


#include "utils.h"
#include "text_file.h"


int main() {
	TextFile file;
	if (file.open("task_b.cpp")) {
		while (true) {
			String s = file.read_line();
			if (s.is_empty()) {
				break;
			}
			printf("%s",s.str());
		}
	}
    return 0;
}
