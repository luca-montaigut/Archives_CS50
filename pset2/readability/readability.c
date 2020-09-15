#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int coleman_liau_index(float letters, float words, float sentences);
void grade(int index);

int main(void)
{
    string text = get_string("Text: ");
    int letters = 0;
    int words = 1;
    int sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
        else if (isspace(text[i]))
        {
            words++;
        }
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }
    
    int index = coleman_liau_index(letters, words, sentences);
    
    grade(index);
}

int coleman_liau_index(float letters, float words, float sentences)
{
    float index = 0.0588 * (letters / words * 100.00) - 0.296 * (sentences / words * 100.00) - 15.8;
    return round(index);
}

void grade(int index)
{
    if (index <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}