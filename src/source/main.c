#include <stdio.h>
#include "hash_table.h"

int main() {
	hash_table_t* t = hash_table_constructor();
	hash_table_insert_elem(t, "r.cmgleite@gmail.com", "1");
	hash_table_insert_elem(t, "r.cmgleite@gmail.coma", "2");
	hash_table_insert_elem(t, "r.cmgleite@gmail.comb", "3");
	hash_table_insert_elem(t, "r.cmgleite@gmail.comc", "4");
	hash_table_insert_elem(t, "r.cmgleite@gmail.comd", "5");
	hash_table_insert_elem(t, "r.cmgleite@gmail.come", "6");

	hash_table_print(t);

	printf("%s\n", hash_table_find_elem(t, "r.cmgleite@gmail.com"));
	printf("%s\n", hash_table_find_elem(t, "r.cmgleite@gmail.comd"));
	printf("%s\n", hash_table_find_elem(t, "r.cmgleite@gmail.come"));

	char* value = hash_table_find_elem(t, "r.cmgleite@gmail.comll");
	if(value != NULL)
		return 1;
	else {
		printf("Value not found.. as it should be\n");
	}

	hash_table_destructor(t);
	return 0;
}
