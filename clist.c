#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "clist.h"

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
	assert(t->size <= BUCKET-1);
	p->index = t->size;
	p->type = type;	
	if(type==I) {
		p->data = (int*)malloc(sizeof(int*));
		memcpy(p->data, data, sizeof(int*));
	}
	if(type==S) {
		p->data = (char*)malloc(sizeof(char*));
		memcpy(p->data, data, sizeof(char*));
	}
	if(type==D) {
		p->data = (double*)malloc(sizeof(double*));
		memcpy(p->data, data, sizeof(double*));
	}
	p->next = t->array[t->size];
	t->array[t->size] = p;
	t->size++;
	t->array[t->size] = NULL;
}

void libr8(struct Table *t) {
	struct Node *p;
	struct Node *nextp;
	int b;
	for(b=0; b<BUCKET; b++) {
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

void print(struct Table *t) {
	struct Node *p;
	struct Node *nextp;
	int i = 0;
	for(i=0;i<BUCKET;i++)
	for(p=t->array[i]; p!= NULL; p=nextp) {
		if(p->type==I) printf("%d ",*(int*)p->data);
		else if(p->type==S) printf("%s ",*(char**)p->data);
		else if(p->type==D) printf("%f ",*(double*)p->data);
		nextp = p->next;
	}
}
