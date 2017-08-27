#include <stdio.h>
#include "clist.h"

int main() {
	const char *names[] = {"Phomolo", "Thekgo", "Puleng", "Tebatso", "Molemo", "Tshepo", "Isaac"};
	struct Table *t = create();
	ID id;
	for(int i=0;i<7;i++) {
		append(t, S, names[i], &names[i]);
		append(t, I, names[(i+3)%7], &i);
	}
	double pi = 3.1415;
	append(t, D, "PIE", &pi);
	printf("len/size of list: %d\n", length(t));
	print(t);
	libr8(t);
	return 0;
}
