#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(3);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with 'generations'
person *create_family(int generations)
{
    // Allocate memory for a new person
    person *p = malloc(sizeof(person));

    // If there are still generations left to create
    if (generations > 1)
    {
        // Create two new parents for the current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // Set parent pointers for the current person
        p->parents[0] = parent0;
        p->parents[1] = parent1;

        // Randomly assign the current person's alleles based on the alleles of their parents
        p->alleles[0] = parent0->alleles[rand() % 2];
        p->alleles[1] = parent1->alleles[rand() % 2];
    }
    else
    {
        // Set parent pointers to NULL for the current person (oldest generation)
        p->parents[0] = NULL;
        p->parents[1] = NULL;

        // Randomly assign alleles for the oldest generation
        p->alleles[0] = random_allele();
        p->alleles[1] = random_allele();
    }

    // Return the newly created person
    return p;
}

// Free 'p' and all ancestors of 'p'
void free_family(person *p)
{
    // Handle the base case: if 'p' is NULL, there's nothing to free, so return
    if (p == NULL)
    {
        return;
    }

    // Free parents recursively
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // Free the child
    free(p);
}

// Print each family member and their alleles
void print_family(person *p, int generation)
{
    // Handle the base case: if 'p' is NULL, return
    if (p == NULL)
    {
        return;
    }

    // Print indentation based on the generation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print the person and their blood type
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Recursively print parents
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Generate a random blood type allele (A, B, or O)
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
