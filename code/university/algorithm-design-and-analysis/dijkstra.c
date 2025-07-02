//pbinfo 1887

#include <stdio.h>
#include <stdlib.h>

#define MAX_G 30
#define INF 9999

int graph[MAX_G][MAX_G] = { 0 };
int nb_nodes;
int start = 0;

void read_file(char filename[])
{
    FILE* f = fopen(filename, "r");

    if (f == NULL)
    {
        perror("Error open file");
        exit(-1);
    }

    for (int i = 1; i <= MAX_G; i++)
    {
        for (int j = 1; j <= MAX_G; j++)
        {
            if (i != j) graph[i][j] = INF;
            else graph[i][j] = 0;
        }
    }

    fscanf(f, "%d", &nb_nodes);
    int nb_edges = 0;
    fscanf(f, "%d", &nb_edges);
    fscanf(f, "%d", &start);

    int node1 = 1, node2 = 1, cost = 0;

    for(int i = 1; i <= nb_edges; i++)
    {
        fscanf(f, "%d %d %d", &node1, &node2, &cost); //use cost variable for memory safety
        graph[node2][node1] = cost;
        graph[node1][node2] = cost;
    }

    if (fclose(f) != 0)
    {
        perror("Error close file");
        exit(-1);
    }
}

void dijkstra()
{
    int dist[MAX_G];
    int visited[MAX_G] = { 0 };
    int prev[MAX_G];

    for (int i = 1; i <= nb_nodes; i++)
    {
        if (graph[start][i] != INF) dist[i] = graph[start][i];
        else dist[i] = INF;
        prev[i] = start;
    } //first step - initalise everything from start's pov

    dist[start] = 0; //distance to itself is 0
    visited[start] = 1; //mark as visited

    for (int step = 1; step <= nb_nodes; step++) //max nb_nodes steps for the algorithm
    {

        int min = INF;
        int next_node = -1; //the next node that will be picked to proceed with the algorithm - smallest cost of an unvisited node  

        for (int i = 1; i <= nb_nodes; i++)
        {
            if (!visited[i] && dist[i] < min)
            {
                min = dist[i];
                next_node = i;
            }
        }

        if (next_node == -1) break;
        visited[next_node] = 1; 

        for (int i = 1; i <= nb_nodes; i++)
        {
            if (dist[i] > dist[next_node] + graph[next_node][i]) 
            {
                dist[i] = dist[next_node] + graph[next_node][i];
                prev[i] = next_node;
            }
        }
    }

    for (int i = 1; i <= nb_nodes; i++)
    {
        if (dist[i] == INF) dist[i] = -1;
        printf("%d ", dist[i]);
    }
}

void print_g()
{
    for (int i = 1; i <= nb_nodes; i++)
    {
        for (int j = 1; j <= nb_nodes; j++)
        {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv)
{
    read_file(argv[1]);
    //print_g();
    dijkstra();

    return 0;
}