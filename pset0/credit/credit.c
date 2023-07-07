#include <stdio.h>
#include <cs50.h>

int count_digits(long long number);
bool is_valid_checksum(long long number);
string get_card_type(long long number);

int main(void)
{
    // Prompt user for credit card number
    long long number = get_long_long("Number: ");

    // Check if the number has a valid checksum
    if (is_valid_checksum(number))
    {
        // Determine the card type
        string card_type = get_card_type(number);
        printf("%s\n", card_type);
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

int count_digits(long long number)
{
    int count = 0;
    while (number > 0)
    {
        number /= 10;
        count++;
    }
    return count;
}

bool is_valid_checksum(long long number)
{
    int sum = 0;
    bool multiply = false;

    while (number > 0)
    {
        int digit = number % 10;

        if (multiply)
        {
            digit *= 2;
            sum += digit % 10 + digit / 10;
        }
        else
        {
            sum += digit;
        }

        multiply = !multiply;
        number /= 10;
    }

    return sum % 10 == 0;
}

string get_card_type(long long number)
{
    int digits = count_digits(number);

    if (digits == 15)
    {
        int prefix = number / 10000000000000;
        if (prefix == 34 || prefix == 37)
        {
            return "AMEX";
        }
    }
    else if (digits == 16)
    {
        int prefix = number / 100000000000000;
        if (prefix >= 51 && prefix <= 55)
        {
            return "MASTERCARD";
        }
        else if (prefix / 10000 == 4) // Updated condition for VISA
        {
            return "VISA";
        }
    }

    return "INVALID";
}
