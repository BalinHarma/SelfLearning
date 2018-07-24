/*
 *caesar.c
 *
 *Balint Harmat
 *balinth.cg@gmail.com
 *
 *Encrypts the given string, with rot k, where k is the first argument.
 */
 
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //check for correct argument
    if (argc == 1)
    {
        printf("I am designed to work with a single non-negative integer argument!\n");
        return 1;
    }
    
    int k = atoi(argv[1]);
    if (argc != 2 || k < 1)
    {
        printf("I am designed to work with a single non-negative integer argument!\n");
        return 1;
    }
    else
    {
        //get plaintext
        string p = GetString();
        //encrypt p
        for (int i = 0, n = strlen(p); i < n; i++)
        {
            int charnum = (int) p[i];
            
            if (charnum >= 65 && charnum <= 90)
            {
                printf("%c", (charnum - 65 + k) % 26 + 65);
            }
            else if (charnum >= 97 && charnum <= 122)
            {
            printf("%c", (charnum - 97 + k) % 26 + 97);
            }
            else
            {
                printf("%c", p[i]);
            }
        }
        printf("\n"); 
    }
    return 0;
}
