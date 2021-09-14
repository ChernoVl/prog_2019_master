#include "k.h"
#include "hof.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

bool change(struct game *game, char direction);

int main()
{
	printf("\e[1;1H\e[2J");
	struct player player;
	char ch;
	int ind;
	printf("Your name: ");
	scanf("%s", player.name);
	while (getchar() != '\n');
	player.score = 0;
	struct game game = {
		.board = {
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}
		},
		.score = 0
	};
	do
	{
		printf("\e[1;1H\e[2J");
		printf("Your name: %s\n", player.name);
		add_random_tile(&game);
		render(game);
		do
		{
			printf("Enter a direction: ");
			scanf("%c", &ch);
			while (getchar() != '\n');
			ind = 0;
			if (!is_move_possible(game))
			{
				printf("*ERROR* is not move possible!\n");
				ind = 0;
			}
			else if (!change(&game, ch))
			{
				printf("*ERROR* You can enter {w,a,s,d}!\n");
				ind = 1;
			}
		} while (ind);

	} while (is_move_possible(game) && !is_game_won(game));
	printf("Are you want to save score?\nYes - [y]\tNo - [n]: ");
	do{
		scanf("%c", &ch);
		while (getchar() != '\n');
	} while (ch != 'y' && ch != 'n');
	if (ch == 'y')
	{
		struct player list[10];
		int size = load(list);
		player.score = game.score;
		if (add_player(list, &size, player))
		{
			printf("Saved!\n");
			save(list, size);
		}
		else
		{
			printf("Unfortunately you are not in the TOP 10 :-(\n");
		}
	}
    return 0;
}

bool change(struct game *game, char direction)
{
	switch (direction)
	{
	case 'w':
		if (!update(game, -1, 0))
		{
			return false;
		}
		break;
	case 's':
		if (!update(game, 1, 0))
		{
			return false;
		}
		break;
	case 'a':
		if (!update(game, 0, -1))
		{
			return false;
		}
		break;
	case 'd':
		if (!update(game, 0, 1))
		{
			return false;
		}
		break;
	default:
		return false;
	}
	return true;
}