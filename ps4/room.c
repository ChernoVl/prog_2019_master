#include "room.h"
#include <stdlib.h>
#include <stdio.h>

struct room* create_room(char* name, char* description)
{
	if (name && description)
	{
		struct room* point = (struct room*)calloc(1, sizeof(struct room));
		point->description = description;
		point->name = name;
		return point;
	}
	return NULL;
}

struct room* destroy_room(struct room* room)
{
	if (room)
	{
		free(room);
	}
return NULL;
}

void set_exits_from_room(struct room* room, struct room* north, struct room* south, struct room* east, struct room* west)
{
	if (room)
	{
		room->north = north;
		room->south = south;
		room->east = east;
		room->west = west;
	}
}

void show_room(const struct room* room)
{
	if (room)
	{
		printf("show_room: %s\n%s\n", room->name, room->description);
	}
}