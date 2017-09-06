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
		p->repr = *(double*)data+1; //>=0) ? (long int)(*(double*)data + 0.5) : (long int)(*(double*)data - 0.5);
	}
	p->next = t->array[t->size];
	t->array[t->size] = p;
	t->size++;
	t->array[t->size] = NULL;
}

void prepend(struct Table *t,type_t type, void *data) {
	if(t->size == 0) { //this is the first ever element.
		append(t,type,data);
	}

	struct Node *p = (struct Node*)malloc(sizeof(struct Node));
	assert(t->size <= BUCKET-1); //check for out of bounds access
	
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
		p->repr = *(double*)data+1; //>=0) ? (long int)(*(double*)data + 0.5) : (long int)(*(double*)data - 0.5);
	}

	int size = t->size;

	for(size; size>0 ;size--) {
		t->array[size] = t->array[size-1];
		t->array[size]->index++;
	}
	p->index = size;
	t->array[size] = p;
	t->size++;
	p->next = t->array[t->size] = NULL;
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
	for(int i=0;i<t->size;i++)
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
	if(index == -1) return; //data is not in list.

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
	/*s->index ^= d->index;
	d->index ^= s->index;
	s->index ^= d->index;
*/
	int tp;
	tp = s->index;
	s->index = d->index;
	d->index = tp;

	// swap the pointers in our array.
	temp = t->array[srci];
	t->array[srci] = t->array[dsti];
	t->array[dsti] = temp;
}

long int _hash(const char *str) {
        long int ret=0;
        for(int i=0;str[i] != '\0';i++) {
                ret += str[i];    
        }
        return ret*6737; //6737 chosen arbitrarily to ensure that the string representation is no less than an ordinary integer. Perhaps a prime number might do better.

}

void _str_sort(table_t t) {
	//Finally sort the strings properly, this will incur a heavy penalty.
	int ind=0;
	while(t->array[ind]!=NULL && t->array[ind+1]!=NULL) {
		if(t->array[ind]->repr%6737==0 && t->array[ind+1]->repr%6737==0) {
		if(strcmp(*(char**)t->array[ind]->data, *(char**)t->array[ind+1]->data) > 0) {
			_swap(t,t->array[ind],t->array[ind+1]);

		}
		}
		ind++;
	}
}

void _hqsort(table_t t, int m, int n) {
	int i,j,k;
	struct Node *key;
	if(m < n) {
		k = (m+n)/2;
		_swap(t, t->array[m], t->array[k]);
		key = t->array[m];
		i = m+1;
		j = n;
		while(i<=j) {
			while((i<=n) && (t->array[i]->repr<=key->repr))
				i++;
			while((j>=m) && (t->array[j]->repr>key->repr))
				j--;
			if(i<j)
				_swap(t, t->array[i], t->array[j]);
		}
		_swap(t, t->array[m],t->array[j]);
		_hqsort(t,m,j-1);
		_hqsort(t,j+1,n);
	}
	_str_sort(t);
}
//End of helper functions.

void sort_asc(table_t t) {
	_hqsort(t,0,t->size-1);
}


void print(struct Table *t) {
	struct Node *p;
	struct Node *nextp;
	int i = 0;
	for(i=0;i<t->size;i++) //changed i<BUCKET; because be already know the size of our 'list'
	for(p=t->array[i]; p!= NULL; p=nextp) {
		if(p->type==I) printf("%d ",*(int*)p->data);
		else if(p->type==S) printf("%s ",*(char**)p->data);
		else if(p->type==D) printf("%f ",*(double*)p->data);
		nextp = p->next;
	}
	puts(""); //print a newline at end of list.
}
