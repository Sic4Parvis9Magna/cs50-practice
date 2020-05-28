// Implements a dictionary's functionality
#define _XOPEN_SOURCE 700 // or any bigger number
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
    struct node *prev;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char first_letter = word[0];
    if (!isalpha(first_letter))
    {
        return false;
    } else
    {
        int len = strlen(word);
        char *str = malloc(sizeof(char)*len);
        for (int i = 0; i < len; i++)
        {
            str[i] = tolower(word[i]);
            
        }
        int bucket_index =  tolower(str[0]) - 'a';
        node *bucket_element = table[bucket_index];
        while (bucket_element != NULL)
        {
            char * from_element = bucket_element->word;
            if (strcmp(from_element, str) == 0)
            {
                free(str);
                return true;
            }
        }
        free(str);
    }
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char first_letter = word[0];
    if (isalpha(first_letter))
    {
        return tolower(first_letter) - 'a';
    }
    
    return -1;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        return false;
    }

    char * line = NULL;
    size_t len = 0;
    size_t read;

    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        // printf("%s", line);
        int bucket = line[0] - 'a';
        
        node *p  = malloc(sizeof(node));

        if (table[bucket] != NULL)
        {
            node *in_bucket = table[bucket];
            while (in_bucket->next != NULL)
            {
                in_bucket = in_bucket->next;
            }
            in_bucket->next = p;
        } 
        else
        {
            p->prev = NULL;
            table[bucket] = p;
        }

        
        for (int i = 0; i < read; i++)
        {
            p->word[i] = line[i];
        }
        p->word[read] = '\0';
        p->next = NULL;
        free(line);
        line = NULL;
    }
    fclose(fp);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        node *next_node = table[i];
        printf("node=%i :: count=%i\n", i, count);
        if (next_node != NULL)
        {
            while (next_node != NULL)
            {
                count++;
                next_node = next_node->next;
            }
        }
    }
    
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *start_node = table[i];
        if (start_node == NULL)
        {
            continue;
        }
        
        node *current_node = start_node;
        
        while (current_node->next != NULL)
        {
            current_node = current_node->next;
        }

        while (current_node->prev != NULL)
        {
            node * to_clear = current_node;
            current_node = current_node->prev;
            free(to_clear);
        }
        free(start_node);
    }
    
    return true;
}