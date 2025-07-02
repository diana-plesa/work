/*A social media platform wants to analyze user connections to understand community formation. 
Given friendship data between users, the platform needs to:

Identify isolated groups of friends who have no connections to other groups
Determine the size of the largest friend circle
Find users who could serve as bridges between different communities
Calculate how many separate social clusters exist in the network
You are provided with a dataset of user friendships where each friendship is bidirectional. Design an algorithm to analyze 
these social connections and answer queries about community structure.*/
//bfs, dfs, articulation points, conex components

#include <stdio.h>
#include <stdlib.h>

#define MAX_G 50
#define MAX_S 50
#define MAX_Q 50

int graph[MAX_G][MAX_G] = { 0 };
int q[MAX_Q] = { 0 };
int s[MAX_S] = { 0 };

int nb_ppl;
int tail = -1, head = -1, top = -1;

void read_file(char file[])
{
    FILE *f = fopen(file, "r");

    if (f == NULL)
    {
        perror("Error open file");
        exit(-1);
    }

    fscanf(f, "%d", &nb_ppl);

    for (int i = 0; i < nb_ppl; i++)
    {
        for (int j = 0; j < nb_ppl; j++)
        {
            fscanf(f, "%d", &graph[i][j]);
        }
    }

    if (fclose(f) != 0)
    {
        perror("Error close file");
        exit(-1);
    }
}

int queue_empty()
{
    if (head == tail && head == -1) return 1;
    else return 0;
}

void enqueue(int x)
{
    if (queue_empty())
    {
        head = 0;
    }
    if (tail < MAX_Q - 1)
    {
        tail++;
        q[tail] = x;
    }
    else printf("Full queue\n");
}

int dequeue()
{
    if (queue_empty()) return -1;

    int dequeued = q[head];
    head++;

    if (head > tail)
    {
        head = -1;
        tail = -1;
    }
    return dequeued;
}

int BFS(int start, int visited[], int max_size)
{
    enqueue(start);
    visited[start] = 1;
    int new_max = 0;
    new_max++;
    //print

    while (!queue_empty())
    {
        int node = dequeue();
        //print

        for (int i = 0; i < nb_ppl; i++)
        {
            if (graph[node][i] == 1 && visited[i] == 0)
            {
                enqueue(i);
                visited[i] = 1;
                new_max++;
            }
        }
    }

    if (new_max > max_size) max_size = new_max;
    return max_size;
}

int stack_empty()
{
    return (top == -1);
}

void push(int x)
{
    if (top < MAX_S - 1)
    {
        top++;
        s[top] = x;
    }
}

int pop()
{
    if (stack_empty()) return -1;

    int popped = s[top];
    top--;

    return popped;
}

void DFS(int start, int visited[])
{
    push(start);
    visited[start] = 1;
    //print

    while (!stack_empty())
    {
        int node = pop();
        //print

        for (int i = nb_ppl - 1; i >= 0; i--)
        {
            if (graph[node][i] == 1 && visited[i] == 0)
            {
                push(i);
                visited[i] = 1;

            }
        }
    }
}

void find_isolated_groups()
{
    int count = 0;
    int visited[MAX_G] = { 0 };
    int max_size = 0;
    for (int i = 0; i < nb_ppl; i++)
    {
        if (visited[i] == 0)
        {
            max_size = BFS(i, visited, max_size);
            count++;
        }
    }

    printf("%d\n", count);
    printf("%d\n", max_size);
}

void find_articulation_points()
{
    //parse all nodes; consider them visited, and then parse each direct neighbor of said node. Use DFS on these neighbors and count
    //if count > 1, it's an articulation point
    for (int i = 0; i < nb_ppl; i++)
    {
        int visited[MAX_G] = { 0 };

        visited[i] = 1;
        int count = 0;

            for (int j = 0; j < nb_ppl; j++)
            {
                if (graph[i][j] == 1 && visited[j] == 0)
                {
                    DFS(j, visited);
                    count++;
                }
            }
    
        if (count > 1) printf("%d ", i);

    }
}

int main(int argc, char** argv)
{
    read_file(argv[1]);
    find_isolated_groups();
    find_articulation_points();
    return 0;
}