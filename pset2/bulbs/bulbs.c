#include <stdio.h>
#include <cs50.h>

// Function to print the bulb emoji based on the given value (0 or 1)
void print_bulb(int bulb)
{
    if (bulb == 0)
    {
        printf("⚫");
    }
    else if (bulb == 1)
    {
        printf("🟡");
    }
}

int main(void)
{
    // Get the message from the user
    string message = get_string("Message: ");

    // Iterate over each character in the message
    for (int i = 0; message[i] != '\0'; i++)
    {
        // Get the ASCII value of the current character
        int ascii_value = (int) message[i];

        // Convert the ASCII value to binary and print the corresponding bulbs
        for (int j = 7; j >= 0; j--)
        {
            int bit = (ascii_value >> j) & 1;
            print_bulb(bit);
        }

        // Print a newline after each "byte" of 8 symbols
        printf("\n");
    }

    return 0;
}
