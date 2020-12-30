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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // use sepia formula
            int sepR = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepG = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepB = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // make sure it doesnt go over 255
            image[i][j].rgbtRed = (sepR>255) ? 255 : sepR;
            image[i][j].rgbtGreen = (sepG>255) ? 255 : sepG;
            image[i][j].rgbtBlue = (sepB>255) ? 255 : sepB;
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
