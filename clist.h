#ifndef _CLIST_H
#define _CLIST_H

enum {BUCKET = 1024}; //The size of the hash table. I naively assume that we will never need a bigger table than this.

/*Defines a type type_t where: I=int, S=string, D=double*/
typedef enum {I, S, D}type_t; 

struct Node {
	type_t type;
	void *data;
	int index;
	struct Node *next;
};

struct Table {
	int size;
	struct Node *array[BUCKET];
};

typedef struct Table* table_t; //type of pointer to hash table.

/* Creates a array Table. Returns a pointer to the array Table struct.
*/
struct Table *create(void);

/* Inserts a new item to the list.
 Params:(struct Table*) Poiter to the Table struct,
	(type_t) (the type of the data you are adding), 
	(void *) pointer to the data/item you want to add.
*/
void append(struct Table*,type_t, void *);

/* Frees the array table and all its associated data.
 Params: pointer to the Table struct which was create()'d.
*/
void libr8(struct Table*);

/* Prints the list. Params: pointer to the array table.*/
void print(struct Table*);

/* Returns the number of items in the array table.*/
int length(struct Table*);

/* Returns the index in the array of the item.
 -1 otherwise.*/
int is_in(struct Table *t, type_t, void *);

/* Removes the last item in the list.*/
void pop(table_t);

/* Removes an item from the list if that item is in the list.
 * Changed to remove_item due to conflict with remove from stdio.h*/
void remove_item(table_t, type_t, void *);
#endif
