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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    int Gx[3][3] = {{ -1,  0,  1 }, { -2,  0,  2 }, { -1,  0,  1 }};

    int Gy[3][3] = {{ -1,  -2,  -1 }, { 0,  0,  0 }, { 1,  2,  1 }};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int GxRed = 0, GxGreen = 0, GxBlue = 0;
            int GyRed = 0, GyGreen = 0, GyBlue = 0;
            int newRed = 0, newGreen = 0, newBlue = 0;

            for (int x = -1, a = 0; x < 2; x++, a++)
            {
                for (int y = -1, b = 0; y < 2; y++, b++)
                {
                    if ((i + x >= 0 && i + x < height) && (j + y >= 0 && j + y < width))
                    {
                        GxRed += Gx[a][b] * image[i + x][j + y].rgbtRed;
                        GxGreen += Gx[a][b] * image[i + x][j + y].rgbtGreen;
                        GxBlue += Gx[a][b] * image[i + x][j + y].rgbtBlue;

                        GyRed += Gy[a][b] * image[i + x][j + y].rgbtRed;
                        GyGreen += Gy[a][b] * image[i + x][j + y].rgbtGreen;
                        GyBlue += Gy[a][b] * image[i + x][j + y].rgbtBlue;
                    }
                }
            }

            newRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
            newGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
            newBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));

            newRed = newRed > 255 ? 255 : newRed;
            newGreen = newGreen > 255 ? 255 : newGreen;
            newBlue = newBlue > 255 ? 255 : newBlue;

            copy[i][j].rgbtRed = newRed;
            copy[i][j].rgbtGreen = newGreen;
            copy[i][j].rgbtBlue = newBlue;
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
