#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

char *substitute(string key, string plain_text);
bool valid_key(string key);
bool in_array(int val, int arr[], int len);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    if (strlen(key) != 26 || !valid_key(key))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string value = get_string("plaintext: ");
    char *result = substitute(key, value);
    printf("ciphertext: ");

    int len = strlen(value);

    for (int i = 0; i < len; i++)
    {
        printf("%c", *(result + i));
    }
    printf("\n");
}

char *substitute(string key, string plain_text)
{
    int len = strlen(plain_text);

    char *result = malloc((len + 1) * sizeof(char));
    *(result + len) = '\0';

    strcpy(result, plain_text);

    for (int i = 0; i < len; i++)
    {
        char symbol =  plain_text[i];
        if (isalpha(symbol))
        {
            if (symbol > 96)
            {
                int index = symbol - 97;
                char sub = key[index];

                if (sub > 96)
                {
                    *(result + i)  = sub;
                }
                else
                {
                    *(result + i)  = sub + 32;
                }

            }
            else
            {
                int index = symbol - 65;
                char sub = key[index];

                if (sub > 96)
                {
                    *(result + i)  = sub - 32;
                }
                else
                {
                    *(result + i)  = sub;
                }
            }

        }
    }

    return result;
}

bool valid_key(string key)
{
    int expected = 2847;
    int sum = 0;
    int array[26];

    for (int i = 0; i < 26; i++)
    {
        char symbol = key[i];
        bool letter = isalpha(symbol);
        if (letter)
        {
            int add = 0;
            if (islower(symbol))
            {
                add = symbol;
            }
            else
            {
                add = tolower(symbol);
            }
            if (in_array(add, array, 26))
            {
                return false;
            }
            array[i] = add;
            sum += add;
        }
        else
        {
            return false;
        }
    }
    return sum == expected;
}

bool in_array(int val, int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        if (arr[i] == val)
        {
            return true;
        }
    }
    return false;
}