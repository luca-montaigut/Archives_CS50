#include <stdio.h>
#include <cs50.h>
#include <math.h>

void get_change(float cents);

int main(void)
{
    float dollars;
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);
    int cents = round(dollars * 100);
    get_change(cents);

}

void get_change(float cents)
{
    int counter = 0;
    while (cents > 0)
    {
        if (cents >= 25)
        {
            cents = cents - 25;
            counter++;
        }
        else if (cents >= 10)
        {
            cents = cents - 10;
            counter++;
        }
        else if (cents >= 5)
        {
            cents = cents - 5;
            counter++;
        }
        else
        {
            cents = cents - 1;
            counter++;
        }
    }
    printf("%i\n", counter);
}
