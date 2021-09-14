#include "backpack.h"
#include <stdlib.h>

struct backpack* create_backpack(const int capacity)
{
	struct backpack* tmp = (struct backpack*)calloc((size_t)capacity, sizeof(struct backpack));
	tmp->capacity = capacity;
	return tmp;
}

struct backpack* destroy_backpack(struct backpack* backpack)
{
	for (int i = 0; i < backpack->size; i++)
	{
		free(backpack[i].items);
	}
	free(backpack);
	return NULL;
}

bool add_item_to_backpack(struct backpack* backpack, struct item* item)
{
	if (backpack && item)
	{
		//backpack->items = item;
		return true;
	}
	return false;
}

void delete_item_from_backpack(struct backpack* backpack, struct item* item)
{
	if (backpack && item)
	{
		free(backpack->items);
	}
}

struct item* get_item_from_backpack(const struct backpack* backpack, char* name)
{
	if (backpack && name)
	{
		return NULL;//backpack->items;
	}
return NULL;
}