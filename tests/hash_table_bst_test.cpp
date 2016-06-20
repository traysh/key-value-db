#include "gtest/gtest.h"
#include "hash_table_bst.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

TEST(HASH_TABLE_BST_TEST, HASH_FUNCTION) {
	hash_table_bst_t* t = hash_table_bst_constructor();
	const char* key1 = "r.cmgleite@gmail.com";
	const char* key2 = "r.cmgleite@gmail.coma";
	const char* key3 = "r.cmgleite@gmail.comb";
	const char* key4 = "aaa";
	const char* key5 = "foobarfoobar";
	const char* key6 = "1234556788";
	const char* key7 = "foo@bar.com.br";
	const char* key8 = "r.cmgleite@gmail.comd";


	uint32_t hash1 = t->hash_function(key1, strlen(key1));
	EXPECT_GT(hash1, 0);

	uint32_t hash2 = t->hash_function(key2, strlen(key2));
	EXPECT_GT(hash2, 0);

	uint32_t hash3 = t->hash_function(key3, strlen(key3));
	EXPECT_GT(hash3, 0);

	uint32_t hash4 = t->hash_function(key4, strlen(key4));
	EXPECT_GT(hash4, 0);

	uint32_t hash5 = t->hash_function(key5, strlen(key5));
	EXPECT_GT(hash5, 0);

	uint32_t hash6 = t->hash_function(key6, strlen(key6));
	EXPECT_GT(hash6, 0);

	uint32_t hash7 = t->hash_function(key7, strlen(key7));
	EXPECT_GT(hash7, 0);

	uint32_t hash8 = t->hash_function(key8, strlen(key8));
	EXPECT_GT(hash8, 0);

	hash_table_bst_destructor(t);
}

TEST(HASH_TABLE_BST_TEST, INSERT_FIND) {
	hash_table_bst_t* t = hash_table_bst_constructor();
	EXPECT_EQ(hash_table_insert_elem(t, "r.cmgleite@gmail.com", "1"), 1);
	EXPECT_EQ(hash_table_insert_elem(t, "r.cmgleite@gmail.coma", "2"), 1);
	EXPECT_EQ(hash_table_insert_elem(t, "r.cmgleite@gmail.comb", "3"), 1);
	EXPECT_EQ(hash_table_insert_elem(t, "r.cmgleite@gmail.comc", "4"), 1);
	EXPECT_EQ(hash_table_insert_elem(t, "r.cmgleite@gmail.comd", "foobar"), 1);
	EXPECT_EQ(hash_table_size(t), 5);

	EXPECT_EQ(strcmp(hash_table_find_elem(t, "r.cmgleite@gmail.com"), "1"), 0);
	EXPECT_EQ(strcmp(hash_table_find_elem(t, "r.cmgleite@gmail.coma"), "2"), 0);
	EXPECT_EQ(strcmp(hash_table_find_elem(t, "r.cmgleite@gmail.comb"), "3"), 0);
	EXPECT_EQ(strcmp(hash_table_find_elem(t, "r.cmgleite@gmail.comc"), "4"), 0);
	EXPECT_EQ(strcmp(hash_table_find_elem(t, "r.cmgleite@gmail.comd"), "foobar"), 0);

	hash_table_bst_destructor(t);
}

TEST(HASH_TABLE_BST_TEST, FIND_ELEMENT_NOT_INSERTED) {
	hash_table_bst_t* t = hash_table_bst_constructor();
	EXPECT_EQ(hash_table_find_elem(t, "foo"), nullptr);

	EXPECT_EQ(hash_table_insert_elem(t, "r.cmgleite@gmail.com", "foobarfoobar"), 1);
	EXPECT_EQ(strcmp(hash_table_find_elem(t, "r.cmgleite@gmail.com"), "foobarfoobar"), 0);

	hash_table_bst_destructor(t);
}

TEST(HASH_TABLE_BST_TEST, UPDATE) {
	hash_table_bst_t* t = hash_table_bst_constructor();

	EXPECT_EQ(hash_table_insert_elem(t, "r.cmgleite@gmail.com", "foobarfoobar"), 1);
	EXPECT_EQ(strcmp(hash_table_find_elem(t, "r.cmgleite@gmail.com"), "foobarfoobar"), 0);

	EXPECT_EQ(hash_table_update_elem(t, "r.cmgleite@gmail.com", "New value!"), 1);
	EXPECT_EQ(strcmp(hash_table_find_elem(t, "r.cmgleite@gmail.com"), "New value!"), 0);

	hash_table_bst_destructor(t);
}

TEST(HASH_TABLE_BST_TEST, UPDATE_ELEMENT_NOT_INSERTED) {
	hash_table_bst_t* t = hash_table_bst_constructor();

	EXPECT_EQ(hash_table_update_elem(t, "r.cmgleite@gmail.com", "New value!"), 0);

	hash_table_bst_destructor(t);
}

