#include "backpack.h"
#include "item.h"
#include "room.h"
#include "container.h"
#include <stdlib.h>
//#include <string.h>

int main()
{
	struct item* key = create_item("ZLATY KLUC",
		"Zlaty kluc pravdepodobne od zlatej zamky. Su na nom viditelne vyryte pismena AB",
		MOVABLE | USABLE);
	key = destroy_item(key);
	struct backpack* backpack = create_backpack(5);
	backpack = destroy_backpack(backpack);
	add_item_to_backpack(backpack, key);
	get_item_from_backpack(backpack, "zlaty klucik");
	delete_item_from_backpack(backpack, key);
	create_room(NULL,NULL);
	destroy_room(NULL);
	set_exits_from_room(NULL,NULL,NULL,NULL,NULL);
	show_room(NULL);
//<<<<<<< HEAD
	strlen("affd");
=======
	create_container(NULL, 0, NULL);
//>>>>>>> b3e52951b9348d310fdfc39aaac7340257ec0131
	return 0;
}
