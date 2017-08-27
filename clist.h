#ifndef _CLIST_H
#define _CLIST_H

/* Returns a hash of key(const char *)*/
unsigned int hash(const char*);

enum {BUCKET = 1024}; //The size of the hash table.

/*Defines a type type_t where: I=int, S=string, D=double*/
typedef enum {I, S, D}type_t; 

struct Node {
	char *key;
	type_t type;
	void *data;
	int hash;
	struct Node *next;
};

struct Table {
	int size;
	struct Node *array[BUCKET];
};

typedef struct Table* table_t; //type of pointer to hash table.

/* Creates a hash Table. Returns a pointer to the hash Table struct.
*/
struct Table *create(void);

/* Inserts a new item to the list.
 Params:(struct Table*) Poiter to the Table struct,
	(ID) id(the type of the data you are adding), 
	(const char*) key(will be hashed to create an entry into the Table), 
	(void *) pointer to the data/item you want to add.
*/
void append(struct Table*,type_t, const char *, void *);

/* Frees the hash table and all its associated data.
 Params: pointer to the Table struct which was create()'d.
*/
void libr8(struct Table*);

/* Prints the list. Params: pointer to the hash table.*/
void print(struct Table*);

/* Returns the number of items in the hash table.*/
int length(struct Table*);

/* Returns the index in the array of the item.
 -1 otherwise.*/
int is_in(struct Table *t, type_t, void *);
#endif
