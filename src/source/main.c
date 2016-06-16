#include <stdio.h>
#include "hash_table.h"

int main() {
	hash_table_t* t = hash_table_constructor();
	// Insert
	printf("Insert Begin\n");
	hash_table_insert_elem(t, "r.cmgleite@gmail.com", "1");
	hash_table_insert_elem(t, "r.cmgleite@gmail.coma", "2");
	hash_table_insert_elem(t, "r.cmgleite@gmail.comb", "3");
	hash_table_insert_elem(t, "r.cmgleite@gmail.comc", "4");
	hash_table_insert_elem(t, "r.cmgleite@gmail.comd", "5");
	hash_table_insert_elem(t, "r.cmgleite@gmail.come", "6");
	printf("Insert End\n");

	hash_table_print(t);

	// Find
	printf("Find Begin\n");
	printf("%s\n", hash_table_find_elem(t, "r.cmgleite@gmail.com"));
	printf("%s\n", hash_table_find_elem(t, "r.cmgleite@gmail.comd"));
	printf("%s\n", hash_table_find_elem(t, "r.cmgleite@gmail.come"));

	char* value = hash_table_find_elem(t, "r.cmgleite@gmail.comll");
	if(value != NULL)
		return 1;
	else {
		printf("Value not found.. as it should be\n");
	}
	printf("Find End\n");

	// Update
	printf("Update Begin\n");
	hash_table_update_elem(t, "r.cmgleite@gmail.com", "Novo Valor");
	printf("Update End\n");
	hash_table_print(t);

	// Delete
	printf("Delete Begin\n");
	hash_table_delete_elem(t, "r.cmgleite@gmail.com");
	printf("Delete End\n");
	hash_table_print(t);

	hash_table_destructor(t);
	return 0;
}
