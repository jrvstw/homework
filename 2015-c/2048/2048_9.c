#include <stdio.h>
void randomize();
void add_number(int a[10][10], int width);
void reset_game(int a[10][10], int width, int *score, int *game, int *played, int *undo);
void transform_matrix(int a[10][10], int width, char input);
void line_push_left(int a[10], int width, int *score, int output[]);
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
        settings loop {
            print settings;
            switch input {
                case: adjust
                case: apply settings
                case: cancel
            }
        }
    }
}
*/

main()
{
    int GAME[10][10] = {0}, score, UNDO[10][10] = {0}, score_undo;
    int output[15] = {0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, -1};
    int width = 4, win = 11, settings[2][3] = {3, -1, 10, 5, -1, 14};
    int game, played, undo, movable, reprint = 1;
    char stage = 'p', input;
    int TMP[10][10] = {0}, score_tmp, i, j;
    randomize();
    reset_game(GAME, width, &score, &game, &played, &undo);
    // Game Stage Loop
    while (stage) {
        // stage p: Play
        while (stage == 'p') {
            // p:1 print play screen
            while (reprint) {
                reprint = 0;
                system("cls");
                // print instructions
                printf(" Menu(esc)");
                if (undo) printf("     Undo(z)");
                // print score and GAME[][]
                printf("\n------------------------\n\n       Score: %5d\n\n", score);
                for (i = 0; i < width; i++) {
                    for (j = 0; j < width; j++)
                        printf(" %4d", output[GAME[i][j]]);
                    printf("\n\n");
                }
                // print notifications
                if (!played) {
                    played = 1;
                    printf("Press arrow keys to play.\n");
                }
                if (game == 1) {
                    game = 0;
                    reprint = 1;
                    printf("You win! Press Space to continue playing.\n");
                    do input = getch(); while (input != 32);
                }
                else if (game == -1) printf("You lose.\n");
            }
            // p:2 switch input
            input = getch();
            switch (input) {
            // p:2-a arrow keys
            case 72: case 75: case 77: case 80:
                // if game is set, arrow keys are invalid
                if (game) break;
                // test result in TMP[][]
                score_tmp = score;
                for (i = 0; i < width; i++) for (j = 0; j < width; j++)
                    TMP[i][j] = GAME[i][j];
                transform_matrix(TMP, width, input);
                for (i = 0; i < width; i++)
                    line_push_left(TMP[i], width, &score_tmp, output);
                transform_matrix(TMP, width, input);
                // check condition: game, movable
                game = -1;
                for (i = 0; i < width; i++) for (j = 0; j < width; j++)
                    if (TMP[i][j] == 0)
                        game = 0;
                if (played != -1)
                    for (i = 0; i < width; i++) for (j = 0; j < width; j++)
                        if (TMP[i][j] == win) {
                            game = 1;
                            played = -1;
                        }
                movable = 0;
                for (i = 0; i < width; i++) for (j = 0; j < width; j++)
                    if (TMP[i][j] != GAME[i][j])
                        movable = 1;
                // input is invalid if it neither moves something nor loses game
                if (!movable && !game) break;
                // save result: GAME[][]=TMP[][]
                reprint = 1;
                undo = (game ==1)? 0 : 1;
                for (i = 0; i < width; i++) for (j = 0; j < width; j++) {
                    UNDO[i][j] = GAME[i][j];
                    GAME[i][j] = TMP[i][j];
                }
                score_undo = score;
                score = score_tmp;
                if (!game)
                    add_number(GAME, width);
                break;
            // p:2-b undo
            case 'z':
                if (!undo) break;
                reprint = 1;
                game = undo = 0;
                score = score_undo;
                for (i = 0; i < width; i++) for (j = 0; j < width; j++)
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
                if (played) {
                    stage = 'p';
                    reprint = 1;
                }
                break;
            // m:2-b reset
            case 'r':
                stage = 'p';
                reprint = 1;
                reset_game(GAME, width, &score, &game, &played, &undo);
                break;
            // m:2-c settings
            case 's':
                stage = 's';
                reprint = 1;
                settings[0][1] = width;
                settings[1][1] = win;
                i = 0;
                break;
            // m:2-d exit game
            case 'e':
                stage = 0;
            // m:2-e other input automatically continues input loop
            }
        }
        // stage s: settings
        while (stage == 's') {
            // s:1 print settings screen
            if (reprint) {
                reprint = 0;
                system("cls");

                printf("\n\n      Set width:    ");
                if (i == 0 && settings[0][0] < settings[0][1]) printf("<"); else printf(" ");
                printf("  %4d  ", settings[0][1]);
                if (i == 0 && settings[0][1] < settings[0][2]) printf(">");

                printf("\n Set difficulty:    ");
                if (i == 1 && settings[1][0] < settings[1][1]) printf("<"); else printf(" ");
                printf("  %4d  ", output[settings[1][1]]);
                if (i == 1 && settings[1][1] < settings[1][2]) printf(">");

                printf("\n\n\n Press arrow keys to adjust.\n Press Enter to apply.\n Press ESC to cancel.");
            }
            // s:2 switch input
            input = getch();
            switch (input) {
            // s:2-a apply settings
            case 13:
                stage = 'm';
                reprint = 1;
                width = settings[0][1];
                win = settings[1][1];
                reset_game(GAME, width, &score, &game, &played, &undo);
                break;
            // s:2-b cancel
            case 27:
                stage = 'm';
                reprint = 1;
                break;
            // s:2-c up
            case 72:
                if (i > 0) {
                    i--;
                    reprint = 1;
                }
                break;
            // s:2-d down
            case 80:
                if (i < 1) {
                    i++;
                    reprint = 1;
                }
                break;
            // s:2-e left
            case 75:
                if (settings[i][0] < settings[i][1]) {
                    settings[i][1]--;
                    reprint = 1;
                }
                break;
            // s:2-f right
            case 77:
                if (settings[i][1] < settings[i][2]) {
                    settings[i][1]++;
                    reprint = 1;
                }
                break;
            // s:2-g other input automatically continues input loop
            }
        }
    }
}

