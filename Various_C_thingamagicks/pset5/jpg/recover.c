/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

bool check(BYTE* buffer, BYTE* cue1, BYTE* cue2);

int main(void)
{
    // int pointers, variables
    FILE* file = fopen("card.raw", "r");
    FILE* outfile;
    BYTE cue1[4] = {0xff, 0xd8, 0xff, 0xe0};
    BYTE cue2[4] = {0xff, 0xd8, 0xff, 0xe1};
    BYTE buffer[512];
    char* filename = malloc(sizeof(char)*8);
    int n = 0;
    
    // error checking
    if (file == NULL)
    {
        printf("Could not open card.raw.\n");
        return 2;
    }
    
    while (file != NULL)
    {
        // read block of 512 byts into buffer
        {
            fread(&buffer, sizeof(BYTE), 512, file);
        }
        // if buffer contains jpeg start pattern, close prev jpeg, and open new one
        if (check(buffer, cue1, cue2))
        {
            if (n > 0)
            {
                fclose(outfile);
            }
            sprintf(filename, "%0*i.jpg", 3, n);
            outfile = fopen(filename, "w");
            fwrite(buffer, sizeof(BYTE), 512, outfile);
            n++;
        }
        // else if EOF close last file, free heap, and return
        else if (feof(file) != 0)
        {
            fclose(outfile);
            fclose(file);
            free(filename);
            return 0;
        }
        // else if an out file was already opened, write in the contents of buffer
        else if (n > 0)
        {
            fwrite(buffer, sizeof(BYTE), 512, outfile);
        }
        
    }
    // return error if coudnt open forensic image
    fclose(file);
    free(filename);
    return 1;
}
// checks for JPEG patterns
bool check(BYTE* buffer, BYTE* cue1, BYTE* cue2)
{
    for (int i = 0; i < 4; i++)
    {
        if (buffer[i] != cue1[i] && buffer[i] != cue2[i])
        {
            return false;
        }
    }
    return true;
}
