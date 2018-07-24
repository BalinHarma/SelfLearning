/**
 *credit.c
 *
 *Harmat Bálint
 *
 *Checks for the validity of the user provided card number.
 */

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long long number = 0;
    // ask for card number
    do
    {
        printf("Number:");
        number = GetLongLong();
    }
    while (number < 0);
    
    // digit counter
    int x = 0;
    
    while (number - pow(10, x) >= 0)
    {
        x++;
    }
    // printf("%i\n", i); // control
    
    int digits[x];
    int y = x;
    while (number > 0)
    {
        digits[y-1] = number % 10;
        number /= 10;
        y--;
    }
    
    int product = 0;
    for (int i = x - 2; i > 0; i = i - 2)
    {
        product = product + (digits[i] * 2) % 10;
        product = product + ((digits[i] * 2) / 10) % 10;
    }
    for (int i = x - 1; i >= 0; i = i - 2)
    {
        product = product + digits[i];
    }
    if (product % 10 != 0)
    {
        printf("INVALID\n");
    }
    else if (digits[0] == 3 && (digits[1] == 4 || digits[1] == 7))
    {
        printf("AMEX\n");
    }
    else if (digits[0] == 5 && (digits[1] > 0 && digits[1] < 6))
    {
        printf("MASTERCARD\n");
    }
    else if (digits[0] == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}
