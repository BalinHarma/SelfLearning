/**
 * linked.c
 *
 * week 7 section
 * fall 2013
 *
 * practice using linked lists
 */

#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>

// typedef a node for the linked list
typedef struct node
{
    int n;
    struct node* next;
}
node;

// function prototypes
bool insert_node(int value);
void print_nodes(node* list);
void free_nodes(node* list);

// global variable for the head of the list
node* head = NULL;

int main(void)
{
    // offer the user two options
    while (true)
    {
        printf("Please choose an option (0, 1, 2): ");
        int option = GetInt();
        
        switch (option)
        {
            // quit
            case 0:
                free_nodes(head);
                printf("Goodbye!\n");
                return 0;
            
            // insert int into linked list
            case 1:
                printf("Please enter an int: ");
                int v = GetInt();
                char* success = insert_node(v) ? "was" : "was not";
                printf("The insert %s successful.\n", success);
                break;
            
            // print all ints
            case 2:
                print_nodes(head);
                break;
            
            default:
                printf("Not a valid option.\n");
                break;
        }
    }
}

/**
 * Create a new node for a given value and insert it into a list.
 */
bool insert_node(int value)
{
    // TODO
    // check node head, if
    node* new = malloc(sizeof(node));
    if (new == NULL)
    {
        return false;
    }
    new->n = value;
    node* curr = head;
    node* prev = NULL;
    while (curr != NULL)
    {
        if (curr->n == value)
        {
            return false;
        }
        if (curr->n > value)
        {
            new->next = curr;
            if (prev == NULL)
            {
                head = new;
            }
            else
            {
                prev->next = new;
            }
            return true;
        }
        prev = curr;
        curr = curr->next;
        if (curr == NULL)
        {
            prev->next = new;
            new->next = NULL;
            return true;
        }
    }
    head = new;
    new->next = NULL;
    return true;
}

/**
 * Print out all of the ints in a list.
 */
void print_nodes(node* list)
{
    node* ptr = list;
    while (ptr != NULL)
    {
        printf("%i, ", ptr->n);
        ptr = ptr->next;
    }
    printf("\n");
    return;
}

/**
 * Frees all of the nodes in a list upon exiting the program.
 */
void free_nodes(node* list)
{   
    // TODO
    if (list == NULL)
    {
        return;
    }
    node* prev = list;
    node* curr = prev->next;
    while (prev != NULL)
    {
        free(prev);
        prev = curr;
        if (curr == NULL)
        {
            return;
        }
        curr = curr->next;
    }
}
