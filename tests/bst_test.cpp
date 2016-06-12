#include "gtest/gtest.h"
#include "binary_search_tree.h"
#include <string.h>
#include <stdio.h>

int bst_compare(const void* lhs, const void* rhs) {
	return strcmp((const char*)lhs, (const char*)rhs);
}

void bst_key_destructor(void* key) {
	free(key);
}

void bst_info_destructor(void* info) {
	free(info);
}

void bst_print_key(const void* key) {
	fprintf(stdout, "%s", (char*)key);
}

void bst_print_info(const void* info) {
	fprintf(stdout, "%s", (char*)info);
}

TEST(FOO, BAR) {
	bst_t* t = bst_constructor(bst_compare, bst_key_destructor, bst_info_destructor, bst_print_key, bst_print_info);
	EXPECT_EQ(t->size, 0);
	char key1[] = "r.cmgleite@gmail.com";
	char* key1copy = (char*)malloc(sizeof(char) * (strlen(key1) + 1));
	strcpy(key1copy, key1);

	char info1[] = "1";
	char* info1copy = (char*)malloc(sizeof(char) * (strlen(info1) + 1));
	strcpy(info1copy, info1);
	bst_insert_node(t, key1copy, info1copy);
	EXPECT_EQ(t->size, 1);

	bst_print(t);
	bst_destructor(t);
}
