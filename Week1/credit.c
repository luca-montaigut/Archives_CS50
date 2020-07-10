/* Resolved by using only the course content, so without array... and it was a pain in the ass ! */
#include <stdio.h>
#include <cs50.h>

bool check_length(long card);
bool luhn(long card);
void check_type(long card);

int main(void)
{
    long card = get_long("Number: ");
    if (check_length(card) && luhn(card))
    {
        check_type(card);
    }
    else
    {
        printf("INVALID\n");
    }
}

bool check_length(long card)
{
    int i = 0;

    while ((card / 10) != 0 || card != 0)
    {
        card = card / 10;
        i++;
    }

    return i >= 13 && i <= 16;
}

bool luhn(long card)
{
    int current_digit;
    int i = 1;
    int sum_simple_digit = 0;
    int sum_double_digit = 0;

    while ((card / 10) != 0 || card != 0)
    {
        current_digit = (card % 10);
        if (i % 2 == 0)
        {
            int double_digit = (current_digit * 2);
            if (double_digit > 9)
            {
                sum_double_digit += (double_digit % 10) + (double_digit / 10) ;
            }
            else
            {
                sum_double_digit += double_digit;
            }
        }
        else
        {
            sum_simple_digit += current_digit;
        }

        card = card / 10;
        i++;
    }
    
    int sum_luhn = sum_double_digit + sum_simple_digit;
    return sum_luhn % 10 == 0;
}

void check_type(long card)
{
    int first_two_digits = 0;

    while ((card / 10) != 0 || card > 9)
    {
        first_two_digits = card % 100;
        card = card / 10;
    }

    if (first_two_digits == 34 || first_two_digits == 37)
    {
        printf("AMEX\n");
    }
    else if (first_two_digits / 10 == 4)
    {
        printf("VISA\n");
    }
    else if (first_two_digits >= 51 && first_two_digits <= 55)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }

}
