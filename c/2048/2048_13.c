#include <stdio.h>
#include <string.h>
void settings(int *size, int *win, char output[15][5], int *played);
void randomize();
void add_number(int a[10][10], int size);
void reset_game(int a[10][10], int size, int *score, int *game,\
                int *played, int *undo);
void transform_matrix(int a[10][10], int size, char input);
void line_push_left(int a[10], int size, int *score);
void move_matrix(int GAME[10][10], int *score, int size, int move,\
                 int UNDO[10][10], int *score_undo)
{
    int TMP[10][10], score_tmp, i, j, movable = 0;
    // test result in TMP[][]
    score_tmp = *score;
    for (i = 0; i < size; i++) for (j = 0; j < size; j++)
        TMP[i][j] = GAME[i][j];
    transform_matrix(TMP, size, move);
    for (i = 0; i < size; i++)
        line_push_left(TMP[i], size, &score_tmp);
    transform_matrix(TMP, size, move);
    // check if movable in assigned direction
    movable = 0;
    for (i = 0; i < size; i++) for (j = 0; j < size; j++)
        if (TMP[i][j] != GAME[i][j])
            movable = 1;
    if (!movable) break;
    // save result: GAME[][]=TMP[][]
    reprint = 1;
    for (i = 0; i < size; i++) for (j = 0; j < size; j++) {
        UNDO[i][j] = GAME[i][j];
        GAME[i][j] = TMP[i][j];
    }
    score_undo = score;
    score = score_tmp;
    add_number(GAME, size);
}
/*
Main Function Structure:
{
    initialize;
    Game stage loop {
        play loop {
            print play screen;
            switch input {
                case: move
                case: undo
                case: menu
            }
        }
        menu loop {
            print menu;
            switch input {
                case: resume
                case: restart
                case: settings
                case: exit game
            }
        }
    }
}
*/

main()
{
    int GAME[10][10] = {0}, score, UNDO[10][10] = {0}, score_undo;
    char output[15][5] = {"  - ", "  2 ", "  4 ", "  8 ", " 16 ", " 32 ",
          " 64 ", "128 ", "256 ", "512 ", "1024", "2048", "4096", "8192"};
    int size = 4, win = 11;
    int game, played, undo, movable, reprint = 1;
    char stage = 'p', input;
    int TMP[10][10] = {0}, score_tmp, i, j;
    randomize();
    reset_game(GAME, size, &score, &game, &played, &undo);
    // Game Stage Loop
    while (stage) {
        // stage p: Play
        while (stage == 'p') {
            // p:1 print play screen
            if (reprint) {
                reprint = 0;
                system("cls");
                // print instructions
                printf(" Menu(esc)");
                if (undo) printf("     Undo(z)");
                // print score and GAME[][]
                printf("\n------------------------\n\n"
                       "       Score: %5d\n\n", score);
                for (i = 0; i < size; i++) {
                    for (j = 0; j < size; j++)
                        printf(" %s", output[GAME[i][j]]);
                    printf("\n\n");
                }
                // print notifications
                printf("\n\n");
                if (!played) {
                    played = 1;
                    printf("\nPress arrow keys to play.");
                }
                if (game == 1) printf("\nYou win!");
                if (game == -1) printf("\nYou lose.");
            }
            // p:2 switch input
            input = getch();
            switch (input) {
            // p:2-a arrow keys
            case 72: case 75: case 77: case 80:
                // if game is set, arrow keys are invalid
                if (game) break;
                // move matrix
                move_matrix(GAME, &score, size, input, UNDO, &score_undo);
                // check winning or losing
                game = -1;
                for (i = 0; i < size; i++) for (j = 0; j < size; j++)
                    if (GAME[i][j] == 0)
                        game = 0;
                for(i = 0; i < size; i++) for(j = 0; j < size - 1; j++)
                    if (GAME[i][j] == GAME[i][j + 1] ||\
                        GAME[j][i] == GAME[j + 1][i])
                        game = 0;
                for (i = 0; i < size; i++) for (j = 0; j < size; j++)
                    if (GAME[i][j] == win)
                        game = 1;
                undo = (game == 1)? 0 : 1;
                break;
            // p:2-b undo
            case 'z':
                if (!undo) break;
                reprint = 1;
                game = undo = 0;
                score = score_undo;
                for (i = 0; i < size; i++) for (j = 0; j < size; j++)
                    GAME[i][j] = UNDO[i][j];
                break;
            // p:2-c menu
            case 27:
                stage = 'm';
                reprint = 1;
            // p:2-d other input automatically continues input loop
            }
        }
        // stage m: Menu
        while (stage == 'm') {
            // m:1 print menu screen
            if (reprint) {
                reprint = 0;
                system("cls");
                printf(" Menu\n------------------------\n");
                if (played) printf("esc: Resume\n"); else printf("\n");
                printf(" r : Restart\n s : Settings\n e : Exit\n\n");
            }
            // m:2 switch input
            input = getch();
            switch (input) {
            // m:2-a resume
            case 27:
                if (!played) break;
                stage = 'p';
                reprint = 1;
                break;
            // m:2-b reset
            case 'r':
                stage = 'p';
                reprint = 1;
                reset_game(GAME, size, &score, &game, &played, &undo);
                break;
            // m:2-c settings
            case 's':
                settings(&size, &win, output, &played);
                stage = 'm';
                reprint = 1;
                break;
            // m:2-d exit game
            case 'e':
                stage = 0;
            // m:2-e other input automatically continues input loop
            }
        }
    }
}

