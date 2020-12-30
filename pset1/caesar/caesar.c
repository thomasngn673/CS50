#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Please enter an input key value: ");
    }

    string keyword = argv[1];
    int keyword_new = atoi(keyword);
    
    string plaintext = get_string("Input plaintext: ");
    printf("plaintext: %s\n", plaintext);
    printf("ciphertext: ");
    for(int i = 0; i<strlen(plaintext); i++)
    {
        printf("%c", plaintext[i] + keyword_new);
    }
}