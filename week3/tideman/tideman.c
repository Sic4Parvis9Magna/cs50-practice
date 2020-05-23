#include <cs50.h>
#include <stdio.h>
#include <string.h>


// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int find_in_candidates(string name);
int get_root_index(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    int candidate_index = find_in_candidates(name);
    if (candidate_index != -1)
    {
        ranks[rank] = candidate_index;
        return true;
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        int winer_index = ranks[i];
        for (int j = i + 1; j < candidate_count; j++)
        {
            int loser_index = ranks[j];
            preferences[winer_index][loser_index]++;
        }


    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int pair_idex = 0;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        // int start_index = 1;
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] == preferences[j][i])
            {
                continue;
            }

            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_idex].winner = i;
                pairs[pair_idex].loser = j;
                pair_idex++;
            }

            if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_idex].winner = j;
                pairs[pair_idex].loser = i;
                pair_idex++;
            }

        }
        // start_index++;
    }
    pair_count = pair_idex;
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int max = -1;
        int max_index = -1;
        for (int j = i; j < pair_count; j++)
        {
            int next_winer = pairs[j].winner;
            int next_loser = pairs[j].loser;
            int next_voutes = preferences[next_winer][next_loser];

            if (next_voutes > max)
            {
                max = next_voutes;
                max_index = j;
            }
        }

        pair tmp = pairs[i];
        pairs[i] = pairs[max_index];
        pairs[max_index] = tmp;
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int pair_index = 0; pair_index < pair_count; pair_index++)
    {
        pair next_pair = pairs[pair_index];
        locked[next_pair.winner][next_pair.loser] = true;

        if (get_root_index() == -1)
        {
            locked[next_pair.winner][next_pair.loser] = false;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    int winner_index = get_root_index();
    printf("%s\n", candidates[winner_index]);

    return;
}

//returns and index of candidate if present or -1
int find_in_candidates(string name)
{
    int result = -1;
    int name_len = strlen(name);

    for (int i = 0; i < candidate_count; i++)
    {
        string next_name = candidates[i];
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


//returns -1 if there is no verticies, else returns index of vertice
int get_root_index(void)
{
    int root = -1;

    for (int i = 0; i < candidate_count; i++)
    {
        int winners = 0;
        bool present_as_winner = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                winners++;
            }

            if (locked[i][j])
            {
                present_as_winner = true;
            }
        }

        if (present_as_winner && winners == 0)
        {
            root = i;
            break;
        }
    }

    return root;
}