#include "gtest/gtest.h"
#include "hash_table.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

TEST(HASH_TABLE_TEST, HASH_FUNCTION) {
	hash_table_t* t = hash_table_constructor();
	const char* key1 = "r.cmgleite@gmail.com\0";
	const char* key2 = "r.cmgleite@gmail.coma\0";
	const char* key3 = "r.cmgleite@gmail.comb\0";
	const char* key4 = "aaa\0";
	const char* key5 = "foobarfoobar\0";
	const char* key6 = "1234556788\0";
	const char* key7 = "foo@bar.com.br\0";
	const char* key8 = "r.cmgleite@gmail.comd\0";


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

	hash_table_destructor(t);
}
