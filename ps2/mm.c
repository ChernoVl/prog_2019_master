#include <stdio.h>
#include <stdlib.h>

int sum_of_digits(int number);

int main(){
	int sum = 0;
	char ch;
	do
	{
		scanf("%c", &ch);
		if (ch >= '0' && ch <= '9')
		{
			sum += (int)(ch - '0');
		}
		else
		{
			break;
		}

	} while (1);
	while (sum >= 10)
	{
		sum = sum_of_digits(sum);
	}
	printf("%d\n", sum);
	return 0;
}

int sum_of_digits(int number)
{
	int sum = 0;
	while (number != 0)
	{
		sum += number % 10;
		number /= 10;
	}
	return sum;
}