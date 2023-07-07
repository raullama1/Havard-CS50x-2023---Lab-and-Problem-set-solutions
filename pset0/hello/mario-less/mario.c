#include <stdio.h>
#include <cs50.h>

void print_pyramids(int height);

int main(void)
{
    int height;

    // Prompt user for pyramid height
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Print the pyramids with a gap
    print_pyramids(height);

    return 0;
}

void print_pyramids(int height)
{
    for (int row = 0; row < height; row++)
    {
        // Print spaces for the left pyramid
        for (int space = 0; space < height - row - 1; space++)
        {
            printf(" ");
        }

        // Print hashes for the left pyramid
        for (int hash = 0; hash < row + 1; hash++)
        {
            printf("#");
        }

        // Print the gap
        printf("  ");

        // Print hashes for the right pyramid
        for (int hash = 0; hash < row + 1; hash++)
        {
            printf("#");
        }

        printf("\n");
    }
}
