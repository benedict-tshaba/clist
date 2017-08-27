#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned int hash(const char*);

enum {BUCKET = 1024};
typedef enum {I, S, D}ID;

struct Node {
	char *key; //const char *key;
	ID id;
	void *data;
	int hash;
	struct Node *next;
};

struct Table {
	struct Node *array[BUCKET];
};

struct Table *create(void) {
	struct Table *t;
	t = (struct Table*)calloc(1, sizeof(struct Table));
	return t;
}

void add(struct Table *t,ID id, const char *key, void *data) {
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
}

int search(struct Table *t, const char *key, void *data) {
	struct Node *p;
	int h = hash(key);
	for(p=t->array[h%1024]; p!=NULL; p=p->next) {
		if((p->hash==h) && strcmp(p->key, key) == 0) {
			//*data = p->data;
			return 1;
		}
	}
	return 0;
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

int main() {
	const char *names[] = {"Phomolo", "Thekgo", "Puleng", "Tebatso", "Molemo", "Tshepo", "Isaac"};
	struct Table *t = create();
	ID id;
	for(int i=0;i<7;i++) {
		add(t, S, names[i], &names[i]);
		add(t, I, names[(i+3)%7], &i);
	}
	double pi = 3.1415;
	add(t, D, "PIE", &pi);
	print(t);
	libr8(t);
	return 0;
}
