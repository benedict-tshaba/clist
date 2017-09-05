#include <stdio.h>
#include <assert.h>
#include "clist.h"

int main() {
	const char *names[] = {"Phomolo", "Thekgo", "Puleng", "Tebatso", "Molemo", "Tshepo", "Isaac"};

	//create the table/array to hold the list.
	puts("Creating list...");
	table_t t = create();

	puts("Adding 15 elements to our list...");
	for(int i=0;i<7;i++) {
		append(t, S, &names[i]);
		append(t, I, &i);
	}

	double pi = 3.1415;
	append(t, D, &pi); //Add pi to the end of the list.

	assert(15 == length(t));
	printf("Testing length(): %d\n", length(t));
	puts("\nTesting print() function");
	print(t);

	puts("\nTesting sort()...");
	sort_asc(t);
	print(t);
	
	puts("\nTesting is_in()...");
	printf("%f is in list @ %d\n%s is in list @ %d\n",pi,is_in(t,D,&pi),names[0], is_in(t,S,&names[0]));
	const char *str[] = {"notinlist","test"};
	assert(-1==is_in(t,S,&str[0]));
	assert(-1==is_in(t,S,&str[1]));
	printf("is_in(%s) returned: %d\nis_in(%s) returned: %d\n",str[0],is_in(t,S,&str[0]),str[1],is_in(t,S,&str[1]));
	
	int i = 4;
	puts("\nTesting Pop() by pop()'ing 4 items from the end of the list");
	while(i>0){
	pop(t);
	i--;
	}
	assert(11 == length(t));
	printf("After pop()'ing 4 items length = %d\n",length(t));
	print(t);

	int z3=3, z2=2;
	puts("\nTesting remove_item()...");
	remove_item(t,S,&names[1]);
	printf("length of new list after removing %s : %d\n",names[1],length(t));
	print(t);
	printf("%s is @ %d\n",names[4],is_in(t,S,&names[4]));
	remove_item(t,I,&z3);
	remove_item(t,I,&z2);
	assert(8 == length(t));
	printf("%s is now @ %d\n",names[4],is_in(t,S,&names[4]));
	print(t);
	puts("\nTesting sort(): sorting list...");
	sort_asc(t);
	print(t);
	puts("\n[!]Done[!]\nFree()'ing/liberating the list...");
	libr8(t);
	return 0;
}
