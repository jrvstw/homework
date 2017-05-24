#include <stdio.h>
#include "apue.h"

void accumulation(int d_sum);

int main()
{
	FILE* sum;
	int total_sum=0;
	pid_t pid[5];
	int year=5, week=52, day=7;

	sum = fopen("sum.txt", "w");
	fprintf(sum, "%d\n", 0);
	fclose(sum);

	/**********************************************************/

	//Implement your code.

	/**********************************************************/

	sum = fopen("sum.txt", "r");
	fscanf(sum, "%d", &total_sum);
	printf("Day_Average = %d\n",total_sum/(year*week*day));
	fclose(sum);

	return 0;
}

void accumulation(int d_sum)    //Accumulating the daily sum to "sum.txt".
{
	FILE* sum;
	int tmp=0;

	sum = fopen("sum.txt", "r+");
	fscanf(sum, "%d", &tmp);

	tmp += d_sum;

	rewind(sum);
	fprintf(sum, "%d", tmp);
	fclose(sum);

	return;
}
