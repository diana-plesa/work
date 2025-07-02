
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIBLINGS 10
#define MAX_N 25

typedef struct 
{
    int parent;
    int val;
    int left_child;
    int right_siblings[MAX_SIBLINGS];
} NODE;

typedef struct 
{
    int nb_nodes;
    NODE nodes[MAX_N];
} TREE;

TREE tree;

void init_tree()
{
    for (int i = 0; i <= tree.nb_nodes; i++)
    {
        tree.nodes[i].left_child = 0;
        tree.nodes[i].val = 0;
        tree.nodes[i].parent = 0;

        for (int j = 0; j < MAX_SIBLINGS; j++)
        {
            tree.nodes[i].right_siblings[j] = 0;
        }
        
    }
}

void add_children()
{
    for (int i = 1; i <= tree.nb_nodes; i++)
    {
        if (tree.nodes[i].parent == 0) continue;

        if (tree.nodes[tree.nodes[i].parent].left_child == 0)
        tree.nodes[tree.nodes[i].parent].left_child = i;

        else
        {
            int left = tree.nodes[tree.nodes[i].parent].left_child;
            for (int j = 0; j < MAX_SIBLINGS; j++)
            {
                if (tree.nodes[left].right_siblings[j] == 0)
                {
                    tree.nodes[left].right_siblings[j] = i;
                    break;
                }
            }
        }
    }
}

void read_file(char file[])
{
    FILE *f = fopen(file, "r");

    if (f == NULL)
    {
        perror("Error open file");
        exit(-1);
    }

    fscanf(f, "%d", &tree.nb_nodes);

    int i = 1;
    while (fscanf(f, "%d %d", &tree.nodes[i].val, &tree.nodes[i].parent) != EOF)
    {
        i++;
    }

    add_children();

    if (fclose(f) != 0)
    {
        perror("Error close file");
        exit(-1);
    }
}

void print_tree()
{
    for (int i = 1; i <= tree.nb_nodes; i++)
    {
        printf("val = %d, parent = %d, left child = %d, right siblings =", 
        tree.nodes[i].val, tree.nodes[i].parent, tree.nodes[i].left_child);

        for (int j = 0; j < MAX_SIBLINGS; j++)
        {
            if (tree.nodes[i].right_siblings[j] == 0)
            break;
            else printf("%d ", tree.nodes[i].right_siblings[j]);
        }
        printf("\n");
    }
}

void do_preorder(int root)
{
    if (!root) return;

    printf("%d ", root);

    int fc = tree.nodes[root].left_child;

    do_preorder(fc);

    for (int i = 0; i < MAX_SIBLINGS; i++)
    {
        if (tree.nodes[fc].right_siblings[i])
        {
            do_preorder(tree.nodes[fc].right_siblings[i]);
        }
        else break;
    }
}

void do_inorder(int root)
{
    if (!root) return;
    
    int fc = tree.nodes[root].left_child;
    do_inorder(fc);

    printf("%d ", root);

    for (int i = 0; i < MAX_SIBLINGS; i++)
    {
        if (tree.nodes[fc].right_siblings[i]) do_inorder(tree.nodes[fc].right_siblings[i]);
        else break;
    }   
}

void do_postorder(int root)
{
    if (!root) return;

    int fc = tree.nodes[root].left_child;

    do_postorder(fc);

    for (int i = 0; i < MAX_SIBLINGS; i++)
    {
        if (tree.nodes[fc].right_siblings[i]) do_postorder(tree.nodes[fc].right_siblings[i]);
        else break;
    }

    printf("%d ", root);
}

void preorder(int root)
{
    if (!root) return;
    do_preorder(root);
    printf("\n");
}

void inorder(int root)
{
    if (!root) return;
    do_inorder(root);
    printf("\n");
}

void postorder(int root)
{
    if (!root) return;
    do_postorder(root);
    printf("\n");
}

int main(int argc, char** argv)
{
    init_tree();
    read_file(argv[1]);
    print_tree();
    return 0;
}