void randomize()
{
    time_t t;
    srand((unsigned)time(&t));
}

void add_number(int a[10][10], int width)
{
    int i, j;
    while(1) {
        i = rand()%width;
        j = rand()%width;
        if (a[i][j] == 0) {
            a[i][j] = rand()%2+1;
            break;
        }
    }
}

void reset_game(int a[10][10], int width, int *score, int *game, int *played, int *undo)
{
    int i, j;
    *game = *undo = *played = *score = 0;
    for (i = 0; i < width; i++) for (j = 0; j < width; j++)
        a[i][j] = 0;
    add_number(a, width);
}

void transform_matrix(int a[10][10], int width, char input)
{
    int i, j, tmp;
    switch (input) {
    case 72:
        for (i = 0; i < width; i++) for (j = i+1; j < width; j++) {
            tmp = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = tmp;
        }
        break;
    case 80:
        for (i = 0; i < width; i++) for (j = 0; j < width-1-i; j++) {
            tmp = a[i][j];
            a[i][j] = a[width-1-j][width-1-i];
            a[width-1-j][width-1-i]=tmp;
        }
        break;
    case 77:
        for (i = 0; i < width; i++) for (j = 0; j <= width/2-1; j++) {
            tmp = a[i][j];
            a[i][j] = a[i][width-1-j];
            a[i][width-1-j]=tmp;
        }
    }
}

void line_push_left(int a[10], int width, int *score, int output[])
{
    int i, j;
    for (i = 0; i < width-1; i++)
        if (a[i] != 0) {
            j = i + 1;
            while (a[j] == 0 && j < width)
                j++;
            if (a[i] == a[j] && j < width) {
                a[i]++;
                *score += output[a[i]];
                a[j] = 0;
            }
    }
    for (i = 0; i < width-1; i++) {
        j = i;
        while (a[j] == 0 && j < width)
            j++;
        if (j != i && j < width) {
            a[i] = a[j];
            a[j] = 0;
        }
    }
}
