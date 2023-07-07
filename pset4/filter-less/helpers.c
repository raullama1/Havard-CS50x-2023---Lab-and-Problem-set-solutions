#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average of the RGB values
            BYTE gray = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Set the RGB values to the average
            image[i][j].rgbtRed = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtBlue = gray;
        }
    }
}

// Convert image to sepia tone
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Apply sepia formula to each RGB value
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            // Cap the values at 255 if they exceed it
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels from left with pixels from right
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image using box blur algorithm
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the original image
    RGBTRIPLE copy[height][width];

    // Copy the image to the copy array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Apply the box blur algorithm to each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redSum = 0, greenSum = 0, blueSum = 0;
            int count = 0;

            // Iterate over the pixels in the surrounding 3x3 box (including the current pixel)
            for (int row = -1; row <= 1; row++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    int newRow = i + row;
                    int newCol = j + col;

                    // Check if the new position is within the image bounds
                    if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width)
                    {
                        // Accumulate the RGB values of the surrounding pixels
                        redSum += copy[newRow][newCol].rgbtRed;
                        greenSum += copy[newRow][newCol].rgbtGreen;
                        blueSum += copy[newRow][newCol].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate the average RGB values
            image[i][j].rgbtRed = round(redSum / (float)count);
            image[i][j].rgbtGreen = round(greenSum / (float)count);
            image[i][j].rgbtBlue = round(blueSum / (float)count);
        }
    }
}
