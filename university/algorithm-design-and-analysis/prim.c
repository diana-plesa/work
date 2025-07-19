/*A city planning department needs to connect all neighborhoods to essential utilities (water, electricity, gas) 
at minimum cost. They have cost estimates for running utility lines between different areas, including:

Installation costs that vary based on terrain and distance
The requirement that all neighborhoods must be connected (directly or indirectly)
Budget constraints requiring the most economical solution
The need to ensure no redundant connections that don't reduce total cost
Given the cost matrix for connecting different neighborhoods, design an algorithm to determine the minimum cost 
to connect the entire city to utilities. Compare different approaches and analyze which is more efficient for this specific application.*/

//PRIM (MST) - only for undirected graphs with no isolated nodes or components

#include <stdio.h>
#include <stdlib.h>

#define MAX_G 50
#define INF 9999

int graph[MAX_G][MAX_G] = { 0 };
int nb_neighborhoods;

void read_file(char file[])
{
    FILE *f = fopen(file, "r");

    if (f == NULL)
    {
        perror("Error open file");
        exit(-1);
    }

    fscanf(f, "%d", &nb_neighborhoods);

    for (int i = 0; i < nb_neighborhoods; i++)
    {
        for (int j = 0; j < nb_neighborhoods; j++)
        {
            int cost = 0;
            fscanf(f, "%d", &cost);
            graph[i][j] = cost;
            graph[j][i] = cost;
        }
    }

    if (fclose(f) != 0)
    {
        perror("Error close file");
        exit(-1);
    }
}

void print_g(int g[][MAX_G])
{
    for (int i = 0; i < nb_neighborhoods; i++)
    {
        for (int j = 0; j < nb_neighborhoods; j++)
            printf("%d ", g[i][j]);
        printf("\n");
    }
}

void prim(int start)
{
    int in_mst[MAX_G] = { 0 }; //is node in mst?
    int prev[MAX_G]; //parent of each node in mst
    int min_cost[MAX_G]; //minimum cost to a reachable node outside mst

    for (int i = 0; i < nb_neighborhoods; i++)
    {
        prev[i] = -1;
        min_cost[i] = INF;
    } //init arrays

    min_cost[start] = 0;

    for (int count = 0; count < nb_neighborhoods; count++)
    {
        int next_node = -1;
        int min = INF;
        for (int i = 0; i < nb_neighborhoods; i++)
        {
            if (!in_mst[i] && min_cost[i] < min)
            {
                next_node = i;
                min = min_cost[i];
            }
        }

        if (next_node == -1) break;
        in_mst[next_node] = 1; //add to mst

        //update min_cost

        for (int i = 0; i < nb_neighborhoods; i++)
        {
            if (!in_mst[i] && graph[next_node][i] != 0 && graph[next_node][i] < min_cost[i])
            {
                min_cost[i] = graph[next_node][i];
                prev[i] = next_node;
            }
        }

    }

    for (int i = 0; i < nb_neighborhoods; i++)
    {
        printf("%d %d, cost = %d\n", prev[i], i, min_cost[i]);
    }
}

int main(int argc, char** argv)
{
    read_file(argv[1]);
    prim(0);

    return 0;
}