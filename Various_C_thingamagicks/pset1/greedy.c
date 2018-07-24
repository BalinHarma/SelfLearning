/**
 *greedy.c
 *
 *Harmat Bálint
 *
 *Spits out the minimum number of coins needed for the provided change.
 */

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // define coins
    int quarters = 25;
    int dimes = 10;
    int nickels = 5;
    int pennies = 1;
    int coins = 0;
    
    float change;
    
    // ask for change
    do
    {
        printf("How much change is owed?\n");
        change = GetFloat();
    }
    while (change < 0 );
    
    // convert to cents
    int cents = (int) round(change * 100);
    
    // count coins
    while (cents >= quarters)
    {
        cents = cents - quarters;
        coins++;
    }
    while (cents >= dimes)
    {
        cents = cents - dimes;
        coins++;
    }
    while (cents >= nickels)
    {
        cents = cents - nickels;
        coins++;
    }
    while (cents >= pennies)
    {
        cents = cents - pennies;
        coins++;
    }
    printf("%i\n", coins);
}
