///#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define A 0.
#define B 1e5
#define EPS 1e-8
#define SIZE 1e5
#define CImm 1e-3
#define CImkm 1e-6
#define CIk 1e3
#define M_PI 3.14159265358979323846

enum boolean { false, true };
typedef enum boolean bool;

struct scope
{
	int R;
	int X;
	int Y;
	int Z;
};
typedef struct scope Scope;

double* solve(Scope **Paramaters, int M, int S);

double fx(Scope **Paramaters, int M, int S, double z2);

double Vsegment(double R, double a, double b);
double V_all(Scope **Paramaters, int M);

void freeArrStruct(Scope **point, int n);

int main(void)
{
	int M; //number of holes in cheese
	int S; //number of slices
	scanf("%d%d", &M, &S);
	while (getchar() != '\n');
	if (M >= 0 && M <= 1e4 && S >= 1 && S <= 100)
	{
		Scope **Paramaters = NULL;
		if (M)
		{
			Paramaters = (Scope**)calloc(M, sizeof(Scope*));
			for (int i = 0; i < M; i++)
			{
				Paramaters[i] = (Scope*)calloc(1, sizeof(Scope));
				scanf("%d %d %d %d", &Paramaters[i]->R, &Paramaters[i]->X, &Paramaters[i]->Y, &Paramaters[i]->Z);
				while (getchar() != '\n');
				if (Paramaters[i]->R < A || Paramaters[i]->R > B ||
					Paramaters[i]->X < A || Paramaters[i]->X > B ||
					Paramaters[i]->Y < A || Paramaters[i]->Y > B ||
					Paramaters[i]->Z < A || Paramaters[i]->Z > B)
				{
					return 0;
				}
			}
		}
		double *p;
		p = solve(Paramaters, M, S);
		for (int i = 0; i < S; i++)
		{
			printf("%.9lf\n", p[i]);
		}
		free(p);
		freeArrStruct(Paramaters, M);
		///system("pause");
		return 0;
	}
}

double* solve(Scope **Paramaters, int M, int S)
{
	double *resolve = (double*)calloc(S, sizeof(double));
	double V; //Цілий обєм
	double V1; //обєм одного кусочку
	V = V_all(Paramaters, M); // обєм кубику сиру в mm (mkm = 10^−6m)
	V1 = V / (double)S;
	double a;
	double b;
	double x;
	double tmp = 0.;
	for (int i = 0; i < S; i++)
	{
		x = tmp + (double)SIZE / S;
		if (M)
		{
			a = 0.;
			b = (double)SIZE;
			while (b - a >= EPS)
			{
				x = (a + b) / 2.;
				if (fx(Paramaters, M, S, x) > V1 * (double)(i + 1))
				{
					b = x;
				}
				else
				{
					a = x;
				}
			}
		}
		resolve[i] = x - tmp;
		tmp += resolve[i];
		resolve[i] *= CImm;
	}
	return resolve;
}

double fx(Scope **Paramaters, int M, int S, double z2)
{
	if (Paramaters)
	{
		double Vp; //обєм одного кусочка, тобіж Паралелепіпеда
		double Vc; //обєм сегменту
		double a;
		double b;

		double z1 = 0.; // початок координат
		double z3; //нижня точка кола
		double h; //висота сегменту
		double c = z2 - z1; //висота куска
		Vp = (double)(SIZE * SIZE) * c; //обєм куска без дирок

		Vc = 0.; // рахуємо обєм сегментів куль в заданому куску
		for (int i = 0; i < M; i++)
		{
			z3 = (double)(Paramaters[i]->Z - Paramaters[i]->R); //нижня точка кола
			h = z2 - z3;
			// вибираємя поле інтегрування
			if (h > 0)
			{
				if (h > 2. * (double)Paramaters[i]->R)
				{
					a = (double)Paramaters[i]->R;
				}
				else if (h >= (double)Paramaters[i]->R)
				{
					a = h - (double)Paramaters[i]->R;
				}
				else
				{
					a = -(Paramaters[i]->R - h);
				}
				if (z3 < z1) // якщо н.т.к нмжче осі координат
				{
					b = (-Paramaters[i]->R - z3);
				}
				else
				{
					b = -(double)Paramaters[i]->R;
				}
				Vc += Vsegment((double)Paramaters[i]->R, a, b);
			}
		}
		return Vp - Vc;
	}
	return 0.;
}

double V_all(Scope **Paramaters, int M)
{
	double V = (double)(SIZE * SIZE * SIZE);
	if (Paramaters)
	{
		for (int i = 0; i < M; i++)
		{
			V -= 4. / 3. * M_PI * Paramaters[i]->R * Paramaters[i]->R * Paramaters[i]->R;
		}
	}
	return V;
}

double Vsegment(double R, double a, double b)
{
	if (R >= 0)
	{
		if ((a < 0 ? (-a) <= R : a <= 2. * R) && (b < 0 ? (-b) <= R : b <= 2 * R))
		{
			return M_PI * (R * R * (a - b) - 1. / 3. * (a * a * a - b * b * b));
		}
	}
	return 0;
}

void freeArrStruct(Scope **point, int n)
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