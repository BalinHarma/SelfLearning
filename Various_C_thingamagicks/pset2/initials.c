/**
 * initials.c
 *
 * Balint Harmat
 *
 * Prints out the provided name's initials.
 *
 */

#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string name = GetString();
    int length = strlen(name);
    bool tag = 0;
    
    // count prints initials, capitalising lower cases
    for (int i = 0; i < length; i++)
    {
        if (name[i] >= 65 && name[i] <= 90)
        {
            if (!tag)
            {
                printf("%c", name[i]);
                tag = 1;
            }
        }
        else if (name[i] >= 97 && name[i] <= 122)
        {
            if (!tag)
            {
                printf("%c", (name[i] - 32));
                tag = 1;
            }
        }
        else if (name[i] == 32)
        {
            tag = 0;
        }
    }
    printf("\n");
    return 0;
}
