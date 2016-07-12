#include "gtest/gtest.h"

#include "max_heap.h"
#include "list.h"

int long_compare(const void* lhs, const void* rhs) {
	long ilhs = (long)lhs;
	long irhs = (long)rhs;

	if(ilhs > irhs)
		return 1;
	else if(ilhs == irhs)
		return 0;
	else
		return -1;
}

void key_destructor(void*) {
	//Nothing to be done
}

void info_destructor(void*) {
	//Nothing to be done
}

void print_key(const void* key) {
	printf("%ld ", (const long)key);
}

void print_info(const void* info) {
	printf("%s", (char*)info);
}

TEST(MAX_HEAP, INSERT_3) {
	heap_t* h = heap_contructor(3, long_compare,
								key_destructor,
								info_destructor,
								print_key,
								print_info);
	
	EXPECT_EQ(h->size, 0);
	EXPECT_EQ(h->max_size, 3);
	
	// Level 0
	heap_insert_node(h, (void*)10, (void*)"17");
	
	// Level 1
	heap_insert_node(h, (void*)15, (void*)"10");
	heap_insert_node(h, (void*)20, (void*)"15");
	
	
	// Level 0
	EXPECT_EQ((long)h->data[0].key, 20);
	
	// Level 1
	EXPECT_EQ((long)h->data[1].key, 10);
	EXPECT_EQ((long)h->data[2].key, 15);
	
	heap_destructor(h);
}

TEST(MAX_HEAP, INSERT_6) {
	heap_t* h = heap_contructor(7, long_compare,
								key_destructor,
								info_destructor,
								print_key,
								print_info);
	
	EXPECT_EQ(h->size, 0);
	EXPECT_EQ(h->max_size, 7);
	
	// Level 0
	heap_insert_node(h, (void*)10, (void*)"");
	
	// Level 1
	heap_insert_node(h, (void*)15, (void*)"");
	heap_insert_node(h, (void*)20, (void*)"");
	
	// Level 2
	heap_insert_node(h, (void*)1, (void*)"");
	heap_insert_node(h, (void*)30, (void*)"");
	heap_insert_node(h, (void*)14, (void*)"");
	
	// Level 0
	EXPECT_EQ((long)h->data[0].key, 30);
	
	// Level 1
	EXPECT_EQ((long)h->data[1].key, 20);
	EXPECT_EQ((long)h->data[2].key, 15);
	
	// Level 1
	EXPECT_EQ((long)h->data[3].key, 1);
	EXPECT_EQ((long)h->data[4].key, 10);
	EXPECT_EQ((long)h->data[5].key, 14);
	
	heap_destructor(h);
}

TEST(MAX_HEAP, INSERT_7) {
	heap_t* h = heap_contructor(7, long_compare,
								key_destructor,
								info_destructor,
								print_key,
								print_info);
	
	EXPECT_EQ(h->size, 0);
	EXPECT_EQ(h->max_size, 7);
	
	// Level 0
	heap_insert_node(h, (void*)20, (void*)"");
	
	// Level 1
	heap_insert_node(h, (void*)17, (void*)"");
	heap_insert_node(h, (void*)15, (void*)"");
	
	// Level 2
	heap_insert_node(h, (void*)10, (void*)"");
	heap_insert_node(h, (void*)14, (void*)"");
	heap_insert_node(h, (void*)1, (void*)"");
	heap_insert_node(h, (void*)30, (void*)"");
	
	
	
	// Level 0
	EXPECT_EQ((long)h->data[0].key, 30);
	
	// Level 1
	EXPECT_EQ((long)h->data[1].key, 17);
	EXPECT_EQ((long)h->data[2].key, 20);
	
	// Level 1
	EXPECT_EQ((long)h->data[3].key, 10);
	EXPECT_EQ((long)h->data[4].key, 14);
	EXPECT_EQ((long)h->data[5].key, 1);
	EXPECT_EQ((long)h->data[6].key, 15);
	
	heap_destructor(h);
}

