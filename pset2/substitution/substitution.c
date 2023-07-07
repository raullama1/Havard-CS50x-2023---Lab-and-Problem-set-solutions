#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt a character based on the given key
char encrypt_char(char c, string key)
{
    // Check if the character is alphabetical
    if (isalpha(c))
    {
        // Get the index of the character in the alphabet
        int index = toupper(c) - 'A';

        // Get the corresponding character from the key
        char encrypted_char = key[index];

        // Preserve the case of the original character
        if (isupper(c))
        {
            return toupper(encrypted_char);
        }
        else
        {
            return tolower(encrypted_char);
        }
    }
    else
    {
        return c;
    }
}

int main(int argc, string argv[])
{
    // Check the command-line argument count
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Get the key from the command-line argument
    string key = argv[1];

    // Check the length of the key
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check if the key contains non-alphabetic characters or repeated characters
    bool valid_key = true;
    bool seen[26] = {false};
    for (int i = 0; i < 26; i++)
    {
        char c = toupper(key[i]);

        if (!isalpha(c))
        {
            valid_key = false;
            break;
        }

        if (seen[c - 'A'])
        {
            valid_key = false;
            break;
        }

        seen[c - 'A'] = true;
    }

    if (!valid_key)
    {
        printf("Invalid key.\n");
        return 1;
    }

    // Get the plaintext from the user
    string plaintext = get_string("plaintext: ");

    // Encrypt each character in the plaintext
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char encrypted_char = encrypt_char(plaintext[i], key);
        printf("%c", encrypted_char);
    }
    printf("\n");

    return 0;
}
