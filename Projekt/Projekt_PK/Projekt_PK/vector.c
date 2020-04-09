#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

vtr* init_vector(int n){
	vtr* v = (vtr*)malloc(sizeof(vtr));
	if (v) {
		v->data = (bool*)malloc(n * sizeof(bool));
		for (int i = 0; i < n; i++)
			v->data[i] = (rand() % 2);
		v->size = n;
		return v;
	}
	return NULL;
}

vtr* create_vector(int n) {
	vtr* v = (vtr*)malloc(sizeof(vtr));
	if (v) {
		v->data = (bool*)malloc(n * sizeof(bool));
		v->size = n;
		return v;
	}
	else {
		perror("Create_vector");
		exit(2);
	}
}

void copy_from_end_vector(vtr* v1, vtr* v2) {
	if (v1->size >= v2->size) {
		int l = v1->size - v2->size;
		for (int i = 0; i < v2->size; i++)
			v2->data[i] = v1->data[l + i];
	}
}

void paste_at_end_vector(vtr* v1, vtr* v2) {
	if (v1->size > v2->size) {
		int l = v1->size - v2->size;
		for (int i = 0; i < v2->size; i++)
			v1->data[l + i] = v2->data[i];
	}
}

void delete_vector(vtr** v) {
	if ((*v)) {
		free((*v)->data);
		free(*v);
	}
}

int resize_vector(vtr *v, int n) {
	if (v) {
		bool* p = (bool*)realloc(v->data, n * sizeof(bool));
		if (p) {
			v->data = p;
			v->size = n;
		}
		return v->size;
	}
	return 0;
}

bool get_vector(vtr* v, int i) {
	if (v && i < v->size) {
		return v->data[i];
	}
	return 0;
}

void load_vector(vtr* v, int i , bool t) {
	if (v&&i < v->size)
		v->data[i] = t;
}

void print_vector(vtr* v) {
	if (v) {
		for (int i = 0; i < v->size; i++)
			putc((int)v->data[i] + 48, stdout);
	}
}