void settings(int *size, int *win, char output[15][5], int *played)
{
    int set = 0, line = 0, reprint = 1, value[2][3] = {3, 0, 10, 5, 0, 13};
    char input, arrow[2][2];
    int i;
    value[0][1] = *size;
    value[1][1] = *win;
    // stage s: settings
    while (!set) {
        // s:1 print settings screen
        if (reprint) {
            reprint = 0;
            system("cls");

            for (i = 0; i < 2; i++)
                arrow[i][0] = arrow[i][1] = ' ';
            arrow[line][0] = (value[line][0] == value[line][1])? ' ' : '<';
            arrow[line][1] = (value[line][1] == value[line][2])? ' ' : '>';

            printf("\n\n       Set size:    %c  %4d  %c",\
                   arrow[0][0], value[0][1], arrow[0][1]);
            printf("\n Set difficulty:    %c  %s  %c",\
                   arrow[1][0], output[value[1][1]], arrow[1][1]);
            printf("\n\n"
                   "\n Press arrow keys to adjust."
                   "\n Press Enter to apply."
                   "\n Press ESC to cancel.");
        }
        // s:2 switch input
        input = getch();
        switch (input) {
        // s:2-a apply settings
        case 13:
            *size = value[0][1];
            *win = value[1][1];
            *played = 0;
            set = 1;
            break;
        // s:2-b cancel
        case 27:
            set = 1;
            break;
        // s:2-c up
        case 72:
            if (line == 0) break;
            line--;
            reprint = 1;
            break;
        // s:2-d down
        case 80:
            if (line == 1) break;
            line++;
            reprint = 1;
            break;
        // s:2-e left
        case 75:
            if (value[line][0] == value[line][1])
                break;
            value[line][1]--;
            reprint = 1;
            break;
        // s:2-f right
        case 77:
            if (value[line][1] == value[line][2])
                break;
            value[line][1]++;
            reprint = 1;
            break;
        // s:2-g other input automatically continues input loop
        }
    }
}

void randomize()
{
    time_t t;
    srand((unsigned)time(&t));
}

void add_number(int a[10][10], int size)
{
    int i, j;
    while(1) {
        i = rand()%size;
        j = rand()%size;
        if (a[i][j] == 0) {
            a[i][j] = rand()%2+1;
            break;
        }
    }
}

void reset_game(int a[10][10], int size, int *score, int *game,\
                int *played, int *undo)
{
    int i, j;
    *game = *undo = *played = *score = 0;
    for (i = 0; i < size; i++) for (j = 0; j < size; j++)
        a[i][j] = 0;
    add_number(a, size);
}

void transform_matrix(int a[10][10], int size, char input)
{
    int i, j, tmp;
    switch (input) {
    case 72:
        for (i = 0; i < size; i++) for (j = i+1; j < size; j++) {
            tmp = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = tmp;
        }
        break;
    case 80:
        for (i = 0; i < size; i++) for (j = 0; j < size-1-i; j++) {
            tmp = a[i][j];
            a[i][j] = a[size-1-j][size-1-i];
            a[size-1-j][size-1-i]=tmp;
        }
        break;
    case 77:
        for (i = 0; i < size; i++) for (j = 0; j <= size/2-1; j++) {
            tmp = a[i][j];
            a[i][j] = a[i][size-1-j];
            a[i][size-1-j]=tmp;
        }
    }
}

void line_push_left(int a[10], int size, int *score)
{
    int SCORE[15] = {0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,\
        2048, 4096, 8192};
    int i, j;
    for (i = 0; i < size-1; i++)
        if (a[i] != 0) {
            j = i + 1;
            while (a[j] == 0 && j < size)
                j++;
            if (a[i] == a[j] && j < size) {
                a[i]++;
                *score += SCORE[a[i]];
                a[j] = 0;
            }
    }
    for (i = 0; i < size-1; i++) {
        j = i;
        while (a[j] == 0 && j < size)
            j++;
        if (j != i && j < size) {
            a[i] = a[j];
            a[j] = 0;
        }
    }
}