TEST(MAX_HEAP, INSERT_IN_ORDER) {
	heap_t* h = heap_contructor(15, long_compare,
								key_destructor,
								info_destructor,
								print_key,
								print_info);
	
	EXPECT_EQ(h->size, 0);
	EXPECT_EQ(h->max_size, 15);
	
	// Level 0
	heap_insert_node(h, (void*)20, (void*)"20");
	EXPECT_EQ(h->size, 1);
	
	// Level 1
	heap_insert_node(h, (void*)17, (void*)"17");
	heap_insert_node(h, (void*)10, (void*)"10");
	EXPECT_EQ(h->size, 3);
	
	// Level 2
	heap_insert_node(h, (void*)15, (void*)"15");
	heap_insert_node(h, (void*)8, (void*)"8");
	heap_insert_node(h, (void*)4, (void*)"4");
	heap_insert_node(h, (void*)9, (void*)"9");
	EXPECT_EQ(h->size, 7);
	
	// Level 3
	heap_insert_node(h, (void*)7, (void*)"7");
	heap_insert_node(h, (void*)14, (void*)"14");
	heap_insert_node(h, (void*)3, (void*)"3");
	heap_insert_node(h, (void*)5, (void*)"5");
	heap_insert_node(h, (void*)2, (void*)"2");
	heap_insert_node(h, (void*)0, (void*)"0");
	heap_insert_node(h, (void*)6, (void*)"6");
	heap_insert_node(h, (void*)1, (void*)"1");
	EXPECT_EQ(h->size, 15);
	
	// Level 0
	EXPECT_EQ((long)h->data[0].key, 20);
	
	// Level 1
	EXPECT_EQ((long)h->data[1].key, 17);
	EXPECT_EQ((long)h->data[2].key, 10);
	
	// Level 2
	EXPECT_EQ((long)h->data[3].key, 15);
	EXPECT_EQ((long)h->data[4].key, 8);
	EXPECT_EQ((long)h->data[5].key, 4);
	EXPECT_EQ((long)h->data[6].key, 9);
	
	// Level 3
	EXPECT_EQ((long)h->data[7].key, 7);
	EXPECT_EQ((long)h->data[8].key, 14);
	EXPECT_EQ((long)h->data[9].key, 3);
	EXPECT_EQ((long)h->data[10].key, 5);
	EXPECT_EQ((long)h->data[11].key, 2);
	EXPECT_EQ((long)h->data[12].key, 0);
	EXPECT_EQ((long)h->data[13].key, 6);
	EXPECT_EQ((long)h->data[14].key, 1);
	
	heap_destructor(h);
}

TEST(MAX_HEAP, INSERT_BIGGEST_LAST) {
	h = heap_contructor(15, long_compare,
								key_destructor,
								info_destructor,
								print_key,
								print_info);
	
	
	EXPECT_EQ(h->size, 0);
	EXPECT_EQ(h->max_size, 15);
	
	// Level 0
	heap_insert_node(h, (void*)17, (void*)"17");
	EXPECT_EQ(h->size, 1);
	
	// Level 1
	heap_insert_node(h, (void*)10, (void*)"10");
	heap_insert_node(h, (void*)15, (void*)"15");
	EXPECT_EQ(h->size, 3);
	
	// Level 2
	heap_insert_node(h, (void*)8, (void*)"8");
	heap_insert_node(h, (void*)4, (void*)"4");
	heap_insert_node(h, (void*)9, (void*)"9");
	heap_insert_node(h, (void*)7, (void*)"7");
	EXPECT_EQ(h->size, 7);
	
	// Level 3
	heap_insert_node(h, (void*)14, (void*)"14");
	heap_insert_node(h, (void*)3, (void*)"3");
	heap_insert_node(h, (void*)5, (void*)"5");
	heap_insert_node(h, (void*)2, (void*)"2");
	heap_insert_node(h, (void*)0, (void*)"0");
	heap_insert_node(h, (void*)6, (void*)"6");
	heap_insert_node(h, (void*)1, (void*)"1");
	heap_insert_node(h, (void*)20, (void*)"20");
	EXPECT_EQ(h->size, 15);
	
	// Level 0
	EXPECT_EQ((long)h->data[0].key, 20);
	
	// Level 1
	EXPECT_EQ((long)h->data[1].key, 14);
	EXPECT_EQ((long)h->data[2].key, 17);
	
	// Level 2
	EXPECT_EQ((long)h->data[3].key, 10);
	EXPECT_EQ((long)h->data[4].key, 5);
	EXPECT_EQ((long)h->data[5].key, 9);
	EXPECT_EQ((long)h->data[6].key, 15);
	
	// Level 3
	EXPECT_EQ((long)h->data[7].key, 8);
	EXPECT_EQ((long)h->data[8].key, 3);
	EXPECT_EQ((long)h->data[9].key, 4);
	
	heap_destructor(h);
}

