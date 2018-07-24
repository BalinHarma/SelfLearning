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
int binse(int value, int values[], int a, int b);

bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if (n > 0)
    {
        if (binse(value, values, 0, n) == 0)
        {
            return true;
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

int binse(int value, int values[], int a, int b)
{
    if (a + b < 1)
    {
        return 1;
    }
    else if (b - a == 1)
    {
        if (values[a] == value || values[b] == value)
        {
            return 0;
        }
        return 1;
    }
    else if (values[(a + b) / 2] == value)
    {
        return 0;
    }
    else if (values[(a + b) / 2] < value)
    {
        return binse(value, values, (a + b) / 2, b);
    }
    return binse(value, values, a, (a + b) / 2);
}
