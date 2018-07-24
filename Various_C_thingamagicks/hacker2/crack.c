/**
 * crack.c
 *
 * Balint Harmat
 *
 * Implements a simple brute force cracking tool, using the supplied dictionary.
 * Needs the ciphertext to be cracked, as the single commandline argument.
 * 
 */

#define _XOPEN_SOURCE
#include <unistd.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // check arguments
    if (argc != 2)
    {
        printf("I need a single ciphertext (13 chars) as an argument!");
        return 1;
    }
    int k = strlen(argv[1]);
    if (k != 13)
    {
        printf("I need a single ciphertext (13 chars) as an argument!");
        return 1;
    }
    // spoon of salt
    char* salt = malloc(3*sizeof(char));
    for (int i = 0; i < 2; i++)
    {
        salt[i] = argv[1][i];
    }
    
    // dictionary
    FILE* dictionary = fopen("/usr/share/dict/words", "r");
    if (dictionary == NULL)
    {
        printf("could not open dictionary at /usr/share/dict/words");
        return 1;
    }
    
    
    return 0;   
}
