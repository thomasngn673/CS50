#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while(height<1 | height>8);
    
    for(int h = 0; h<height; h++)
    {    
        for(int i = 0; i<(height-(h+1)); i++)
        {
            printf(" ");
        }
        for(int j = 0; j<(h+1); j++)
        {
            printf("#");
        }
        
        printf("  ");
        for(int j = 0; j<(h+1); j++)
        {
            printf("#");
        }
        for(int i = 0; i<(height-(h+1)); i++)
        {
            printf(" ");
        }
        
        printf("\n");
    }
}