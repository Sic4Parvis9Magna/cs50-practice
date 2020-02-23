#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);
int find_in_candidates(string name);
int get_top_ranked(int vouter_index);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    int candidate_index = find_in_candidates(name);
    if (candidate_index != -1)
    {
        preferences[voter][rank] = candidate_index;
        return true;
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    for (int i = 0; i < voter_count; i++)
    {
        int candidate_index = get_top_ranked(i);
        candidates[candidate_index].votes++;
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    int max_votes = 0;
    int max_index = -1;
    bool more_than_one = false;
    for (int i = 0; i < candidate_count; i++)
    {
        bool elemenated = candidates[i].eliminated;
        int votes = candidates[i].votes;
        if (!elemenated && votes > max_votes)
        {
            more_than_one = false;
            max_votes = votes;
            max_index = i;
        }
        else if (!elemenated && votes == max_votes)
        {
            more_than_one = true;
        }

    }

    if (max_index != -1 && !more_than_one && (float)max_votes > (float)voter_count / 2)
    {
        printf("%s\n", candidates[max_index].name);
        return true;
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int top_limit = voter_count + 1;
    int result = top_limit;
    for (int i = 0; i < candidate_count; i++)
    {
        candidate next_candidate = candidates[i];
        if (!next_candidate.eliminated && next_candidate.votes < result)
        {
            result = next_candidate.votes;
        }
    }

    if (result == top_limit)
    {
        result = 0;
    }

    return result;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        candidate next_candidate = candidates[i];
        if (!next_candidate.eliminated && next_candidate.votes !=  min)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes ==  min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}

//returns and index of candidate if present or -1
int find_in_candidates(string name)
{
    int result = -1;
    int name_len = strlen(name);

    for (int i = 0; i < candidate_count; i++)
    {
        string next_name = candidates[i].name;
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

int get_top_ranked(int vouter_index)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int next_candidate_index = preferences[vouter_index][i];
        if (!candidates[next_candidate_index].eliminated)
        {
            return next_candidate_index;
        }
    }
    return -1;
}