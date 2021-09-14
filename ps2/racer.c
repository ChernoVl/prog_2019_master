///#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 1000
#define eps 10e-8

struct move
{
	int s;
	int v;
};
typedef struct move Move;

double fx(double x, Move **move_set, int n, int t);
int search_for_the_minimum_array_element(Move **move_set, int n);
void freeMoveArr(Move **point, int n);

int main()
{
	int n; //reprezentuje pocet casti jednej jazdy
	int t; //reprezentuje celkovy cas jazdy
	scanf("%d%d", &n, &t);
	if (n >= 1 && n <= N && t >= 1 && t <= 10e6)
	{
		Move** move_set = (Move**)calloc(n, sizeof(Move*));
		for (int i = 0; i < n; i++)
		{
			move_set[i] = (Move*)calloc(1, sizeof(Move));
		}
		for (int i = 0; i < n; i++)
		{
			scanf("%d%d", &move_set[i]->s, &move_set[i]->v);
			if (move_set[i]->s<1 || move_set[i]->s>N || abs(move_set[i]->v) > N)
			{
				return 1;
			}
		}
		double a = -search_for_the_minimum_array_element(move_set, n);
		double b = 2e3 + 1;
		double k;
		while (fabs(b - a) > eps)
		{
			k = (a + b) / 2;
			if (fx(k, move_set, n, 0) > t)
			{
				a = k;
			}
			else
			{
				b = k;
			}
		}
		freeMoveArr(move_set, n);
		printf("%lf\n", k);
	}
	///system("pause");
	return 0;
}

double fx(double x, Move **move_set, int n, int t)
{
	if (move_set)
	{
		double y = 0.;
		for (int i = 0; i < n; i++)
		{
			y += move_set[i]->s / (move_set[i]->v + x);
		}
		y -= t;
		return y;
	}
	return 0;
}

int search_for_the_minimum_array_element(Move **move_set, int n)
{
	if (move_set)
	{
		int min = move_set[0]->v;
		for (int i = 1; i < n; i++)
		{
			if (min > move_set[i]->v)
			{
				min = move_set[i]->v;
			}
		}
		return min;
	}
	return 0;
}

void freeMoveArr(Move **point, int n)
{
	if (point == NULL)
	{
		return;
	}
	for (int i = 0; i < n; i++)
	{
		free(point[i]);
	}
	free(point);
}
