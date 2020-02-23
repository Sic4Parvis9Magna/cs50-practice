#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
int get_max_votes(candidate arr[]);
int name_is_present(string name, candidate arr[]);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    int index = name_is_present(name, candidates);
    if (index != -1)
    {
        candidates[index].votes++;
        return true;
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int max = get_max_votes(candidates);
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max)
        {
            printf("%s\n", candidates[i].name);
        }

    }

    return;
}

int get_max_votes(candidate arr[])
{
    int max = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        int next_val = arr[i].votes;
        if (next_val > max)
        {
            max = next_val;
        }
    }

    return max;
}

int name_is_present(string name, candidate arr[])
{
    int result = -1;
    int name_len = strlen(name);

    for (int i = 0; i < candidate_count; i++)
    {
        string next_name = arr[i].name;
        int next_len = strlen(next_name);
        if (name_len == next_len)
        {
            bool equal = true;
            for (int j = 0; j < name_len; j++)
            {
                if (name[j] != next_name[j])
                {
                    equal = false;
                    break;
                }
            }
            if (equal)
            {
                result = i;
                break;
            }
        }
    }
    return result;
}