#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#define	START	1
#define	BAITINWATER	2
#define	BITTING 3
#define	ESCAPE 4
#define FINISH 5
int sum = 0;
int status;

void sig_alarm()
{
	if (status == BAITINWATER) {
		printf("A fish is biting, pull the fishing rod\n");
		status = BITTING;
		alarm(3);
	} else if (status == BITTING) {
		printf("The fish was escaped\n");
		status = ESCAPE;
	}
	fflush(NULL);
}

void sig_int(int sig)
{
    printf("\n");
    if (status == START) {
        printf("Cast the fishing rod\nBait into water, waiting fish...\n");
        alarm(rand() % 3 + 3);
        status = BAITINWATER;
    } else if (status == BAITINWATER) {
        status = FINISH;
    } else if (status == BITTING) {
        alarm(0);
        printf("pull the fishing rod\nCatch a Fish!!\n");
        sum++;
        status = FINISH;
    } else if (status == ESCAPE) {
        printf("The bait was eaten\n");
        status = FINISH;
    }
    fflush(NULL);
}

void sig_stop()
{
	printf("\nTotally caught fishes: %d\n", sum);
	exit(0);
}

int main(int argc,char *argv[])
{
	srand(time(NULL));
	signal(SIGINT, sig_int);
	signal(SIGTSTP, sig_stop);
	signal(SIGALRM, sig_alarm);
	while (1) {
		printf("Fishing rod is ready!\n");
		status = START;
        while (status != FINISH)
            sleep(1);
	}
	return 0;
}
