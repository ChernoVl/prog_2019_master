//#define _CRT_SECURE_NO_WARNINGS
#include "arraylist.h"
#include <stdlib.h>

int main()
{
	struct list* list = create_list();
	struct element* element = create_element("Hello world");
	append(list, element);
	element = create_element("two");
	append(list, element);
	element = create_element("three");
	append(list, element);
	element = create_element("four");
	append(list, element);

	element = get(list, 1);

 	int result = get_index_of(list, "three");

	int list_size = size(list);

	result = is_empty(list);

	element = create_element("Cat");
	insert(list, 1, element);

	element = remove_element(list, "two");
	free_element(element);

	element = remove_at(list, size(list));
	free_element(element);

	free_list(list);
	return 0;
}