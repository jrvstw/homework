int main()
{
    int i = 0;
    int count_char = 0;
    char a[20] = "TestString.";

    while (i < 20) {
        if (64 < a[i] && a[i] < 91 || 113 > a[i] && a[i] > 96)
            /* letter in ASCII */
            count_char = count_char + 1;
        else if (a[i] == 46)
            /* period in ASCII */
            break;
    }
}
