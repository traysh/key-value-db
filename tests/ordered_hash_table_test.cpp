#include "gtest/gtest.h"
#include "ordered_hash_table.h"
#include "arbitrary_values.h"
#include "arbitrary_values_sorted.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

TEST(ORDERED_HASH_TABLE_TEST, INSERT_FIND) {
	ordered_hash_table_t* t = ordered_hash_table_constructor();
	EXPECT_EQ(ordered_hash_table_insert_elem(&t, "r.cmgleite@gmail.com", 1), 1);
	EXPECT_EQ(ordered_hash_table_insert_elem(&t, "r.cmgleite@gmail.coma", 2), 1);
	EXPECT_EQ(ordered_hash_table_insert_elem(&t, "r.cmgleite@gmail.comb", 3), 1);
	EXPECT_EQ(ordered_hash_table_insert_elem(&t, "r.cmgleite@gmail.comc", 4), 1);
	EXPECT_EQ(ordered_hash_table_insert_elem(&t, "r.cmgleite@gmail.comd", 5), 1);
	EXPECT_EQ(ordered_hash_table_size(t), 5);

	EXPECT_EQ(ordered_hash_table_find_elem(t, "r.cmgleite@gmail.com")->value, 1);
	EXPECT_EQ(ordered_hash_table_find_elem(t, "r.cmgleite@gmail.coma")->value, 2);
	EXPECT_EQ(ordered_hash_table_find_elem(t, "r.cmgleite@gmail.comb")->value, 3);
	EXPECT_EQ(ordered_hash_table_find_elem(t, "r.cmgleite@gmail.comc")->value, 4);
	EXPECT_EQ(ordered_hash_table_find_elem(t, "r.cmgleite@gmail.comd")->value, 5);

	ordered_hash_table_destructor(t);
}

TEST(ORDERED_HASH_TABLE_TEST, INSERT_DUPLICATED) {
	ordered_hash_table_t* t = ordered_hash_table_constructor();
	// Tests inserting elements with same keys
	EXPECT_EQ(ordered_hash_table_insert_elem(&t, "danilo.luvizotto@gmail.com", 1), 1);
	EXPECT_EQ(ordered_hash_table_insert_elem(&t, "danilo.luvizotto@gmail.com", 1), 0);
	EXPECT_EQ(ordered_hash_table_insert_elem(&t, "danilo.luvizotto@gmail.com", 2), 0);
	
	// Tests inserting elements with same values
	EXPECT_EQ(ordered_hash_table_insert_elem(&t, "danilo.luvizotto@gmail.coma", 2), 1);
	EXPECT_EQ(ordered_hash_table_insert_elem(&t, "danilo.luvizotto@gmail.comb", 2), 1);
	EXPECT_EQ(ordered_hash_table_insert_elem(&t, "danilo.luvizotto@gmail.comc", 2), 1);
	EXPECT_EQ(ordered_hash_table_insert_elem(&t, "danilo.luvizotto@gmail.comd", 2), 1);
	
	ordered_hash_table_destructor(t);
}

TEST(ORDERED_HASH_TABLE_TEST, FIND_ELEMENT_NOT_INSERTED) {
	ordered_hash_table_t* t = ordered_hash_table_constructor();
	EXPECT_EQ(ordered_hash_table_find_elem(t, "foo"), nullptr);

	EXPECT_EQ(ordered_hash_table_insert_elem(&t, "r.cmgleite@gmail.com", 55), 1);
	EXPECT_EQ(ordered_hash_table_find_elem(t, "r.cmgleite@gmail.com")->value, 55);

	ordered_hash_table_destructor(t);
}

TEST(ORDERED_HASH_TABLE_TEST, UPDATE) {
	ordered_hash_table_t* t = ordered_hash_table_constructor();

	EXPECT_EQ(ordered_hash_table_insert_elem(&t, "r.cmgleite@gmail.com", 55), 1);
	EXPECT_EQ(ordered_hash_table_find_elem(t, "r.cmgleite@gmail.com")->value, 55);

	EXPECT_EQ(ordered_hash_table_update_elem(t, "r.cmgleite@gmail.com", 33), 1);
	EXPECT_EQ(ordered_hash_table_find_elem(t, "r.cmgleite@gmail.com")->value, 33);

	ordered_hash_table_destructor(t);
}

