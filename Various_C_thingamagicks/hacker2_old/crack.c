#define _XOPEN_SOURCE
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <cs50.h>


int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("I need one ciphertext as a single argument!");
        return 1;
    }
    else
    {
        string key = argv[1];
        string salt = "50";
        string cipher = crypt(key, salt);
        printf("%s", cipher);
        return 0;
    }
}
