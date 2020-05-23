#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


bool char_in_array(char c, char array[], int size);
float proportion_to_100(int convertable, int eqvivalent);

int main(void)
{
    string text = get_string("Text: ");
    int len = strlen(text);

    int sentenses = 0;
    int words = 0;
    int letters = 0;

    char sentense_end[] = {'.', '!', '?'};
    int end_arr_size = sizeof(sentense_end) / sizeof(sentense_end[0]);

    char word_dividers[] = {' ', '"', ','};
    int dividers_arr_size = sizeof(word_dividers) / sizeof(word_dividers[0]);

    bool inword = false;

    for (int i = 0; i < len; i++)
    {
        char letter = text[i];
        if (char_in_array(letter, sentense_end, end_arr_size))
        {
            sentenses++;
            if (inword)
            {
                inword = false;
                words++;
            }
            continue;
        }
        else if (char_in_array(letter, word_dividers, dividers_arr_size) && inword)
        {
            inword = false;
            words++;
            continue;
        }
        else
        {
            bool is_alpha = isalpha(text[i]);
            if (!inword && is_alpha)
            {
                inword = true;
            }

            if (is_alpha)
            {
                letters++;
            }
        }


    }

    float l  = proportion_to_100(letters, words);
    float s  = proportion_to_100(sentenses, words);

    float result = round(0.0588F * l - 0.296F * s - 15.8F);
    int final_result = (int)result;

    if (final_result < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (final_result > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", final_result);
    }

}


float proportion_to_100(int convertable, int eqvivalent)
{
    return ((float) convertable * 100) / eqvivalent;
}

bool char_in_array(char c, char array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (c == array[i])
        {
            return true;
        }
    }

    return false;
}