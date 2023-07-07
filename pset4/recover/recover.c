#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for correct number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        printf("where IMAGE is the name of the forensic image.\n");
        return 1;
    }

    // Open the forensic image file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open %s for reading.\n", argv[1]);
        return 1;
    }

    // Create a buffer to read 512 bytes at a time
    BYTE buffer[512];

    // Counter to keep track of the number of JPEG files found
    int jpegCount = 0;

    // File to write the recovered JPEGs
    FILE *jpegFile = NULL;

    // Read 512 bytes at a time until the end of the file
    while (fread(buffer, sizeof(BYTE), 512, file) == 512)
    {
        // Check if the current block starts with the JPEG signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close the previous JPEG file (if any)
            if (jpegFile != NULL)
            {
                fclose(jpegFile);
            }

            // Create a new JPEG file with a numbered filename
            char filename[8];
            sprintf(filename, "%03i.jpg", jpegCount);
            jpegFile = fopen(filename, "w");
            jpegCount++;
        }

        // Write the current block to the JPEG file
        if (jpegFile != NULL)
        {
            fwrite(buffer, sizeof(BYTE), 512, jpegFile);
        }
    }

    // Close the last JPEG file
    if (jpegFile != NULL)
    {
        fclose(jpegFile);
    }

    // Close the forensic image file
    fclose(file);

    return 0;
}