TEST(MAX_HEAP, INSERT_A_MILLION) {
	heap_t* h = heap_contructor(10, long_compare,
								key_destructor,
								info_destructor,
								print_key,
								print_info);
	
	
	EXPECT_EQ(h->size, 0);
	EXPECT_EQ(h->max_size, HEAP_INITIAL_SIZE);
	
	for (size_t i = HEAP_INITIAL_SIZE*HEAP_INITIAL_SIZE -1; i+1 > 0; --i)
		heap_insert_node(h, (void*)i, (void*)"foo");
	
	EXPECT_EQ(h->size, 10);
	EXPECT_EQ(h->max_size, 10);
	
	for (size_t i = 0; i < 10; ++i)
		EXPECT_EQ((long)h->data[i].key, HEAP_INITIAL_SIZE*HEAP_INITIAL_SIZE -1 -i);
	
	heap_destructor(h);
}

TEST(MAX_HEAP, DELETE_NODE) {
	heap_t* h = heap_contructor(15, long_compare,
								key_destructor,
								info_destructor,
								print_key,
								print_info);
	
	EXPECT_EQ(h->size, 0);
	EXPECT_EQ(h->max_size, 15);
	
	// Level 0
	heap_insert_node(h, (void*)17, (void*)"17");
	
	// Level 1
	heap_insert_node(h, (void*)10, (void*)"10");
	heap_insert_node(h, (void*)15, (void*)"15");
	
	// Level 2
	heap_insert_node(h, (void*)8, (void*)"8");
	heap_insert_node(h, (void*)4, (void*)"4");
	heap_insert_node(h, (void*)9, (void*)"9");
	heap_insert_node(h, (void*)7, (void*)"7");
	
	// Level 3
	heap_insert_node(h, (void*)14, (void*)"14");
	heap_insert_node(h, (void*)3, (void*)"3");
	heap_insert_node(h, (void*)5, (void*)"5");
	heap_insert_node(h, (void*)2, (void*)"2");
	heap_insert_node(h, (void*)0, (void*)"0");
	heap_insert_node(h, (void*)6, (void*)"6");
	heap_insert_node(h, (void*)1, (void*)"1");
	heap_insert_node(h, (void*)20, (void*)"20");
	
	// Level 0
	EXPECT_EQ((long)h->data[0].key, 20);
	
	// Level 1
	EXPECT_EQ((long)h->data[1].key, 14);
	EXPECT_EQ((long)h->data[2].key, 17);
	
	// Level 2
	EXPECT_EQ((long)h->data[3].key, 10);
	EXPECT_EQ((long)h->data[4].key, 5);
	EXPECT_EQ((long)h->data[5].key, 9);
	EXPECT_EQ((long)h->data[6].key, 15);
	
	// Level 3
	EXPECT_EQ((long)h->data[7].key, 8);
	EXPECT_EQ((long)h->data[8].key, 3);
	EXPECT_EQ((long)h->data[9].key, 4);
	EXPECT_EQ((long)h->data[10].key, 2);
	EXPECT_EQ((long)h->data[11].key, 0);
	EXPECT_EQ((long)h->data[12].key, 6);
	EXPECT_EQ((long)h->data[13].key, 1);
	EXPECT_EQ((long)h->data[14].key, 7);
	
	///// APAGA UMA FOLHA
	heap_delete_node(h, 9);
	EXPECT_EQ(h->size, 14);
	
	// Level 0
	EXPECT_EQ((long)h->data[0].key, 20);
	
	// Level 1
	EXPECT_EQ((long)h->data[1].key, 14);
	EXPECT_EQ((long)h->data[2].key, 17);
	
	// Level 2
	EXPECT_EQ((long)h->data[3].key, 10);
	EXPECT_EQ((long)h->data[4].key, 7);
	EXPECT_EQ((long)h->data[5].key, 9);
	EXPECT_EQ((long)h->data[6].key, 15);
	
	// Level 3
	EXPECT_EQ((long)h->data[7].key, 8);
	EXPECT_EQ((long)h->data[8].key, 3);
	EXPECT_EQ((long)h->data[9].key, 5);
	EXPECT_EQ((long)h->data[10].key, 2);
	EXPECT_EQ((long)h->data[11].key, 0);
	EXPECT_EQ((long)h->data[12].key, 6);
	EXPECT_EQ((long)h->data[13].key, 1);
	
	///// APAGA UM NÓ INTERNO
	heap_delete_node(h, 4);
	EXPECT_EQ(h->size, 13);
	
	// Level 0
	EXPECT_EQ((long)h->data[0].key, 20);
	
	// Level 1
	EXPECT_EQ((long)h->data[1].key, 14);
	EXPECT_EQ((long)h->data[2].key, 17);
	
	// Level 2
	EXPECT_EQ((long)h->data[3].key, 10);
	EXPECT_EQ((long)h->data[4].key, 5);
	EXPECT_EQ((long)h->data[5].key, 9);
	EXPECT_EQ((long)h->data[6].key, 15);
	
	// Level 3
	EXPECT_EQ((long)h->data[7].key, 8);
	EXPECT_EQ((long)h->data[8].key, 3);
	EXPECT_EQ((long)h->data[9].key, 1);
	EXPECT_EQ((long)h->data[10].key, 2);
	EXPECT_EQ((long)h->data[11].key, 0);
	EXPECT_EQ((long)h->data[12].key, 6);
	
	///// APAGA OUTRO NÓ INTERNO
	heap_delete_node(h, 4);
	EXPECT_EQ(h->size, 12);
	
	// Level 0
	EXPECT_EQ((long)h->data[0].key, 20);
	
	// Level 1
	EXPECT_EQ((long)h->data[1].key, 14);
	EXPECT_EQ((long)h->data[2].key, 17);
	
	// Level 2
	EXPECT_EQ((long)h->data[3].key, 10);
	EXPECT_EQ((long)h->data[4].key, 6);
	EXPECT_EQ((long)h->data[5].key, 9);
	EXPECT_EQ((long)h->data[6].key, 15);
	
	// Level 3
	EXPECT_EQ((long)h->data[7].key, 8);
	EXPECT_EQ((long)h->data[8].key, 3);
	EXPECT_EQ((long)h->data[9].key, 1);
	EXPECT_EQ((long)h->data[10].key, 2);
	EXPECT_EQ((long)h->data[11].key, 0);
	
	///// APAGA A RAIZ
	heap_delete_node(h, 0);
	EXPECT_EQ(h->size, 11);
	
	// Level 0
	EXPECT_EQ((long)h->data[0].key, 17);
	
	// Level 1
	EXPECT_EQ((long)h->data[1].key, 14);
	EXPECT_EQ((long)h->data[2].key, 15);
	
	// Level 2
	EXPECT_EQ((long)h->data[3].key, 10);
	EXPECT_EQ((long)h->data[4].key, 6);
	EXPECT_EQ((long)h->data[5].key, 9);
	EXPECT_EQ((long)h->data[6].key, 0);
	
	// Level 3
	EXPECT_EQ((long)h->data[7].key, 8);
	EXPECT_EQ((long)h->data[8].key, 3);
	EXPECT_EQ((long)h->data[9].key, 1);
	EXPECT_EQ((long)h->data[10].key, 2);
	heap_destructor(h);
}

