#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>

// Function to change black pixels to the specified color
void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Define the new color values for the non-black pixels
    BYTE red = 0x00;    // Change to the desired red value (0x00 - 0xFF)
    BYTE green = 0x00;  // Change to the desired green value (0x00 - 0xFF)
    BYTE blue = 0xFF;   // Change to the desired blue value (0x00 - 0xFF)

    // Iterate over each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Check if the pixel is black (RGB values are all 0x00)
            if (image[i][j].rgbtRed == 0x00 && image[i][j].rgbtGreen == 0x00 && image[i][j].rgbtBlue == 0x00)
            {
                // Change the pixel's color to the specified values
                image[i][j].rgbtRed = red;
                image[i][j].rgbtGreen = green;
                image[i][j].rgbtBlue = blue;
            }
        }
    }
}
