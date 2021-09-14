#include <stdlib.h>

#include "k.h"

void add_random_tile(struct game *game){
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}


int move(char *arr, int dx, bool *ind);
bool letter(char ch);
void del(char *arr, int index, int dx);
bool update(struct game *game, int dy, int dx)
{
	if (game && ((dy == 0 && (dx == -1 || dx == 1)) || ((dy == -1 || dy == 1) && dx == 0)))
	{
		if (game->board)
		{
			bool ind = false;
			if (dy == 0)
			{
				for (int i = 0; i < SIZE; i++)
				{
					game->score += move(game->board[i], dx, &ind);
				}
				if (ind)
				{
					return true;
				}
			}
			else // if (dx == 0)
			{
				char *tmp_arr = (char*)calloc(SIZE, sizeof(char));
				for (int i = 0; i < SIZE; i++)
				{
					for (int j = 0; j < SIZE; j++)
					{
						tmp_arr[j] = game->board[j][i];
					}
					game->score += move(tmp_arr, dy, &ind);
					for (int j = 0; j < SIZE; j++)
					{
						game->board[j][i] = tmp_arr[j];
					}
				}
				free(tmp_arr);
				if (ind)
				{
					return true;
				}
			}
		}
	}
	return false;
}

int letter_score(char ch);
int move(char *arr, int dx, bool *ind)
{
	if (arr)
	{
		bool ind_space = false;
		int score = 0;
		int i;
		int size = SIZE;
		for ((dx == -1) ? (i = 0) : (i = size - 1); ((dx == -1) ? (i < size) : (i >= 0)) && size; i += -dx)
		{
			if (arr[i] == ' ')
			{
				ind_space = true;
			}
			if (ind_space && letter(arr[i]))
			{
				(*ind) = true;
				break;
			}
		}
		for ((dx == -1) ? (i = 0) : (i = size - 1); ((dx == -1) ? (i < size) : (i >= 0)) && size; i += -dx)
		{
			if (arr[i] == ' ')
			{
				del(arr, i, dx);
				i += dx;
				size--;
			}
		}
		size = SIZE;
		for ((dx == -1) ? (i = 0) : (i = size - 1); (dx == -1) ? (i < size - 1) : (i >= 1); i += -dx)
		{
			if (letter(arr[i]) && arr[i] == arr[i - dx])
			{
				score += 2 * letter_score(arr[i]);
				arr[i]++;
				del(arr, i - dx, dx);
				i += dx;
				size--;
				(*ind) = true;
				break;
			}
		}
		return score;
	}
	return 0;
}

bool letter(char ch)
{
	return (ch >= 'A' && ch <= 'Z') ? true : false;
}

void del(char *arr, int index, int dx)
{
	if (arr)
	{
		int i;
		for (i = index; (dx == -1) ? (i < SIZE - 1) : (i >= 1); i += -dx)
		{
			arr[i] = arr[i - dx];
		}
		(dx == -1) ? (arr[SIZE - 1] = ' ') : (arr[0] = ' ');
	}
}

int letter_score(char ch)
{
	/*if (ch == 'A')
	{
		return 2;
	}
	return letter_score((char)((int)ch - 1)) * 2;*/
	int count = 1;
	for (int i = 0; i <= (int)(ch - 'A'); i++)
	{
		count *= 2;
	}
	return count;
}

bool is_move_possible(const struct game game)
{
	int i, j;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if ((game.board[i][j] == game.board[i + 1][j] ||
				game.board[i][j] == ' ' || game.board[i + 1][j] == ' ') &&
				i < SIZE - 1)
			{
				return true;
			}
			if (game.board[i][j] == game.board[i][j + 1] && j < SIZE - 1)
			{
				return true;
			}
		}
	}
	return false;
}

bool is_game_won(const struct game game)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (game.board[i][j] == 'K')
			{
				return true;
			}
		}
	}
	return false;
}