TEST(MAX_HEAP, TOP_N) {
	heap_t* h = heap_contructor(10, long_compare,
								key_destructor,
								info_destructor,
								print_key,
								print_info);
	
	EXPECT_EQ(h->size, 0);
	EXPECT_EQ(h->max_size, HEAP_INITIAL_SIZE);
	
	//// INSERTIONS
	// Level 0
	heap_insert_node(h, (void*)4, (void*)"4");
	
	// Level 1
	heap_insert_node(h, (void*)0, (void*)"0");
	heap_insert_node(h, (void*)2, (void*)"2");
	
	// Level 2
	heap_insert_node(h, (void*)17, (void*)"17");
	heap_insert_node(h, (void*)9, (void*)"9");
	heap_insert_node(h, (void*)7, (void*)"7");
	heap_insert_node(h, (void*)14, (void*)"14");
	
	// Level 3
	heap_insert_node(h, (void*)10, (void*)"10");
	heap_insert_node(h, (void*)8, (void*)"8");
	heap_insert_node(h, (void*)3, (void*)"3");
	heap_insert_node(h, (void*)5, (void*)"5");
	heap_insert_node(h, (void*)15, (void*)"15");
	heap_insert_node(h, (void*)6, (void*)"6");
	heap_insert_node(h, (void*)1, (void*)"1");
	heap_insert_node(h, (void*)20, (void*)"20");
	
	list_t* top_n = heap_top_n(h);
	EXPECT_EQ(top_n->size, 10);
	long expected[] = { 20, 17, 15, 14, 10, 9, 8, 7, 6, 5 };
	for (size_t i = 0; i < top_n->size-1; ++i) {
		EXPECT_EQ(expected[i], (long)list_pop_front(top_n));
		EXPECT_EQ(top_n->size, 10-i-1);
	}
	
	list_destructor(top_n);
	heap_destructor(h);
}