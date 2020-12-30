#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            int b = image[i][j].rgbtBlue;
            int g = image[i][j].rgbtGreen;
            int r = image[i][j].rgbtRed;
            float average = (float)(b + g + r) / 3.00;
            int avg = round(average);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width/2; j++)
        {
            // Right side
            // If this is placed under "left side" data, its image[i][j] would be based on "left side" data
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            // Left side
            image[i][j].rgbtRed = image[i][width-j-1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width-j-1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width-j-1].rgbtBlue;

            // Right side
            image[i][width-j-1].rgbtRed = red;
            image[i][width-j-1].rgbtGreen = green;
            image[i][width-j-1].rgbtBlue = blue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            float counter = 0.00;

            for(int k=-1; k<2; k++)
            {
                for(int h=-1; h<2; h++)
                {
                    if(k+i<0||k+i>height-1||j+h<0||j+h>width-1)
                    {
                        continue;
                    }
                    sumRed = sumRed + image[i+k][j+h].rgbtRed;
                    sumGreen = sumGreen + image[i+k][j+h].rgbtGreen;
                    sumBlue = sumBlue + image[i+k][j+h].rgbtBlue;
                    counter++;
                }
            }

            copy[i][j].rgbtRed = round(sumRed/counter);
            copy[i][j].rgbtGreen = round(sumGreen/counter);
            copy[i][j].rgbtBlue = round(sumBlue/counter);
        }
    }

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
        }
    }
    return;
}

// Limit RGB value overflow
int limit(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    return RGB;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    float redX;
    float redY;
    float greenX;
    float greenY;
    float blueX;
    float blueY;
    float modifierX;
    float modifierY;
    
    RGBTRIPLE copy[height][width];
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            redX = 0.0;
            redY = 0.0;
            blueX = 0.0;
            blueY = 0.0;
            greenX = 0.0;
            greenY = 0.0;
            modifierX = 0.0;
            modifierY = 0.0;
            
            for(int di=-1; di<2; di++)
            {
                if(di+i<0||di+i>height-1)
                {
                    continue;
                }
                for(int dj=-1; dj<2; dj++)
                {
                    if(j+dj<0||j+dj>width-1)
                    {
                        continue;
                    }
                    
                    modifierX = (di + 1 * di - di * abs(dj));
                    modifierY = (dj + 1 * dj - dj * abs(di));
                    
                    redX += modifierX * image[i+di][j+dj].rgbtRed;
                    greenX += modifierX * image[i+di][j+dj].rgbtGreen;
                    blueX += modifierX * image[i+di][j+dj].rgbtBlue;
                    
                    redY += modifierY * image[i+di][j+dj].rgbtRed;
                    greenY += modifierY * image[i+di][j+dj].rgbtGreen;
                    blueY += modifierY * image[i+di][j+dj].rgbtBlue;
                }
            }
            
            copy[i][j].rgbtRed = limit(round(sqrt(redX*redX + redY*redY)));
            copy[i][j].rgbtGreen = limit(round(sqrt(greenX*greenX + greenY*greenY)));
            copy[i][j].rgbtBlue = limit(round(sqrt(blueX*blueX + blueY*blueY)));
            
        }
    }
    
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
        }
    }
    return;
}
