// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Initiate has value
// Unsigned int for positive values
unsigned int hash_value;

// Initialize number of words in hash table
unsigned int word_count;

// Hash table
node* table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // hash the word to get hash_value
    hash_value = hash(word);
    
    // Access linked list at hash_value index in the hash table
    // Assign address at key to node: cursor 
    node* cursor = table[hash_value];
    
    // while address is not NULL, check if words are same (case insensitive)
    while(cursor != NULL) 
    {
        // if inputted word is the same as the value of the node.word value, return true
        if(strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        
        // set new cursor address to the "next" address of the old cursor address
        // move down the linked list until NULL is reached
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;
    while((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) +c;
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE* filePtr = fopen(dictionary, "r");
    if(filePtr==NULL)
    {
        return false;
    }
    
    // Set every index in hash table == NULL
    for(int i=0; i<N; i++)
    {
        table[i] = NULL;
    }
    
    // buffer space for word
    char tempWord[LENGTH+1];
    
    while(fscanf(filePtr, "%s\n", tempWord) != EOF)
    {
        // Goal: put word into table
        // table is type: node --> 
        // create temporary node and load tempWord onto it -->
        // put temporary node into table
        node* tempNode = malloc(sizeof(node));
        if(tempNode == NULL)
        {
            return false;
        }
        
        // change "value" of char in node with dictionary word
        // tempNode is an address (*tempNode goes to the address it is pointing to, which is the node)
        strcpy(tempNode->word, tempWord);
        
        // Hash word for hash_value
        hash_value = hash(tempWord);
        
        // TABLE IS A TABLE FULL OF TEMPNODE ADDRESSES
        // tempNode (address) points to an actual node with value tempWord, and 'next' pointer address
        
        // set new pointer
        tempNode->next = table[hash_value];
        // set head to new pointer
        table[hash_value] = tempNode;
        word_count++;
    }
    // close file
    fclose(fileptr);
    
    // dictionary is finished loading
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if(word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over every bunker
    for(int i=0; i<N; i++)
    {
        // set cursor to this bunker's location in the table
        node* cursor = table[i];
        
        // free cursor if not NULL (while(NULL) will break the loop)
        while(cursor)
        {
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        
        // If last bunker in table and cursor is NULL
        if(i == N-1 && cursor == NULL)
        {
            return true;
        }
    }
    return false;
}
