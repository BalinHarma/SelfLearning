/**
 *mario.c
 *
 *Harmat Bálint
 *
 *Prints a pyramid.
 */

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    
    // ask for height
    do
    {
        printf("height:");
        height = GetInt();
    }
    while (height > 23 || height < 0);
    
    // write out the pyramid
    for (int i = 0; i < height; i++)
    {
        for (int j = 1; j < height - i; j++)
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("#");
        printf("\n");
    }
}
