#include <stdio.h>
#include <cs50.h>

void pyramid(int floor);

int main(void)
{
    int floor;
    do
    {
        floor = get_int("Height: ");
    }
    while (floor < 1 || floor > 8);
    pyramid(floor);
}

void pyramid(int floor)
{
    for (int i = 1; i <= floor; i++)
    {
        for (int j = 0; j <= (floor + i); j++)
        {
            if (j == floor)
            {
                printf("  ");
            }
            else if (j >= (floor - i) && j <= (floor + i))
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }

        }
        printf("\n");
    }
}