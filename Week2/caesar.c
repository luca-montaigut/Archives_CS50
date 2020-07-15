#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool not_a_number(string user_cmd);
void cipher(int key, string plaintext);
void cipher_lower(int key, char letter);
void cipher_upper(int key, char letter);

int main(int argc, string argv[])
{
    if (argc != 2 || not_a_number(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]) % 26;

    string plaintext = get_string("plaintext: ");
    cipher(key, plaintext);
}

bool not_a_number(string user_cmd)
{
    bool not_only_digit = false;
    for (int i = 0, n = strlen(user_cmd); i < n; i++)
    {
        if (!isdigit(user_cmd[i]))
        {
            not_only_digit = true;
        }
    }
    return not_only_digit;
}

void cipher(int key, string plaintext)
{
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (islower(plaintext[i]))
        {
            cipher_lower(key, plaintext[i]);
        }
        else if (isupper(plaintext[i]))
        {
            cipher_upper(key, plaintext[i]);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}

void cipher_lower(int key, char letter)
{
    if (letter + key > 122)
    {
        int tmp_key = letter + key - 122;
        printf("%c", 96 + tmp_key);
    }
    else
    {
        printf("%c", letter + key);
    }
}

void cipher_upper(int key, char letter)
{
    if (letter + key > 90)
    {
        int tmp_key = letter + key - 90;
        printf("%c", 64 + tmp_key);
    }
    else
    {
        printf("%c", letter + key);
    }
}
