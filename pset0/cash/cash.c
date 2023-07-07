#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Function prototypes
int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Get the number of cents owed
    int cents = get_cents();

    // Calculate the minimum number of coins needed
    int quarters = calculate_quarters(cents);
    cents -= quarters * 25;

    int dimes = calculate_dimes(cents);
    cents -= dimes * 10;

    int nickels = calculate_nickels(cents);
    cents -= nickels * 5;

    int pennies = calculate_pennies(cents);

    // Print the total number of coins
    int total_coins = quarters + dimes + nickels + pennies;
    printf("%i\n", total_coins);

    return 0;
}

// Prompt the user for a number of cents
int get_cents(void)
{
    int cents;

    // Prompt for input until a valid positive value is entered
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    return cents;
}

// Calculate the number of quarters
int calculate_quarters(int cents)
{
    return cents / 25;
}

// Calculate the number of dimes
int calculate_dimes(int cents)
{
    return cents / 10;
}

// Calculate the number of nickels
int calculate_nickels(int cents)
{
    return cents / 5;
}

// Calculate the number of pennies
int calculate_pennies(int cents)
{
    return cents;
}
