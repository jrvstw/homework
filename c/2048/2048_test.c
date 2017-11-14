#include <stdio.h>
void transform_matrix(int width, int a[10][10], char move);
void line_push_left(int width, int a[10]);


main()
{
    int N, game, i, j, width=4, a[10][10]={0};
    char move;
//    freopen("2048.in","r",stdin);
    scanf("%d", &N);
    while(N--)
    {   //input
        for(i=0;i<width;i++) for(j=0;j<width;j++) scanf("%d ", &a[i][j]);
        scanf("%c", &move);
        //push matrix
        transform_matrix(width,a,move);
        for(i=0;i<width;i++) line_push_left(width,a[i]);
        transform_matrix(width,a,move);
        //check win or lose
        game=-1;
        for(i=0;i<width;i++) for(j=0;j<width-1;j++) if (a[i][j]==a[i][j+1] || a[j][i]==a[j+1][i]) game=0;
        for(i=0;i<width;i++) for(j=0;j<width;j++) if(a[i][j]==0) game=0;
        for(i=0;i<width;i++) for(j=0;j<width;j++) if(a[i][j]==64) game=1;
        //output
        for(i=0;i<width;i++)
        {
            for(j=0;j<width-1;j++) printf("%d ", a[i][j]);
            printf("%d\n", a[i][width-1]);
        }
        if(game==1) printf("You win\n");
        if(game==-1) printf("Game over\n");
        if(N) printf("\n");
    }
}

void transform_matrix(int width, int a[10][10], char move)
{
    int i, j, tmp;
    if(move=='w') for(i=0;i<width;i++) for(j=i+1;j<width;j++)
    {
        tmp=a[i][j]; a[i][j]=a[j][i]; a[j][i]=tmp;
    }
    if(move=='s') for(i=0;i<width;i++) for(j=0;j<width-1-i;j++)
    {
        tmp=a[i][j]; a[i][j]=a[width-1-j][width-1-i]; a[width-1-j][width-1-i]=tmp;
    }
    if(move=='d') for(i=0;i<width;i++) for(j=0;j<=width/2-1;j++)
    {
        tmp=a[i][j]; a[i][j]=a[i][width-1-j]; a[i][width-1-j]=tmp;
    }
}

void line_push_left(int width, int a[10])
{
    int i, j;
    // add up
    for(i=0;i<width-1;i++) if(a[i]!=0)
    {
        j=i+1;
        while(a[j]==0 && j<width) j++;
        if(a[i]==a[j] && j<width)
        {
            a[i]*=2;
            a[j]=0;
        }
    }
    // move
    for(i=0;i<width-1;i++)
    {
        j=i;
        while(a[j]==0&&j<width) j++;
        if(j!=i&&j<width)
        {
            a[i]=a[j];
            a[j]=0;
        }
    }
}
