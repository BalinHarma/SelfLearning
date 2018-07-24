/*
 *vigenere.c
 *
 *Balint Harmat
 *balinth.cg@gmail.com
 *
 *Encrypts the given string, with vigenere, where k keyword is the first argument.
 */
 
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //check for argument number
    if (argc != 2)
    {
        printf("I am designed to work with a single keyword argument!\n");
        return 1;
    }
    else
    {
        //numberizes keyword
        int k[strlen(argv[1])];
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            k[i] = (int) argv[1][i] - 97;
            if (k[i] > -33 && k[i] < -6)
            {
                k[i] = k[i] + 32;
            }
            if (k[i] < 0 || k[i] > 25)
            {
                printf("I am designed to work with alphabetical arguments.!\n");
                return 1; 
            }
        }
        //plaintext input
        string p = GetString();
        //encrypts p with k[j]
        int j = 0;
        for (int i = 0, n = strlen(p); i < n; i++)
        {
            int charnum = (int) p[i];
            if (charnum >= 65 && charnum <= 90)
            {
                printf("%c", (charnum - 65 + k[j]) % 26 + 65);
                j = (j + 1) % strlen(argv[1]);
            }
            else if (charnum >= 97 && charnum <= 122)
            {
                printf("%c", (charnum - 97 + k[j]) % 26 + 97);
                j = (j + 1) % strlen(argv[1]);
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
