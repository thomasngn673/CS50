#include <stdio.h>
#include <cs50.h>
#include <string.h>

#define MAX 9

typedef struct
{
    string name;
    int votes;
}
candidate;

candidate candidates[MAX];
int candidate_count;

bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    if(argc<2)
    {
        printf("Usage: ./plurality [candidate names...]");
        return 1;
    }
    
    candidate_count = argc - 1;
    for(int i = 0; i<candidate_count; i++)
    {
        candidates[i].name = argv[i+1];
        candidates[i].votes = 0;
    }
    
    int voter_count = get_int("Number of voters: ");
    for(int j = 0; j<voter_count; j++)
    {
        string name = get_string("Vote: ");
        if(!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }
    
    print_winner();
}

bool vote(string name)
{
    for(int k = 0; k<candidate_count; k++)
    {
        if(strcmp(candidates[k].name, name) == 0)
        {
            candidates[k].votes++;
            return true;
        }
    }
    return false;
}

void print_winner(void)
{
    int maxvotes = 0;
    for(int l = 0; l<candidate_count; l++)
    {
        if(candidates[l].votes > maxvotes)
        {
            maxvotes = candidates[l].votes;
        }
    }
    
    for(int l = 0; l<candidate_count; l++)
    {
        if(candidates[l].votes == maxvotes)
        {
            printf("Winner(s): %s\n", candidates[l].name);
        }
    }
    return;
}