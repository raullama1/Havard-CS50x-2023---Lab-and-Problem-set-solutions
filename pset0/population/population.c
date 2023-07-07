#include <stdio.h>

int main(void)
{
    // Prompt the user for the starting population size
    int startSize;
    do
    {
        printf("Start size: ");
        scanf("%i", &startSize);
    }
    while (startSize < 9);

    // Prompt the user for the ending population size
    int endSize;
    do
    {
        printf("End size: ");
        scanf("%i", &endSize);
    }
    while (endSize < startSize);

    // Calculate the number of years required for the population to reach the end size
    int years = 0;
    int population = startSize;
    while (population < endSize)
    {
        int births = population / 3;
        int deaths = population / 4;
        population += births - deaths;
        years++;
    }

    // Print the number of years required
    printf("Years: %i\n", years);

    return 0;
}
