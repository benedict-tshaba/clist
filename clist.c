/*
# clist library.
# A research program into the implemenation of a generic list type in C,
# it serves as a proof of concept that Python's list object can be implemented
# and used within a C program.
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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "clist.h"

long int _hash(const char *);
void _swap(table_t, struct Node*, struct Node*);

struct Table *create(void) {
	struct Table *t;
	t = (struct Table*)calloc(1, sizeof(struct Table));
	t->size=0;
	return t;
}

int length(struct Table *t) {
	return t->size;
}

void append(struct Table *t,type_t type, void *data) {
	struct Node *p = (struct Node*)malloc(sizeof(struct Node));
	assert(t->size <= BUCKET-1); //check for out of bounds access
	p->index = t->size;
	p->type = type;	
	if(type==I) {
		p->data = (int*)malloc(sizeof(int*));
		memcpy(p->data, data, sizeof(int*));
		p->repr = *(long int*)data;
	}
	if(type==S) {
		p->data = (char*)malloc(sizeof(char*));
		memcpy(p->data, data, sizeof(char*));
		p->repr = _hash(*(const char**)data);
	}
	if(type==D) {
		p->data = (double*)malloc(sizeof(double*));
		memcpy(p->data, data, sizeof(double*));
		p->repr = *(long int*)data;
	}
	p->next = t->array[t->size];
	t->array[t->size] = p;
	t->size++;
	t->array[t->size] = NULL;
}

void libr8(struct Table *t) {
	struct Node *p;
	struct Node *nextp;
	for(int b=0; b<BUCKET; b++) {
		for(p=t->array[b]; p!=NULL; p=nextp) {
			nextp = p->next;
			free(p->data);
			free(p);
		}
	}
	free(t);
}

int is_in(struct Table *t, type_t type, void *data) {
	struct Node *p;
	for(int i=0;i<BUCKET;i++)
	for(p=t->array[i]; p!=NULL; p=p->next) {
		if(type == S && p->type == S) {
		       	if(strcmp(*(char**)p->data,*(char**)data) == 0)
				return p->index;
		}
		if(type == I && p->type == I) {
		       	if(*(int*)p->data == *(int*)data)
				return p->index;
		}
		if(type == D && p->type == D) {
			if(*(double*)p->data == *(double*)data)
				return p->index;
		}
	}
	return -1;
}

void pop(table_t t) {
	struct Node *p;
	p=t->array[t->size-1];
	free(p->data);
	free(p);
	t->size--;
	t->array[t->size] = NULL;
}

void remove_item(table_t t, type_t type, void *data) {
	int index = is_in(t, type, data);
	int i=index;
	if(index == -1) return;

	struct Node *p;
	p=t->array[index];
	free(p->data);
	free(p);

	while((p=t->array[i]) != NULL) {
		t->array[i] = t->array[i+1];
		p->index = i-1;
		i++;
	}
	t->array[i] = NULL;
	t->size--;
}

//helper functions for sort_asc. Not visible to the outside.
void _swap(table_t t, struct Node *s, struct Node *d) {
	int srci = s->index;
	int dsti = d->index;
	struct Node *temp;

	// swap the indices first, to reflect new changes.
	s->index ^= d->index;
	d->index ^= s->index;
	s->index ^= d->index;

	// swap the pointers in our array.
	temp = t->array[srci];
	t->array[srci] = t->array[dsti];
	t->array[dsti] = temp;
}

long int _hash(const char *str) {
        int i=0;
        int c;
        long int ret=0;
        while(str[i] != '\0') {
                c = str[i];
                ret += c;
                i++;    
        }
        return ret;

}
//End of helper functions.

void sort_asc(table_t t) {
	struct Node *p;
	struct Node *np;
	int i=0, j=0;
	for(i,p=t->array[i];i<t->size;i++) {
		int index = i;
		for(j=i,np=t->array[i];j<t->size;j++) {
			if(p->repr > np->repr) {
				index = j;
				_swap(t,p,np);
			}
		}
	}
}


void print(struct Table *t) {
	struct Node *p;
	struct Node *nextp;
	int i = 0;
	for(i=0;i<t->size;i++) //changed i<BUCKET; because be already know the size of our 'list'
	for(p=t->array[i]; p!= NULL; p=nextp) {
		if(p->type==I) printf("%d ",*(int*)p->data,p->repr);
		else if(p->type==S) printf("%s ",*(char**)p->data,p->repr);
		else if(p->type==D) printf("%f ",*(double*)p->data,p->repr);
		nextp = p->next;
	}
	puts(""); //print a newline at end of list.
}
