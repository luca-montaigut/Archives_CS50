#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool errors_handling(int argc, string argv[]);
bool not_all_alpha(string key);
bool not_only_uniq_char(string key);
void sub_cipher(string key, string plaintext);
void sub_cipher_letter(string key, char letter);

const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, string argv[])
{

    if (errors_handling(argc, argv))
    {
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    sub_cipher(argv[1], plaintext);
    return 0;
}

bool errors_handling(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (not_all_alpha(argv[1]))
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }
    else if (not_only_uniq_char(argv[1]))
    {
        printf("Key must only contain repeated characters.\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

bool not_all_alpha(string key)
{
    bool as_non_alpha = false;
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            as_non_alpha = true;
        }
    }
    return as_non_alpha;
}

bool not_only_uniq_char(string key)
{
    bool as_duplicated_char = false;
    int counter = 0;

    for (int i = 0, n = strlen(alphabet); i < n; i++)
    {
        for (int j = 0, k = strlen(key); j < k; j++)
        {
            if (tolower(alphabet[i]) == tolower(key[j]))
            {
                counter++;
            }
        }
        if (counter > 1)
        {
            as_duplicated_char = true;
        }
        else
        {
            counter = 0;
        }
    }
    return as_duplicated_char;
}

void sub_cipher(string key, string plaintext)
{
    for (int i = 0, plain = strlen(plaintext); i < plain; i++)
    {
        if (isalpha(plaintext[i]))
        {
            sub_cipher_letter(key, plaintext[i]);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}

void sub_cipher_letter(string key, char letter)
{
    for (int i = 0, alpha = strlen(alphabet); i < alpha; i++)
    {
        if (tolower(letter) == tolower(alphabet[i]))
        {
            if (islower(letter))
            {
                printf("%c", tolower(key[i]));
            }
            else if (isupper(letter))
            {
                printf("%c", toupper(key[i]));
            }
        }
    }
}
