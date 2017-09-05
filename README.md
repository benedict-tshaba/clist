This Project aims to implement the LIST data structure as in Python to be usable in a C project. i.e. We aim to create a 'type' of 'list' which will be generic and can contain an int,float,char, etc. as allowed in c. This is just a research project to see if the same concepts that work in Python (an intepreted language) can be applied to a compiled language like C.

Example Usage:
```
#include <stdio.h>
#include "clist.h"

int main() {
table_t t = create();
int i = 6;
double pi = 3.1415;
const char *strings[] = {"Kevin","Adam","Carl"};

append(t, I, &i); // I represents an integer. S = string, D = double.
append(t, D, &pi);
for(int j=0; j<3; j++) {
	append(t, S, &strings[j]);
}

print(t); // should print: 6 3.1415 Kevin Adam Carl
sort_asc(t); // sorts the list in place
print(t); // should print: 3.1415 6 Adam Carl Kevin

return 0;
}

```

Other supported functions are remove, and pop.

# TODO:
### Implement prepend - Although at this point it seems unnecessary.
