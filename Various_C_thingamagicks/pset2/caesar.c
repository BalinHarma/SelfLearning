/**
 * caesar.c
 *
 * Balint Harmat
 *
 * Implements Caesar's cipher, needs a non negative integer key as argument.
 *
 */

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // check arguments
    if (argc != 2)
    {
        printf("I need a single non negative integer as an argument!");
        return 1;
    }
    int k = atoi(argv[1]);
    if (k < 0)
    {
        printf("I need a single non negative integer as an argument!");
        return 1;
    }
    
    // take user input plaintext
    string ptxt = GetString();
    
    // generate cipher text
    for (int i = 0, n = strlen(ptxt); i < n; i++)
    {
        if (ptxt[i] >= 65 && ptxt[i] <= 90)
        {
            printf("%c", ((ptxt[i] - 65 + k) % 26 + 65));
        }
        else if (ptxt[i] >= 97 && ptxt[i] <= 122)
        {
            printf("%c", ((ptxt[i] - 97 + k) % 26 + 97));
        }
        else
        {
            printf("%C", ptxt[i]);
        }
    }
    printf("\n");
    return 0;
    
}