TEST(HASH_TABLE_BST_TEST, DELETE) {
	hash_table_bst_t* t = hash_table_bst_constructor();
	EXPECT_EQ(hash_table_insert_elem(t, "r.cmgleite@gmail.com", "1"), 1);
	EXPECT_EQ(hash_table_insert_elem(t, "r.cmgleite@gmail.coma", "2"), 1);
	EXPECT_EQ(hash_table_insert_elem(t, "r.cmgleite@gmail.comb", "3"), 1);
	EXPECT_EQ(hash_table_insert_elem(t, "r.cmgleite@gmail.comc", "4"), 1);
	EXPECT_EQ(hash_table_insert_elem(t, "r.cmgleite@gmail.comd", "foobar"), 1);
	EXPECT_EQ(hash_table_size(t), 5);

	EXPECT_EQ(strcmp(hash_table_find_elem(t, "r.cmgleite@gmail.com"), "1"), 0);
	EXPECT_EQ(strcmp(hash_table_find_elem(t, "r.cmgleite@gmail.coma"), "2"), 0);
	EXPECT_EQ(strcmp(hash_table_find_elem(t, "r.cmgleite@gmail.comb"), "3"), 0);
	EXPECT_EQ(strcmp(hash_table_find_elem(t, "r.cmgleite@gmail.comc"), "4"), 0);
	EXPECT_EQ(strcmp(hash_table_find_elem(t, "r.cmgleite@gmail.comd"), "foobar"), 0);

	hash_table_delete_elem(t, "r.cmgleite@gmail.coma");
	EXPECT_EQ(hash_table_find_elem(t, "r.cmgleite@gmail.coma"), nullptr);

	hash_table_delete_elem(t, "r.cmgleite@gmail.comd");
	EXPECT_EQ(hash_table_find_elem(t, "r.cmgleite@gmail.comd"), nullptr);

	EXPECT_EQ(hash_table_size(t), 3);

	hash_table_bst_destructor(t);
}

/*
 *	This is a test that only makes sense when using valgrind.
 */
TEST(HASH_TABLE_BST_TEST, DELETE_ELEMENT_NOT_INSERTED) {
	hash_table_bst_t* t = hash_table_bst_constructor();

	hash_table_delete_elem(t, "r.cmgleite@gmail.com");
	EXPECT_EQ(hash_table_insert_elem(t, "r.cmgleite@gmail.com", "1"), 1);
	EXPECT_EQ(hash_table_insert_elem(t, "r.cmgleite@gmail.coma", "2"), 1);

	EXPECT_EQ(strcmp(hash_table_find_elem(t, "r.cmgleite@gmail.com"), "1"), 0);
	EXPECT_EQ(strcmp(hash_table_find_elem(t, "r.cmgleite@gmail.coma"), "2"), 0);
	EXPECT_EQ(hash_table_size(t), 2);

	hash_table_delete_elem(t, "foobar");

	EXPECT_EQ(strcmp(hash_table_find_elem(t, "r.cmgleite@gmail.com"), "1"), 0);
	EXPECT_EQ(strcmp(hash_table_find_elem(t, "r.cmgleite@gmail.coma"), "2"), 0);
	EXPECT_EQ(hash_table_size(t), 2);

	hash_table_bst_destructor(t);
}

TEST(HASH_TABLE_BST_TEST, INSERT_ELEM_BIG_KEY) {
	hash_table_bst_t* t = hash_table_bst_constructor();

	char big_key[] = "qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnm";

	EXPECT_EQ(hash_table_insert_elem(t, big_key, "1"), 1);
	EXPECT_EQ(strcmp(hash_table_find_elem(t, big_key), "1"), 0);

	hash_table_bst_destructor(t);
}

TEST(HASH_TABLE_BST_TEST, INSERT_TOO_MANY) {
	hash_table_bst_t* t = hash_table_bst_constructor();
	int loop_size = 10000;

	for(int i = 0; i < loop_size; i++) {
		char str[10];
		sprintf(str, "%d", i);
		hash_table_insert_elem(t, str, str);
	}

	EXPECT_EQ(hash_table_size(t), loop_size);

	// Some finds just to be sure...
	EXPECT_EQ(strcmp(hash_table_find_elem(t, "1"), "1"), 0);
	EXPECT_EQ(strcmp(hash_table_find_elem(t, "44"), "44"), 0);
	EXPECT_EQ(strcmp(hash_table_find_elem(t, "5000"), "5000"), 0);
	EXPECT_EQ(strcmp(hash_table_find_elem(t, "200"), "200"), 0);
	EXPECT_EQ(strcmp(hash_table_find_elem(t, "9876"), "9876"), 0);
	EXPECT_EQ(strcmp(hash_table_find_elem(t, "1234"), "1234"), 0);
	EXPECT_EQ(strcmp(hash_table_find_elem(t, "432"), "432"), 0);
	EXPECT_EQ(strcmp(hash_table_find_elem(t, "7777"), "7777"), 0);
	EXPECT_EQ(hash_table_find_elem(t, "foo"), nullptr);


	hash_table_bst_destructor(t);
}
