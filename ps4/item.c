#include "item.h"
#include <stdlib.h>
#include <string.h>

struct item* create_item(char* name, char* description, unsigned int properties)
{
	if (name && description && name[0] && description[0])
	{
		struct item* item = (struct item*)calloc(1, sizeof(struct item));
		item->name = name;
		item->description = description;
		item->properties = properties;
		return item;
	}
	return NULL;
}

struct item* destroy_item(struct item* item)
{
	if (item)
	{
		//free(item->name);
		//free(item->description);
		free(item);
	}
	return NULL;
}