#include "gtest/gtest.h"

#include "list.h"

void data_destructor(void*) {
	//Nothing to be done
}

void print_data(const void* d) {
	printf("%ld", *((const long*)d));
}

TEST(LIST, CONSTRUCTION) {
	list_t* l = list_constructor(data_destructor, print_data);
	EXPECT_EQ(l->size, 0);
	ASSERT_TRUE(l->first == NULL);
	ASSERT_TRUE(l->last == NULL);
	list_destructor(l);
}

TEST(LIST, INSERT_POP) {
	list_t* l = list_constructor(data_destructor, print_data);
	
	// INSERTIONS
	list_push_back(l, (void*)0);
	EXPECT_EQ(l->size, 1);
	ASSERT_TRUE(l->first == l->last);
	
	list_push_back(l, (void*)1);
	EXPECT_EQ(l->size, 2);
	EXPECT_EQ((long)list_peek_front(l), 0);
	EXPECT_EQ((long)list_peek_back(l), 1);
	
	list_push_back(l, (void*)2);
	EXPECT_EQ(l->size, 3);
	EXPECT_EQ((long)list_peek_front(l), 0);
	EXPECT_EQ((long)list_peek_back(l), 2);
	
	list_push_back(l, (void*)3);
	EXPECT_EQ(l->size, 4);
	EXPECT_EQ((long)list_peek_front(l), 0);
	EXPECT_EQ((long)list_peek_back(l), 3);
	
	list_push_front(l, (void*)-1);
	EXPECT_EQ(l->size, 5);
	EXPECT_EQ((long)list_peek_front(l), -1);
	EXPECT_EQ((long)list_peek_back(l), 3);
	
	list_push_front(l, (void*)-2);
	EXPECT_EQ(l->size, 6);
	EXPECT_EQ((long)list_peek_front(l), -2);
	EXPECT_EQ((long)list_peek_back(l), 3);
	
	list_push_front(l, (void*)-3);
	EXPECT_EQ(l->size, 7);
	EXPECT_EQ((long)list_peek_front(l), -3);
	EXPECT_EQ((long)list_peek_back(l), 3);
	
	// POPs
	void* data;
	data = list_pop_front(l);
	EXPECT_EQ(l->size, 6);
	EXPECT_EQ((long)data, -3);
	
	data = list_pop_back(l);
	EXPECT_EQ(l->size, 5);
	EXPECT_EQ((long)data, 3);
	
	data = list_pop_front(l);
	EXPECT_EQ(l->size, 4);
	EXPECT_EQ((long)data, -2);
	
	data = list_pop_back(l);
	EXPECT_EQ(l->size, 3);
	EXPECT_EQ((long)data, 2);
	
	data = list_pop_front(l);
	EXPECT_EQ(l->size, 2);
	EXPECT_EQ((long)data, -1);
	EXPECT_EQ((long)list_peek_front(l), 0);
	EXPECT_EQ((long)list_peek_back(l), 1);
	ASSERT_FALSE(l->first == l->last);
	
	data = list_pop_back(l);
	EXPECT_EQ(l->size, 1);
	EXPECT_EQ((long)data, 1);
	EXPECT_EQ((long)list_peek_front(l), 0);
	EXPECT_EQ((long)list_peek_back(l), 0);
	ASSERT_TRUE(l->first == l->last);
	
	data = list_pop_back(l);
	EXPECT_EQ(l->size, 0);
	EXPECT_EQ((long)data, 0);
	
	list_destructor(l);
}

TEST(LIST, POP_EMPTY_LIST) {
	list_t* l = list_constructor(data_destructor, print_data);
	
	ASSERT_TRUE(list_pop_back(l) == NULL);
	EXPECT_EQ(l->size, 0);
	ASSERT_TRUE(list_pop_front(l) == NULL);
	EXPECT_EQ(l->size, 0);
	
	list_destructor(l);
}