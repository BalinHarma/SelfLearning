/*
 *greedy.c
 *
 *Balint Harmath
 *balinth.cg@gmail.com
 *
 *Computes the minimum number of coins 
 *that can make up a user specified amount of dollars and cents.
 */
#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float amount;
    int change = 0, coins = 0;
    // user input
    do
    {
        printf("Amount to be change'd $:");
        amount = GetFloat();
    }
    while (amount < 0);
    // converting to integer
    change = (int) round(amount * 100);
    //coin counting
    while(change > 0)
    {
        if (change >= 25)
        {
            coins = coins + 1;
            change = change - 25;
        }
        else if (change >= 10)
        {
            coins = coins +1;
            change = change -10;
        }
        else if (change >= 5)
        {
            coins = coins + 1;
            change = change -5;
        }
        else
        {
            coins = coins +1;
            change = change -1;
        }
    }
    //answer
    printf("%d\n", coins);
    return 0;
}
 
