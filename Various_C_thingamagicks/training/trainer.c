
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int* getAge(void);

int main(int argc, char* argv[])
{
    //check argc
    if (argc !=  2)
    {
        printf("Usage: ""./trainer n"", where n is the number of dolphins.\n");
        return 1;
    }
    int n = atoi(argv[1]);
    if (n < 1)
    {
        printf("Usage: ""./trainer n"", where n is the number of dolphins.\n");
        return 2;
    }
    int* dolphins[n];
    for (int i = 0; i < n; i++)
    {
        dolphins[i] = getAge();
    }
    for (int i = 0, oldest = 0; i < n; i++)
    {
        if (*dolphins[oldest] < *dolphins[i])
        {
            oldest = i;
        }
        if (i == n-1)
        {
            printf("The oldest dolphin is %i years old\n", *dolphins[oldest]);
            return 0; 
        }
    }
    
    //print out age of oldest dolphin
    
}

int* getAge(void)
{
    int* age = malloc(sizeof(int));
    do
    {
       printf("how old is the dolphin? : ");
       *age = GetInt();
    }
    while (*age < 1);
    return age;
}

