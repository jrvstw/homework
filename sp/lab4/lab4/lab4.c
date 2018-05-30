#include <stdio.h>
#include "apue.h"

void accumulation(int d_sum);
void addfunc(int num, int *count);

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
    TELL_WAIT();
    int count = 0;
    for (int i = 0; i < 5; i++) {
        if ((pid[i] = fork()) < 0)
            err_sys("fork error");
        else if (pid[i] == 0)
        {
            WAIT_PARENT();
            addfunc(i, &count);
            TELL_PARENT(getppid());
            exit(0);
        }
        else
            TELL_CHILD(pid[i]);
            WAIT_CHILD();
    }

	/**********************************************************/

	sum = fopen("sum.txt", "r");
	fscanf(sum, "%d", &total_sum);
    //printf("count = %d\n", count);
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

void addfunc(int num, int *count)
{
    FILE *current;
    int ptr = 0;
    char fname[] = "0-00.txt";

    fname[0] = '1' + num;
    for (int k = 1; k <= 52; k++) {
        fname[2] = '0' + k / 10;
        fname[3] = '0' + k % 10;
        current = fopen(fname, "r");
        for (int j = 0; j < 7; j++)
            for (int i = 0; i < 96; i++) {
                fscanf(current, "%d", &ptr);
                accumulation(ptr);
                (*count)++;
            }
        fclose(current);
    }
    return;
}

