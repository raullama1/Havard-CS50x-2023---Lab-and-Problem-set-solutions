#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Maximum number of candidates
#define MAX 9

// Preferences[i][j] is the number of voters who prefer i over j
int preferences[MAX][MAX];

// Pairs[i][j] is true if i is preferred over j
bool locked[MAX][MAX];

// Each pair has a winner and a loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate the array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %d\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear the graph of locked-in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    // Number of voters
    int voter_count = get_int("Number of voters: ");

    // Query for each rank
    int ranks[candidate_count];

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %d: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int candidate_i = ranks[i];
            int candidate_j = ranks[j];
            preferences[candidate_i][candidate_j]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int pair_index = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_index].winner = i;
                pairs[pair_index].loser = j;
                pair_count++;
                pair_index++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_index].winner = j;
                pairs[pair_index].loser = i;
                pair_count++;
                pair_index++;
            }
        }
    }
}

// Sort pairs in decreasing order by the strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            int margin1 = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            int margin2 = preferences[pairs[j + 1].winner][pairs[j + 1].loser] - preferences[pairs[j + 1].loser][pairs[j + 1].winner];

            if (margin1 < margin2)
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        // Check if creating the edge will form a cycle
        if (!creates_cycle(loser, winner))
        {
            locked[winner][loser] = true;
        }
    }
}

// Check if adding an edge between the given candidate pair will form a cycle
bool creates_cycle(int start, int end)
{
    // If there is a direct edge from end to start, a cycle is formed
    if (locked[end][start])
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        // If there is an edge from end to another candidate, check if that candidate forms a cycle
        if (locked[end][i] && creates_cycle(start, i))
        {
            return true;
        }
    }

    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_winner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            // If there is a directed edge pointing to the candidate, they are not the winner
            if (locked[j][i])
            {
                is_winner = false;
                break;
            }
        }

        if (is_winner)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
