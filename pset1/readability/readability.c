#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");
    
    // # OF WORDS
    int words = 0;
    for(int i = 0; i < strlen(text); i++)
    {
        if(text[i] == ' ')
        {
            words = words + 1;
        }
    }
    printf("# of Words: %i\n", words+1);
    
    // # OF LETTERS
    int letters = 0;
    for(int j = 0; text[j] != '\0'; j++)
    {
        if((text[j] != ' ') && (text[j] != '.') && (text[j] != '!') && (text[j] != '!'))
        {
            letters = letters + 1;
        }
    }
    printf("# of Letters: %i\n", letters);

    // # OF SENTENCES
    int sentences = 0;
    for(int k = 0; k < strlen(text); k++)
    {
        if((text[k] == '.') | (text[k] == '!') | (text[k] == '?'))
        {
            sentences = sentences + 1;
        }
    }
    printf("# of Sentences: %i\n", sentences);
    
    float index = (.0588 * (100 * (float) letters / (float) words)) - (0.296 * (100 * (float) sentences / (float) words)) - 15.8;
    int grade_level = round(index);
    printf("Grade %i\n", grade_level);
}