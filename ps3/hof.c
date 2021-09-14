#include "hof.h"
#include <stdio.h>
#include <stdlib.h>

struct player* sort(const struct player list[], const int size);
int load(struct player list[])
{
	FILE *fp = fopen(HOF_FILE, "r");
	if (fp == NULL)
	{
		return -1;
	}
	int count = 0;
	while (!feof(fp) && count < 10)
	{
		if (fscanf(fp, "%s", list[count].name) != EOF &&
			fscanf(fp, "%d", &list[count].score) != EOF)
		{
			count++;
		}
	}
	//copy
	struct player* point = sort(list, count);
	for (int i = 0; i < count; i++)
	{
		list[i] = point[i];
	}
	free(point);
	fclose(fp);
	return count;
}

void swap(struct player* list1, struct player* list2);
bool save(const struct player list[], const int size)
{
	struct player *tmp_list = sort(list, size);
	FILE *fp = fopen(HOF_FILE, "w");
	if (fp == NULL)
	{
		free(tmp_list);
		return false;
	}
	for (int i = 0; i < size; i++)
	{
		fprintf(fp, "%s", tmp_list[i].name);
		fprintf(fp, "%s", DELIMITER);
		fprintf(fp, "%d\n", tmp_list[i].score);
	}
	fclose(fp);
	free(tmp_list);
	return true;
}

bool add_player(struct player list[], int* size, const struct player player)
{
	if (list && size && player.name && (*size) >= 0 && (*size) <= 10)
	{
		for (int i = 0; i < *size; i++)
		{
			if (player.score >= list[i].score)
			{
				for (int j = 9; j > i; j--)
				{
					list[j] = list[j - 1];
				}
				list[i] = player;
				if ((*size) < 10) (*size)++;
				return true;
			}
		}
		if ((*size) < 10)
		{
			list[*size] = player;
			(*size)++;
			return true;
		}
	}
	return false;
}

struct player* sort(const struct player list[], const int size)
{
	struct player* tmp_list = (struct player*)calloc((unsigned int)size, sizeof(struct player));
	for (int i = 0; i < size; i++)
	{
		tmp_list[i] = list[i];
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (tmp_list[j].score < tmp_list[j + 1].score)
			{
				swap(&tmp_list[j], &tmp_list[j + 1]);
			}
		}
	}
	return tmp_list;
}

void swap(struct player* list1, struct player* list2)
{
	struct player tmp = *list1;
	*list1 = *list2;
	*list2 = tmp;
}
