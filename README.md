This Project aims to implement the LIST data structure as in Python to be usable in a C project. i.e. We aim to create a 'type' of 'list' which will be generic and can contain an int,float,char, etc. as allowed in c. This is just a research project to see if the same concepts that work in Python (an intepreted language) can be applied to a compiled language like C.

An example of what I hope to achieve (Keeping in mind that C is not Object Orientated):
list mylist = list_create("A", 6, 3.1415, "Adam");
size(mylist); //should return 4.
append(mylist, "C");
print(mylist); //should return/print "A", 6, 3.1415, "Adam", "C".

Other supported functions might be prepend, remove, search, sort, etc...


