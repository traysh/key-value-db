#include <stdio.h>
#include "ordered_hash_table.h"

int main() {
	ordered_hash_table_t* t = ordered_hash_table_constructor();
	// Insert
	printf("Insert Begin\n");
	ordered_hash_table_insert_elem(&t, "r.cmgleite@gmail.com",  1);
	ordered_hash_table_insert_elem(&t, "r.cmgleite@gmail.coma", 2);
	ordered_hash_table_insert_elem(&t, "r.cmgleite@gmail.comb", 3);
	ordered_hash_table_insert_elem(&t, "r.cmgleite@gmail.comc", 4);
	ordered_hash_table_insert_elem(&t, "r.cmgleite@gmail.comd", 5);
	ordered_hash_table_insert_elem(&t, "r.cmgleite@gmail.come", 6);
	printf("Insert End\n");

	ordered_hash_table_print(t);

	// Find
	printf("Find Begin\n");
	printf("%d\n", ordered_hash_table_find_elem(t, "r.cmgleite@gmail.com")->value);
	printf("%d\n", ordered_hash_table_find_elem(t, "r.cmgleite@gmail.comd")->value);
	printf("%d\n", ordered_hash_table_find_elem(t, "r.cmgleite@gmail.come")->value);

	ordered_hash_table_entry_t* entry = ordered_hash_table_find_elem(t, "r.cmgleite@gmail.comll");
	if (entry != nullptr)
		return 1;
	else
		printf("Value not found.. as it should be\n");
	printf("Find End\n");

	// Update
	printf("Update Begin\n");
	ordered_hash_table_update_elem(t, "r.cmgleite@gmail.com", 33);
	printf("Update End\n");
	ordered_hash_table_print(t);

	// Delete
	printf("Delete Begin\n");
	ordered_hash_table_delete_elem(t, "r.cmgleite@gmail.com");
	printf("Delete End\n");
	ordered_hash_table_print(t);

	ordered_hash_table_destructor(t);
	return 0;
}
