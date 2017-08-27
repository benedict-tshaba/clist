#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

void append(struct Table *t,ID id, const char *key, void *data) {
	struct Node *p = (struct Node*)malloc(sizeof(struct Node));
	int h = hash(key);
	p->hash = h;
	p->id = id;
	p->key = (char*)malloc(strlen(key)+1);
	strcpy(p->key, key);
	if(id==I) {
		p->data = (int*)malloc(sizeof(int*));
		memcpy(p->data, data, sizeof(int*));
	}
	if(id==S) {
		p->data = (char*)malloc(sizeof(char*));
		memcpy(p->data, data, sizeof(char*));
	}
	if(id==D) {
		p->data = (double*)malloc(sizeof(double*));
		memcpy(p->data, data, sizeof(double*));
	}
	p->next = t->array[h];
	t->array[h] = p;
	t->size++;
}

void libr8(struct Table *t) {
	struct Node *p;
	struct Node *nextp;
	int b;
	for(b=0; b<BUCKET; b++) {
		for(p=t->array[b]; p!=NULL; p=nextp) {
			nextp = p->next;
			free(p->key);
			free(p->data);
			free(p);
		}
	}
	free(t);
}

unsigned int hash(const char *x) {
	int i;
	unsigned int h = 0U;
	for(i=0; x[i]!='\0'; i++) {
		h = h*65599 + (unsigned char)x[i];
	}
	return h&1023;
}

void print(struct Table *t) {
	struct Node *p;
	struct Node *nextp;
	int i = 0;
	for(i=0;i<BUCKET;i++)
	for(p=t->array[i]; p!= NULL; p=nextp) {
		if(p->id==I) printf("%d, ",*(int*)p->data);
		else if(p->id==S) printf("%s, ",*(char**)p->data);
		else if(p->id==D) printf("%f, ",*(double*)p->data);
		nextp = p->next;
	}
}