TEST(ORDERED_HASH_TABLE_TEST, UPDATE_ELEMENT_NOT_INSERTED) {
	ordered_hash_table_t* t = ordered_hash_table_constructor();

	EXPECT_EQ(ordered_hash_table_update_elem(t, "r.cmgleite@gmail.com", 33), 0);

	ordered_hash_table_destructor(t);
}

TEST(ORDERED_HASH_TABLE_TEST, DELETE) {
	ordered_hash_table_t* t = ordered_hash_table_constructor();
	EXPECT_EQ(ordered_hash_table_insert_elem(&t, "r.cmgleite@gmail.com", 1), 1);
	EXPECT_EQ(ordered_hash_table_insert_elem(&t, "r.cmgleite@gmail.coma", 2), 1);
	EXPECT_EQ(ordered_hash_table_insert_elem(&t, "r.cmgleite@gmail.comb", 3), 1);
	EXPECT_EQ(ordered_hash_table_insert_elem(&t, "r.cmgleite@gmail.comc", 4), 1);
	EXPECT_EQ(ordered_hash_table_insert_elem(&t, "r.cmgleite@gmail.comd", 5), 1);
	EXPECT_EQ(ordered_hash_table_size(t), 5);

	EXPECT_EQ(ordered_hash_table_find_elem(t, "r.cmgleite@gmail.com")->value, 1);
	EXPECT_EQ(ordered_hash_table_find_elem(t, "r.cmgleite@gmail.coma")->value, 2);
	EXPECT_EQ(ordered_hash_table_find_elem(t, "r.cmgleite@gmail.comb")->value, 3);
	EXPECT_EQ(ordered_hash_table_find_elem(t, "r.cmgleite@gmail.comc")->value, 4);
	EXPECT_EQ(ordered_hash_table_find_elem(t, "r.cmgleite@gmail.comd")->value, 5);

	ordered_hash_table_delete_elem(t, "r.cmgleite@gmail.coma");
	EXPECT_EQ(ordered_hash_table_find_elem(t, "r.cmgleite@gmail.coma"), nullptr);

	ordered_hash_table_delete_elem(t, "r.cmgleite@gmail.comd");
	EXPECT_EQ(ordered_hash_table_find_elem(t, "r.cmgleite@gmail.comd"), nullptr);

	EXPECT_EQ(ordered_hash_table_size(t), 3);

	ordered_hash_table_destructor(t);
}

///*
// *	This is a test that only makes sense when using valgrind.
// */
TEST(ORDERED_HASH_TABLE_TEST, DELETE_ELEMENT_NOT_INSERTED) {
	ordered_hash_table_t* t = ordered_hash_table_constructor();

	ordered_hash_table_delete_elem(t, "r.cmgleite@gmail.com");
	EXPECT_EQ(ordered_hash_table_insert_elem(&t, "r.cmgleite@gmail.com", 1), 1);
	EXPECT_EQ(ordered_hash_table_insert_elem(&t, "r.cmgleite@gmail.coma", 2), 1);

	EXPECT_EQ(ordered_hash_table_find_elem(t, "r.cmgleite@gmail.com")->value, 1);
	EXPECT_EQ(ordered_hash_table_find_elem(t, "r.cmgleite@gmail.coma")->value, 2);
	EXPECT_EQ(ordered_hash_table_size(t), 2);

	ordered_hash_table_delete_elem(t, "foobar");

	EXPECT_EQ(ordered_hash_table_find_elem(t, "r.cmgleite@gmail.com")->value, 1);
	EXPECT_EQ(ordered_hash_table_find_elem(t, "r.cmgleite@gmail.coma")->value, 2);
	EXPECT_EQ(ordered_hash_table_size(t), 2);

	ordered_hash_table_destructor(t);
}

TEST(ORDERED_HASH_TABLE_TEST, INSERT_ELEM_BIG_KEY) {
	ordered_hash_table_t* t = ordered_hash_table_constructor();

	char big_key[] = "qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnm";

	EXPECT_EQ(ordered_hash_table_insert_elem(&t, big_key, 1), 1);
	EXPECT_EQ(ordered_hash_table_find_elem(t, big_key)->value, 1);

	ordered_hash_table_destructor(t);
}

