#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = round((float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
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
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            sepiaRed = sepiaRed > 255 ? 255 : sepiaRed;
            sepiaGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            sepiaBlue = sepiaBlue > 255 ? 255 : sepiaBlue;

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][width - 1 - j];
        }
    }

    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int averageRed = 0;
            int averageGreen = 0;
            int averageBlue = 0;
            int counter = 0;
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if ((i + x >= 0 && i + x < height) && (j + y >= 0 && j + y < width))
                    {
                        averageRed += image[i + x][j + y].rgbtRed;
                        averageGreen += image[i + x][j + y].rgbtGreen;
                        averageBlue += image[i + x][j + y].rgbtBlue;
                        counter++;
                    }
                }
            }
            copy[i][j].rgbtRed = round((float)averageRed / (float)counter);
            copy[i][j].rgbtGreen = round((float)averageGreen / (float)counter);
            copy[i][j].rgbtBlue = round((float)averageBlue / (float)counter);
        }
    }

    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            image[i][j] = copy[i][j];
        }
    }

    return;
}
