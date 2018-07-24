#include <stdio.h>

int atoi_50(char* argv);

int main(int argc, char* argv[])
{
    int i = atoi_50(argv[2]);
    printf("%i\n", i);
    return 0;
}

int atoi_50(char* a)
{
    int i = 0;
    for (int j = 0, int n = stlen(a); j < n; j++)
    {
        //minden 10-est beolvasni egyesével, stb stb...
        i = i + j * 10 * (*a[j]);
        //ha a beolvasott \0, akkor van vége  
    }
    return i;
}
