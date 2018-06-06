int square(int input)
{
    return input * input;
}

void main()
{
    int a;
    a = 0;
    int i;
    for (i = 0; i < 30; i = i + 1) {
        if (i % 5 == 0)
            continue;
        a = a + square(i);
        if (a > 500)
            break;
    }
    while (i > 0) {
        printf("%d ", i);
        i = i - 1;
    }
    return;
}

