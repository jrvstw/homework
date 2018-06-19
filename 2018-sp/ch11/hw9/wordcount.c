#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "error: missing argument\n");
        exit(0);
    }

    int pipefd[2];
    pipe(pipefd);

    int ret = fork();
    if (ret == 0) {

        // child 1:
        close(1);
        dup(pipefd[1]);
        close(pipefd[0]);
        close(pipefd[1]);
        char *execv_argv[] = {"/bin/cat", argv[1], NULL};
        execv("/bin/cat", execv_argv);

    } else {
        ret = fork();
        if (ret == 0) {

            //child 2:
            close(0);
            dup(pipefd[0]);
            close(pipefd[0]);
            close(pipefd[1]);
            char *execv_argv[] = {"/usr/bin/wc", NULL};
            execv("/usr/bin/wc", execv_argv);
        }
    }
    return 0;
}
