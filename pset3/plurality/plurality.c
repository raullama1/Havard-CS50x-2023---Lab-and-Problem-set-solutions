#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9

// Structure to represent a candidate
typedef struct
{
    string name;
    int votes;
}
candidate;

candidate candidates[MAX]; // Array to store candidates
int candidate_count;

bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check if the command-line arguments are provided correctly
    if (argc < 2)
    {
        printf("Usage: %s candidate1 candidate2 ...\n", argv[0]);
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    // Initialize candidates with names from command-line arguments
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Process each vote
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display the winner(s)
    print_winner();
    return 0;
}

bool vote(string name)
{
    // Check if the given name matches any candidate's name
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            // Increase the vote count for the matched candidate
            candidates[i].votes++;
            return true; // Ballot is valid
        }
    }
    return false; // Ballot is invalid
}

void print_winner(void)
{
    int max_votes = 0;

    // Find the maximum number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    }

    // Print the winner(s)
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}