TEST(ORDERED_HASH_TABLE_TEST, INSERT_TOO_MANY) {
	ordered_hash_table_t* t = ordered_hash_table_constructor();
	int loop_size = 10000;

	for(int i = 0; i < loop_size; i++) {
		char str[10];
		sprintf(str, "%d", i);
		ordered_hash_table_insert_elem(&t, str, i);
	}

	EXPECT_EQ(ordered_hash_table_size(t), loop_size);

	// Some finds just to be sure...
	EXPECT_EQ(ordered_hash_table_find_elem(t, "1")->value, 1);
	EXPECT_EQ(ordered_hash_table_find_elem(t, "44")->value, 44);
	EXPECT_EQ(ordered_hash_table_find_elem(t, "5000")->value, 5000);
	EXPECT_EQ(ordered_hash_table_find_elem(t, "200")->value, 200);
	EXPECT_EQ(ordered_hash_table_find_elem(t, "9876")->value, 9876);
	EXPECT_EQ(ordered_hash_table_find_elem(t, "1234")->value, 1234);
	EXPECT_EQ(ordered_hash_table_find_elem(t, "432")->value, 432);
	EXPECT_EQ(ordered_hash_table_find_elem(t, "7777")->value, 7777);
	EXPECT_EQ(ordered_hash_table_find_elem(t, "foo"), nullptr);
	

	ordered_hash_table_destructor(t);
}

TEST(ORDERED_HASH_TABLE_TEST, GET_ORDERED_VALUES_EMPTY_BASE) {
	ordered_hash_table_t* t = ordered_hash_table_constructor();
	
	ordered_hash_table_entry_list_t* current = ordered_hash_table_get_top_n_values(t, 100);
	ASSERT_TRUE(current == NULL);
}

TEST(ORDERED_HASH_TABLE_TEST, GET_ORDERED_VALUES_SINGLE_ELEMENT_BASE) {
	ordered_hash_table_t* t = ordered_hash_table_constructor();
	
	ordered_hash_table_insert_elem(&t, "1", 1);
	ordered_hash_table_entry_list_t* current = ordered_hash_table_get_top_n_values(t, 1);
	
	ASSERT_FALSE(current == NULL);
	EXPECT_EQ(current->entry->value, 1);
}

TEST(ORDERED_HASH_TABLE_TEST, GET_ORDERED_VALUES_NEGATIVE_N) {
	ordered_hash_table_t* t = ordered_hash_table_constructor();
	
	ordered_hash_table_entry_list_t* current = ordered_hash_table_get_top_n_values(t, -100);
	ASSERT_TRUE(current == NULL);
}

TEST(ORDERED_HASH_TABLE_TEST, GET_ORDERED_VALUES_MORE_THAN_AVAILABLE) {
	ordered_hash_table_t* t = ordered_hash_table_constructor();
	
	int values[] = { 4, 15, -6, -19, 33, 0, 2, 8, -12, 22 };
	int values_sorted[] = { 33, 22, 15, 8, 4, 2, 0, -6, -12, -19 };
	
	size_t i;
	for (i = 0; i < 10; ++i) {
		char str[10];
		sprintf(str, "%lu", i);
		ordered_hash_table_insert_elem(&t, str, values[i]);
	}
	ordered_hash_table_entry_list_t* current = ordered_hash_table_get_top_n_values(t, 20);
	for (int i = 0; i < 10; ++i) {
		ASSERT_FALSE(current == NULL);
		EXPECT_EQ(current->entry->value, values_sorted[i]);
		current = current->next;
	}
	ASSERT_TRUE(current == NULL);
}
TEST(ORDERED_HASH_TABLE_TEST, GET_ORDERED_VALUES_A_MILLION_RANDOM_ELEMENTS_BASE) {
	ordered_hash_table_t* t = ordered_hash_table_constructor();
	
	size_t i;
	for (i = 0; i < sizeof(arbitrary_values)/sizeof(int); ++i) {
		char str[10];
		sprintf(str, "%lu", i);
		ordered_hash_table_insert_elem(&t, str, arbitrary_values[i]);
	}
	
	ordered_hash_table_entry_list_t* current = ordered_hash_table_get_top_n_values(t, 100);
	for (int i = 0; i < 100; ++i) {
		ASSERT_FALSE(current == NULL);
		EXPECT_EQ(current->entry->value, arbitrary_values_sorted[i]);
		current = current->next;
	}
}