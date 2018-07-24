/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */

void swap(int* a, int* b);
 
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if (n > 0)
    {
        for (int i = 0; i < n; i++)
        {
            if (value == values[i])
            {
                return true;
            } 
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    for (int i = 0; i < n; i++)
    {
        int curmin = i;
        for (int j = 0 + i; j < n; j++)
        {
            if (values[curmin] > values[j])
            {
                curmin = j;
            }
        }
        swap(&values[i], &values[curmin]);
    }
    return;
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
