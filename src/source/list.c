#include "list.h"

list_t* list_constructor(
		void (*data_destructor)(void* data),
		void (*print_data)(const void* data)
)
{
	list_t* list = (list_t*)malloc(sizeof(list_t));
	list->data_destructor = data_destructor;
	list->print_data = print_data;
	
	list->first = NULL;
	list->last = NULL;
	list->size = 0;
	
	return list;
}

void list_destructor(list_t* l) {
	while (l->size > 0) {
		void* data = list_pop_front(l);
		l->data_destructor(data);
	}
	free(l);
}

#define BACK 1
#define FRONT -1

static int list_push(list_t* l, void* data, int where) {
	if (!l)
		return 0;
	
	list_node_t* node = (list_node_t*)malloc(sizeof(list_node_t));
	node->data = data;
	
	// Insertion in empty list
	if (l->size == 0) { 
		node->next = NULL;
		node->previous = NULL;
		l->first = node;
		l->last = node;
	}
	else if (where == BACK) {
		node->next = NULL;
		node->previous = l->last;
		l->last->next = node;
		l->last = node;
	}
	else {
		node->previous = NULL;
		node->next = l->first;
		l->first->previous = node;
		l->first = node;
	}
	
	++(l->size);
	return 1;
}

int list_push_front(list_t* l, void* data) {
	return list_push(l, data, FRONT);
}

int list_push_back(list_t* l, void* data) {
	return list_push(l, data, BACK);
}

static void* list_pop(list_t* l, int where) {
	if (!l || l->size == 0)
		return NULL;
	
	list_node_t* node;
	if (l->size == 1) {
		node = l->first;
		l->first = NULL;
		l->last = NULL;
	}
	else if (where == BACK) {
		node = l->last;
		l->last->previous->next = NULL;
		l->last = node->previous;
	}
	else {
		node = l->first;
		l->first->next->previous = NULL;
		l->first = node->next;
	}
	
	void* data = node->data;
	free(node);
	--(l->size);
	
	return data;
}

void* list_pop_back(list_t* l) {
	return list_pop(l, BACK);
}

void* list_pop_front(list_t* l) {
	return list_pop(l, FRONT);
}

void* list_peek_back(list_t* l)
{
	return l->last->data;
}

void* list_peek_front(list_t* l)
{
	return l->first->data;
}

#undef BACK
#undef FRONT
