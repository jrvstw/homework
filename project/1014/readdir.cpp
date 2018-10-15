#include <iostream>
#include <dirent.h>

using namespace std;

int main(int argc, char *argv[])
{
    char *input = argv[1];
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(input)) == NULL) {
        cerr << "invalid directory." << endl;
        exit(0);
    }

    while ((ent = readdir(dir)) != NULL)
        cout << ent->d_name << endl;

    closedir(dir);

    return 0;
}
