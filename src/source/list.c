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
}

#define BACK 1
#define FRONT -1

static int list_push(list_t* t, void* data, int where) {
	if (!t)
		return 0;
	
	list_node_t* node_valid_neighbor = where == BACK ? t->last : t->first;
	list_node_t** node_null_neighbor_pointer = where == FRONT ? &node->next : &node->previous;
	
	list_node_t* node = (list_node_t*)malloc(sizeof(list_node_t));
	node->data = data;
	node_null_neighbor_pointer = NULL;
	
	// Could be !t->last, they will be NULL always together
	if (!t->first) { 
		node_valid_neighbor = NULL;
		t->first = node;
		t->last = node;
	}
	else {
		if (where == BACK) {
			node->previous = node_valid_neighbor;
			node_valid_neighbor->next = node;
			t->last = node;
		}
		else  {
			node->next = node_valid_neighbor;
			node_valid_neighbor->last = node;
			t->first = node;
		}
	}
	
	return 1;
}

int list_push_front(list_t* t, void* data) {
	list_push(t, data, FRONT);
}

int list_push_back(list_t* t, void* data) {
	list_push(t, data, BACK);
}

void* list_pop(list_t* t, int where) {
	list_node_t* node;
	list_node_t** node_valid_neighbor_node_pointer;
	if (where == BACK) {
		node = t->last;
		node_valid_neighbor_node_pointer = &t->last->previous->next;
	}
	else {
		node = t->first;
		node_valid_neighbor_node_pointer = &t->first->next->previous;
	}
	
	node_valid_neighbor_node_pointer = NULL;
	void* data = node->data;
	free(node);
	
	return data;
}

void* list_pop_back(list_t* t) {
	return list_pop(t, BACK);
}

void* list_pop_front(list_t* t) {
	return list_pop(t, FRONT);
}

#undef BACK
#undef FRONT