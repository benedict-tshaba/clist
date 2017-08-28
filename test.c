#include <stdio.h>
#include "clist.h"

int main() {
	const char *names[] = {"Phomolo", "Thekgo", "Puleng", "Tebatso", "Molemo", "Tshepo", "Isaac"};
	table_t t = create();
	for(int i=0;i<7;i++) {
		append(t, S, &names[i]);
		append(t, I, &i);
	}
	double pi = 3.1415;
	append(t, D, &pi);
	printf("length of list: %d\n", length(t));
	print(t);

	printf("\npie is in list @ %d\nphomolo is in list @ %d\n",is_in(t,D,&pi), is_in(t,S,&names[0]));
	const char *str[] = {"notinlist","test"};
	printf("is_in(%s) returned: %d\nis_in(%s) returned: %d\n",str[0],is_in(t,S,&str[0]),str[1],is_in(t,S,&str[1]));

	libr8(t);
	return 0;
}
