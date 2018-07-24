/**
 * vigenere.c
 *
 * Balint Harmat
 *
 * Implements Vigenere's cipher, needs a single alphabetical keyword as 
 *an argument.
 *
 */

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // process arguments
    if (argc != 2)
    {
        printf("I need a single alphabetical keyword as an argument!");
        return 1;
    }
    int k = strlen(argv[1]);
    int kword[k];
    for (int i = 0; i < k; i++)
    {
        if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
        {
            kword[i] = argv[1][i] - 'A';
        }
        else if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
        {
            kword[i] = argv[1][i] - 'a';
        }
        else
        {
            printf("I need a single alphabetical keyword as an argument!");
            return 1;
        }
    }
    // process user input plaintext
    string ptxt = GetString();
    for (int i = 0, n = strlen(ptxt), j = 0; i < n; i++)
    {
        if (ptxt[i] >= 'A' && ptxt[i] <= 'Z')
        {
            ptxt[i] = (ptxt[i] + kword[j % k] - 'A') % 26 + 'A';
            j++;
            printf("%c", ptxt[i]);
        }
        else if (ptxt[i] >= 'a' && ptxt[i] <= 'z')
        {
            ptxt[i] = (ptxt[i] + kword[j % k] - 'a') % 26 + 'a';
            j++;
            printf("%c", ptxt[i]);
        }
        else
        {
            printf("%c", ptxt[i]);
        }
    }
    printf("\n");
    return 0;   
}
