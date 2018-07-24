/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Global variable, the root of the dictionary trie
node* root = NULL;
int words = 0;

const struct node false_null = { false, {NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL}};

/**
 * Makes a new node,with all its values set to null, and false where applicable
 */
node* makenode(void)
{
    node* ptr = malloc(sizeof(node));
    *ptr = false_null;
    return ptr;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    node* ptr = root;
    int c;
    for (int i = 0; i < 46; i++)
    {
        // if end of word, check the trie for the word's existence
        if (word[i] == '\0')
        {
            if (ptr->word == true)
            {
                return true;
            }
            return false;
        }
        
        // pre-process c to make check case insesnsitive
        c = word[i];
        c-= 96;
        if (c > -32 && c < -5)
        {
            c += 32; 
        }
        else if (c == 0)
        {
            c = 100;
        }
        else if (c == -57)
        {
            c = 0;
        }
        // check if the char is valid for a word in the trie
        if (ptr->next[c] == NULL)
        {
            return false;
        }        
        ptr = ptr->next[c];
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open dictionary
    FILE* fp = fopen(dictionary, "r");
    
    // root
    root = makenode();
    // temp pointer;
    node* curr = root;
    
    // chew through the file char by char
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        // if end of line, reset to the root of the trie, and signal the ending of a word
        if (c != '\n')
        {
            // make the value of c be between 0 and 27 where 0 is the ' and 1 through 27 is "a" to "z"
            c = c - 96;
            if (c == - 57)
            {
                c = 0;
            }
            // create new trie node if needed
            if (curr->next[c] == NULL)
            {
                curr->next[c] = malloc(sizeof(node));
                *curr->next[c] = false_null;
                curr = curr->next[c];
                
            }
            // else just walk to the next
            else
            {
                curr = curr->next[c];
            }
        }
        else
        {
            curr->word = true;
            curr = root;
            words ++;
        }
    }

    fclose(fp);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{

    node* ptr = root;
    return trieunload(ptr);
}

/**
 * Recursive unload function.
 */
bool trieunload(node* ptr)
{
    if (ptr != NULL)
    {
        for (int i = 0; i < 27; i++)
        {
            trieunload(ptr->next[i]);
        }
        free(ptr);
        return true;
    }
    return true;
}
