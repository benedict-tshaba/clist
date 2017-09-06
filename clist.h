/*
# Interface to clist library.
# 
# Copyright (C) 2017 Tshaba Phomolo Benedict

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _CLIST_H
#define _CLIST_H

enum {BUCKET = 1024}; //The size of the hash table. I naively assume that we will never need a bigger table than this.

/*Defines a type type_t where: I=int, S=string, D=double*/
typedef enum {I, S, D}type_t; 

struct Node {
	type_t type;
	int index;
	void *data;
	long int repr; //this is the internal representation of the data.
	struct Node *next;
};

struct Table {
	int size;
	struct Node *array[BUCKET];
};

typedef struct Table* table_t; //type of pointer to hash table.

/* Creates a array Table. Returns a pointer to the array Table struct.
*/
table_t create(void);

/* Inserts a new item to the list.
 Params:(struct Table*) Poiter to the Table struct,
	(type_t) (the type of the data you are adding), 
	(void *) pointer to the data/item you want to add.
*/
void append(table_t,type_t, void *);

/* Inserts a new item to the beginning of the list.
 Params:(struct Table*) Poiter to the Table struct,
	(type_t) (the type of the data you are adding), 
	(void *) pointer to the data/item you want to add.
*/
void prepend(table_t,type_t, void *);

/* Frees the array table and all its associated data.
 Params: pointer to the Table struct which was create()'d.
*/
void libr8(table_t);

/* Prints the list. Params: pointer to the array table.*/
void print(table_t);

/* Returns the number of items in the array table.*/
int length(table_t);

/* Returns the index in the array of the item.
 -1 otherwise.*/
int is_in(table_t, type_t, void *);

/* Removes the last item in the list.*/
void pop(table_t);

/* Removes an item from the list if that item is in the list.
 * Changed to remove_item due to conflict with remove from stdio.h*/
void remove_item(table_t, type_t, void *);

/* Sorts the 'list' in place(ascending order), takes in the pointer 
 * to the 'list' as its argument and returns nothing.*/
void sort_asc(table_t);
#endif
