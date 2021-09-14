#define _CRT_SECURE_NO_WARNINGS
#include "arraylist.h"
#include <stdlib.h>
#include <string.h>

struct list* create_list()
{
	return (struct list*)calloc(1, sizeof(struct list));
}

struct element* create_element(char* text)
{
	if (text)
	{
		struct element* point = (struct element*)calloc(1, sizeof(struct element));
		point->text = (char*)calloc(strlen(text) + 1, sizeof(char));
		point->next = NULL;
		strcpy(point->text, text);
		return point;
	}
	return NULL;
}

struct element* append(struct list* list, struct element* element)
{
	if (list && element)
	{
		list->size++;
		if (list->element == NULL)
		{
			list->element = element;
		}
		else
		{
			struct element* point = list->element;
			while (point->next)
			{
				point = point->next;
			}
			point->next = element;
		}
		return element;
	}
	return NULL;
}

void insert(struct list* list, int index, struct element* element)
{
	if (list && element)
	{
		struct element* point = NULL;
		if (index == 0)
		{
			list->element = element;
			list->element->next = point;
		}
		else if (index == list->size)
		{
			append(list, element);
		}
		else
		{
			point = get(list, index - 1);
			struct element* p2 = point->next;
			point->next = element;
			point->next->next = p2;
		}
		list->size++;
	}
}

struct element* get(struct list* list, int index)
{
	if (list)
	{
		if (index >= 0 && index < list->size)
		{
			struct element* point = list->element;
			for (int i = 0; i < index; i++)
			{
				point = point->next;
			}
			return point;
		}
	}
	return NULL;
}

int size(struct list* list)
{
	if (list)
	{
		int size = 0;
		struct element* point = list->element;
		while (point)
		{
			point = point->next;
			size++;
		}
		return size;
	}
	return -1;
}

bool is_empty(struct list* list)
{
	if (size(list))
	{
		return true;
	}
	return false;
}

int get_index_of(struct list* list, const char* text)
{
	if (list && text)
	{
		struct element *point = list->element;
		int index = 0;
		while (point)
		{
			if (strcmp(point->text, text) == 0)
			{
				return index;
			}
			point = point->next;
			index++;
		}
		return index;
	}
	return -1;
}

struct element* remove_at(struct list* list, int index)
{
	if (list)
	{
		struct element* point = NULL;
		if (index == 0)
		{
			point = list->element;
			list->element = list->element->next;
			list->size--;
			return point;
		}
		else if(index == list->size - 1)
		{
			point = get(list, index - 1);
			struct element* p2 = point->next;
			point->next = NULL;
			list->size--;
			return p2;
		}
		else if (index > 0 && index < list->size)
		{
			point = get(list, index - 1);
			struct element* p2 = point->next;
			point->next = point->next->next;
			list->size--;
			return p2;
		}
	}
	return NULL;
}


struct element* remove_element(struct list* list, char* text)
{
	if (list && text)
	{
		int index = get_index_of(list, text);
		return remove_at(list, index);
	}
	return NULL;
}

void free_list(struct list* list) 
{
	if (list)
	{
		struct element* point = list->element;
		struct element* p2 = NULL;
		while (point)
		{
			p2 = point;
			point = point->next;
			free_element(p2);
		}
	}
}

void free_element(struct element* element)
{
	if (element)
	{
		free(element->text);
		free(element);
	}
}