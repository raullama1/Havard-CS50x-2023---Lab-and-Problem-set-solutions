#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>

// Array representing the point values for each letter
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Function to compute the score of a word
int compute_score(string word);

int main(void)
{
    // Prompt players for their words
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Compute scores for both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Compare scores and determine the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

    return 0;
}

int compute_score(string word)
{
    int score = 0;

    // Iterate over each character in the word
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // Convert the character to uppercase for indexing in POINTS array
        char c = toupper(word[i]);

        // Check if the character is a letter
        if (isalpha(c))
        {
            // Calculate the score by adding the corresponding value from POINTS array
            score += POINTS[c - 'A'];
        }
    }

    return score;
}
