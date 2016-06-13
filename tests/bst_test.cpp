#include "gtest/gtest.h"
#include "binary_search_tree.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int bst_compare(const void* lhs, const void* rhs) {
	int ilhs = *(int*)lhs;
	int irhs = *(int*)rhs;

	if(ilhs > irhs)
		return 1;
	else if(ilhs == irhs)
		return 0;
	else
		return -1;
}

void bst_key_destructor(void* key) {
	//Nothing to be done
}

void bst_info_destructor(void* info) {
	free(info);
}

void bst_print_key(const void* key) {
	fprintf(stdout, "%ld", *((const long*)key));
}

void bst_print_info(const void* info) {
	fprintf(stdout, "%s", (char*)info);
}

TEST(BST_TEST, SIMPLE_INSERTION) {
	bst_t* t = bst_constructor(bst_compare, bst_key_destructor, bst_info_destructor, bst_print_key, bst_print_info);
	EXPECT_EQ(t->size, 0);

	// PAIR 1
	long key1 = 7;
	char info1[] = "1";
	char* info1copy = (char*)malloc(sizeof(char) * (strlen(info1) + 1));
	strcpy(info1copy, info1);
	bst_insert_node(t, &key1, info1copy);
	EXPECT_EQ(t->size, 1);

	// PAIR 2
	long key2 = 4;
	char info2[] = "2";
	char* info2copy = (char*)malloc(sizeof(char) * (strlen(info2) + 1));
	strcpy(info2copy, info2);
	bst_insert_node(t, &key2, info2copy);
	EXPECT_EQ(t->size, 2);

	// PAIR 3
	long key3 = 2;
	char info3[] = "3";
	char* info3copy = (char*)malloc(sizeof(char) * (strlen(info3) + 1));
	strcpy(info3copy, info3);
	bst_insert_node(t, &key3, info3copy);
	EXPECT_EQ(t->size, 3);

	// PAIR 4
	long key4 = 8;
	char info4[] = "4";
	char* info4copy = (char*)malloc(sizeof(char) * (strlen(info4) + 1));
	strcpy(info4copy, info4);
	bst_insert_node(t, &key4, info4copy);
	EXPECT_EQ(t->size, 4);

	// PAIR 5
	long key5 = 10;
	char info5[] = "5";
	char* info5copy = (char*)malloc(sizeof(char) * (strlen(info5) + 1));
	strcpy(info5copy, info5);
	bst_insert_node(t, &key5, info5copy);
	EXPECT_EQ(t->size, 5);

	// PAIR 6
	long key6 = 3;
	char info6[] = "5";
	char* info6copy = (char*)malloc(sizeof(char) * (strlen(info6) + 1));
	strcpy(info6copy, info6);
	bst_insert_node(t, &key6, info6copy);
	EXPECT_EQ(t->size, 6);

	bst_print(t);
	bst_destructor(t);
}

TEST(BST_TEST, INSERT_DUPLICATE_NODE) {
	bst_t* t = bst_constructor(bst_compare, bst_key_destructor, bst_info_destructor, bst_print_key, bst_print_info);
	EXPECT_EQ(t->size, 0);

	// PAIR 1
	long key1 = 7;
	char info1[] = "1";
	char* info1copy = (char*)malloc(sizeof(char) * (strlen(info1) + 1));
	strcpy(info1copy, info1);
	bst_insert_node(t, &key1, info1copy);
	EXPECT_EQ(t->size, 1);

	// PAIR 2
	long key2 = 7;
	char info2[] = "2";
	char* info2copy = (char*)malloc(sizeof(char) * (strlen(info2) + 1));
	strcpy(info2copy, info2);
	EXPECT_EQ(bst_insert_node(t, &key2, info2copy), nullptr);
	EXPECT_EQ(t->size, 1);

	bst_print(t);
	bst_destructor(t);
	free(info2copy);
}

TEST(BST_TEST, FIND_NODE) {
	bst_t* t = bst_constructor(bst_compare, bst_key_destructor, bst_info_destructor, bst_print_key, bst_print_info);
	EXPECT_EQ(t->size, 0);

	long key = 44;
	bst_node_t* n = bst_find_node(t, &key);
	EXPECT_EQ(n, nullptr);

	// PAIR 1
	long key1 = 11;
	char info1[] = "1";
	char* info1copy = (char*)malloc(sizeof(char) * (strlen(info1) + 1));
	strcpy(info1copy, info1);
	bst_insert_node(t, &key1, info1copy);
	EXPECT_EQ(t->size, 1);

	// PAIR 2
	long key2 = 12;
	char info2[] = "2";
	char* info2copy = (char*)malloc(sizeof(char) * (strlen(info2) + 1));
	strcpy(info2copy, info2);
	bst_insert_node(t, &key2, info2copy);
	EXPECT_EQ(t->size, 2);

	// PAIR 3
	long key3 = 1;
	char info3[] = "3";
	char* info3copy = (char*)malloc(sizeof(char) * (strlen(info3) + 1));
	strcpy(info3copy, info3);
	bst_insert_node(t, &key3, info3copy);
	EXPECT_EQ(t->size, 3);

	// PAIR 4
	long key4 = 2;
	char info4[] = "4";
	char* info4copy = (char*)malloc(sizeof(char) * (strlen(info4) + 1));
	strcpy(info4copy, info4);
	bst_insert_node(t, &key4, info4copy);
	EXPECT_EQ(t->size, 4);

	// PAIR 5
	long key5 = 99;
	char info5[] = "5";
	char* info5copy = (char*)malloc(sizeof(char) * (strlen(info5) + 1));
	strcpy(info5copy, info5);
	bst_insert_node(t, &key5, info5copy);
	EXPECT_EQ(t->size, 5);

	// PAIR 6
	long key6 = 0;
	char info6[] = "5";
	char* info6copy = (char*)malloc(sizeof(char) * (strlen(info6) + 1));
	strcpy(info6copy, info6);
	bst_insert_node(t, &key6, info6copy);
	EXPECT_EQ(t->size, 6);

	bst_node_t* found = bst_find_node(t, &key5);
	EXPECT_EQ((long*)found->key, &key5);

	long not_found_key = 44;
	bst_node_t* not_found = bst_find_node(t, &not_found_key);
	EXPECT_EQ(not_found, nullptr);

	bst_print(t);
	bst_destructor(t);
}
