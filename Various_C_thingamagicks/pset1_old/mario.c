/**
 *mario.c
 *
 *Balint Harmath
 *balinth.cg@gmail.com
 *
 *prints a half-pyramid based on user input.
 */
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    height = -1;
    //user input
    while (height < 0 || height > 23)
    {
        printf("Enter a non negative height, no higher than 23:");
        height = GetInt();
    }
    // loop for the rows
    for (int i = 0; i < height; i++)
    {
        // loop of the columns
        for (int j = 0; j < height + 1; j++)
        {
            if (j < height - i - 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    } 
    return 0;
}
