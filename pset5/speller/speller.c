// Implements a spell-checker

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "dictionary.h"

// Default dictionary
#define DICTIONARY "dictionaries/large"

// Prototype
double calculate(const struct rusage *b, const struct rusage *a);

int main(int argc, char *argv[])
{
    // Check for correct number of command-line arguments
    if (argc < 2 || argc > 3)
    {
        printf("Usage: ./speller [DICTIONARY] text\n");
        return 1;
    }

    // Structures for timing
    struct rusage before, after;

    // Benchmarks - start timer
    getrusage(RUSAGE_SELF, &before);

    // Determine dictionary to use
    char *dictionary = (argc == 3) ? argv[1] : DICTIONARY;

    // Load dictionary
    bool loaded = load(dictionary);
    if (!loaded)
    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }

    // Remember dictionary load time
    double timeLoad = calculate(&before, &after);

    // Try to open text
    char *text = (argc == 3) ? argv[2] : argv[1];
    FILE *file = fopen(text, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", text);
        unload();
        return 1;
    }

    // Prepare to report misspellings
    printf("\nMISSPELLED WORDS:\n\n");

    // Prepare to spell-check
    char word[LENGTH + 1];
    int index = 0;
    int misspellings = 0;
    int words = 0;
    char c;

    // Spell-check each word in text
    while ((c = fgetc(file)) != EOF)
    {
        // Allow alphabetical characters and apostrophes (for possessives and contractions)
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Append character to word
            word[index] = tolower(c);
            index++;

            // Ignore alphabetical strings too long to be words
            if (index > LENGTH)
            {
                // Consume remainder of alphabetical string
                while ((c = fgetc(file)) != EOF && isalpha(c));

                // Prepare for new word
                index = 0;
            }
        }
        // Ignore words with numbers (like MS Word can)
        else if (isdigit(c))
        {
            // Consume remainder of alphanumeric string
            while ((c = fgetc(file)) != EOF && isalnum(c));

            // Prepare for new word
            index = 0;
        }
        // We must have found a whole word
        else if (index > 0)
        {
            // Terminate current word
            word[index] = '\0';

            // Update counter
            words++;

            // Check word's spelling
            bool misspelled = !check(word);
            if (misspelled)
            {
                printf("%s\n", word);
                misspellings++;
            }

            // Prepare for next word
            index = 0;
        }
    }

    // Close file
    fclose(file);

    // Benchmarks - end timer
    getrusage(RUSAGE_SELF, &after);

    // Calculate total time
    double timeTotal = calculate(&before, &after);

    // Report benchmarks
    printf("\nWORDS MISSPELLED:     %d\n", misspellings);
    printf("WORDS IN DICTIONARY:  %d\n", size());
    printf("WORDS IN TEXT:        %d\n", words);
    printf("TIME IN load:         %.2f\n", timeLoad);
    printf("TIME IN check:        %.2f\n", timeTotal - timeLoad);
    printf("TIME IN TOTAL:        %.2f\n\n", timeTotal);

    // Unload dictionary
    bool unloaded = unload();
    if (!unloaded)
    {
        printf("Could not unload %s.\n", dictionary);
        return 1;
    }

    // Success
    return 0;
}

// Returns number of seconds between b and a
double calculate(const struct rusage *b, const struct rusage *a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec))) /
                1000000.0);
    }
}
