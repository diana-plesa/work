/*A sports tournament organizer needs to manage elimination brackets for 64 teams. Each match eliminates one team, and winners 
advance to the next round until a champion is determined. The system must efficiently:

Track which teams advance at each round
Determine the path any team took to reach their final position
Calculate the minimum number of matches needed
Find all teams that were eliminated by the eventual winner
Design an algorithm to represent this tournament structure and implement functions to answer queries about team progression and match outcomes.*/

#include <stdio.h>
#include <stdlib.h>

#define M_MAX 150
#define POW 7 //power of 2 -> 2^POW = nb_nodes

typedef struct 
{
    int index; //index of match
    int winner; //value of winner of the match - value between 1 and 64, from the initial teams
    int parent; //parent index
    int left_team; //left team/child index
    int right_team; //right team/child index
} MATCH;

typedef struct 
{
    int nb_nodes;
    MATCH matches[M_MAX];
} TOURNAMENT;

TOURNAMENT sys;

void init_tree()
{
    for (int i = 0; i < M_MAX; i++)
    {
        sys.matches[i].index = 0;
        sys.matches[i].parent = 0;

        //if (i >= 1 && i <= 64) sys.matches[i].winner = i; //iniial teams; leaf nodes
        sys.matches[i].winner = 0;

        sys.matches[i].left_team = 0;
        sys.matches[i].right_team = 0;
    }
}

void read_file(char filename[])
{
    FILE *f = fopen(filename, "r");

    if (f == NULL)
    {
        perror("Error open file");
        exit(-1);
    }

    init_tree();
    
    int index, winner, parent, left_team, right_team;

    while (fscanf(f, "%d %d %d %d %d", &index, &winner, &parent, &left_team, &right_team) != EOF)
    {
        sys.matches[index].winner = winner;
        sys.matches[index].parent = parent;
        sys.matches[index].left_team = left_team;
        sys.matches[index].right_team = right_team;
        sys.matches[index].index = index;
    }

    if (fclose(f) != 0)
    {
        perror("Error close file");
        exit(-1);
    }
}

int power(int x, int y)
{
    int val = 1;
    for (int i = 0; i < y; i++)
    {
        val = val * x;
    }
    return val;
}

void winners_per_round()
{
    int round = 0, count = 0;
    printf("Round %d: ", POW - round);

    for (int i = sys.nb_nodes - 1; i >= 1; i--)
    {    
        if (count < power(2, round))
        {
            printf("%d ", sys.matches[i].winner);
            count++;
        }
        else 
        {
            round++;
            printf("\nRound %d: ", POW - round);
            printf("%d ", sys.matches[i].winner);
            count = 1;
        }
    }
    printf("\n");
}

void get_team_path(int team)
{
    int cursor = team; 
    for (int i = sys.nb_nodes - 1; i >= 1; i--)
    {
        if (sys.matches[i].winner == team) 
        {
            cursor = i;
            printf("%d", cursor); //final position of the team in the tournament

            break;
        }
    }

    while (cursor != team) //not in leaf node
    {
        if (sys.matches[sys.matches[cursor].left_team].winner == team) cursor = sys.matches[cursor].left_team;
        else if (sys.matches[sys.matches[cursor].right_team].winner == team) cursor = sys.matches[cursor].right_team;

        printf(" <- %d", cursor);
    }

    printf("\n");
}

void print_tree()
{
    for (int i = 1; i < sys.nb_nodes; i++)
    {
        printf("index = %d, winner = %d, parent = %d, left = %d, right = %d\n",
        sys.matches[i].index, sys.matches[i].winner, sys.matches[i].parent, sys.matches[i].left_team, sys.matches[i].right_team);
    }
}

void get_losers()
{
    int cursor = sys.nb_nodes - 1; //final winner index
    //printf("%d", cursor);
    while (cursor != sys.matches[sys.nb_nodes - 1].winner) //while not in leaf node
    {
        if (sys.matches[sys.matches[cursor].left_team].winner == sys.matches[cursor].winner) 
        {
            printf("%d ", sys.matches[sys.matches[cursor].right_team].winner);
            cursor = sys.matches[cursor].left_team;
        }
        else if (sys.matches[sys.matches[cursor].right_team].winner == sys.matches[cursor].winner)
        {
            printf("%d ", sys.matches[sys.matches[cursor].left_team].winner);
            cursor = sys.matches[cursor].right_team;
        }
        
    }
}

int main(int argc, char** argv)
{
    sys.nb_nodes = 128;
    read_file(argv[1]);
    //winners_per_round();
    //get_team_path(56);
    //print_tree();
    get_losers();

    return 0;
}