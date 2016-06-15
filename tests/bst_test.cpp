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

	bst_destructor(t);
}

TEST(BST_TEST, DELETE_NODE) {
	bst_t* t = bst_constructor(bst_compare, bst_key_destructor, bst_info_destructor, bst_print_key, bst_print_info);
	EXPECT_EQ(t->size, 0);
	
	// PAIR 0
	long key = 6;
	char info[] = "def";
	char* infocopy = (char*)malloc(sizeof(char) * (strlen(info) + 1));
	strcpy(infocopy, info);
	bst_insert_node(t, &key, infocopy);
	EXPECT_EQ(t->size, 1);

	// PAIR 1
	long key1 = 4;
	char info1[] = "abcd";
	char* info1copy = (char*)malloc(sizeof(char) * (strlen(info1) + 1));
	strcpy(info1copy, info1);
	bst_insert_node(t, &key1, info1copy);
	EXPECT_EQ(t->size, 2);

	// PAIR 2
	long key2 = 20;
	char info2[] = "foobar";
	char* info2copy = (char*)malloc(sizeof(char) * (strlen(info2) + 1));
	strcpy(info2copy, info2);
	bst_insert_node(t, &key2, info2copy);
	EXPECT_EQ(t->size, 3);

	// PAIR 3
	long key3 = 10;
	char info3[] = "3";
	char* info3copy = (char*)malloc(sizeof(char) * (strlen(info3) + 1));
	strcpy(info3copy, info3);
	bst_insert_node(t, &key3, info3copy);
	EXPECT_EQ(t->size, 4);

	// PAIR 4
	long key4 = 9;
	char info4[] = "4";
	char* info4copy = (char*)malloc(sizeof(char) * (strlen(info4) + 1));
	strcpy(info4copy, info4);
	bst_insert_node(t, &key4, info4copy);
	EXPECT_EQ(t->size, 5);

	// PAIR 5
	long key5 = 11;
	char info5[] = "5";
	char* info5copy = (char*)malloc(sizeof(char) * (strlen(info5) + 1));
	strcpy(info5copy, info5);
	bst_insert_node(t, &key5, info5copy);
	EXPECT_EQ(t->size, 6);

	// PAIR 6
	long key6 = 12;
	char info6[] = "5";
	char* info6copy = (char*)malloc(sizeof(char) * (strlen(info6) + 1));
	strcpy(info6copy, info6);
	bst_insert_node(t, &key6, info6copy);
	EXPECT_EQ(t->size, 7);

	// PAIR 7
	long key7 = 30;
	char info7[] = "5";
	char* info7copy = (char*)malloc(sizeof(char) * (strlen(info7) + 1));
	strcpy(info7copy, info7);
	bst_insert_node(t, &key7, info7copy);
	EXPECT_EQ(t->size, 8);
	
	// PAIR 8
	long key8 = 22;
	char info8[] = "5";
	char* info8copy = (char*)malloc(sizeof(char) * (strlen(info8) + 1));
	strcpy(info8copy, info8);
	bst_insert_node(t, &key8, info8copy);
	EXPECT_EQ(t->size, 9);

	// PAIR 9
	long key9 = 36;
	char info9[] = "5";
	char* info9copy = (char*)malloc(sizeof(char) * (strlen(info9) + 1));
	strcpy(info9copy, info9);
	bst_insert_node(t, &key9, info9copy);
	EXPECT_EQ(t->size, 10);

	// PAIR 10
	long key10 = 40;
	char info10[] = "5";
	char* info10copy = (char*)malloc(sizeof(char) * (strlen(info10) + 1));
	strcpy(info10copy, info10);
	bst_insert_node(t, &key10, info10copy);
	EXPECT_EQ(t->size, 11);

	// PAIR 11
	long key11 = 26;
	char info11[] = "5";
	char* info11copy = (char*)malloc(sizeof(char) * (strlen(info11) + 1));
	strcpy(info11copy, info11);
	bst_insert_node(t, &key11, info11copy);
	EXPECT_EQ(t->size, 12);

	// PAIR 12
	long key12 = 28;
	char info12[] = "5";
	char* info12copy = (char*)malloc(sizeof(char) * (strlen(info12) + 1));
	strcpy(info12copy, info12);
	bst_insert_node(t, &key12, info12copy);
	EXPECT_EQ(t->size, 13);


	// Delete node with 2 children
	bst_delete_node(t, &key2); //(node with key = 20)
	bst_node_t* found = bst_find_node(t, &key2);
	EXPECT_EQ(found, nullptr);
	EXPECT_EQ(t->size, 12);

	// Delete node with 1 child
	bst_delete_node(t, &key11);
	bst_node_t* found1 = bst_find_node(t, &key11);
	EXPECT_EQ(found1, nullptr);
	EXPECT_EQ(t->size, 11);
	
	// Delete node without child
	bst_delete_node(t, &key12);
	bst_node_t* found2 = bst_find_node(t, &key12);
	EXPECT_EQ(found2, nullptr);
	EXPECT_EQ(t->size, 10);

	bst_destructor(t);
}

TEST(BST_TEST, UPDATE_NODE) {
	bst_t* t = bst_constructor(bst_compare, bst_key_destructor, bst_info_destructor, bst_print_key, bst_print_info);
	EXPECT_EQ(t->size, 0);
	
	// PAIR 0
	long key = 6;
	char info[] = "def";
	char* infocopy = (char*)malloc(sizeof(char) * (strlen(info) + 1));
	strcpy(infocopy, info);
	bst_insert_node(t, &key, infocopy);
	EXPECT_EQ(t->size, 1);

	// PAIR 1
	long key1 = 4;
	char info1[] = "abcd";
	char* info1copy = (char*)malloc(sizeof(char) * (strlen(info1) + 1));
	strcpy(info1copy, info1);
	bst_insert_node(t, &key1, info1copy);
	EXPECT_EQ(t->size, 2);

	// PAIR 2
	long key2 = 20;
	char info2[] = "foobar";
	char* info2copy = (char*)malloc(sizeof(char) * (strlen(info2) + 1));
	strcpy(info2copy, info2);
	bst_insert_node(t, &key2, info2copy);
	EXPECT_EQ(t->size, 3);

	// PAIR 3
	long key3 = 10;
	char info3[] = "3";
	char* info3copy = (char*)malloc(sizeof(char) * (strlen(info3) + 1));
	strcpy(info3copy, info3);
	bst_insert_node(t, &key3, info3copy);
	EXPECT_EQ(t->size, 4);

	char new_info[] = "new info here";
	char* new_info_copy = (char*)malloc(sizeof(char) * (strlen(new_info) + 1));
	strcpy(new_info_copy, new_info);
	bst_node_t* updated1 = bst_update_node_info(t, &key3, new_info_copy);
	EXPECT_EQ(0, strcmp((char*)updated1->info, new_info));
	
	bst_destructor(t);
}
