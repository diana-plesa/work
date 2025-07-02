#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_ALPHA 26  
#define MAX_T 30

typedef struct node
{
    int end_of_word;
    struct node* children[MAX_ALPHA];
} NODE;

int count_nodes = 0;

NODE* create_node()
{
    NODE* new_node = (NODE*) malloc(sizeof(NODE));
    new_node->end_of_word = 0;

    for (int i = 0; i < MAX_ALPHA; i++)
    {
        new_node->children[i] = NULL;
    }

    return new_node;
}

int get_index(char c)
{
    return tolower(c) - 'a';
}

void insert(char word[], NODE* root)
{
    NODE* current = root;
    for (int i = 0; word[i]; i++)
    {
        int index = get_index(word[i]);

        if (index < 0 || index > MAX_ALPHA) continue;
        if (!current->children[index]) 
        {
            current->children[index] = create_node();
            count_nodes++;
        }

        current = current->children[index];
    }

    current->end_of_word = 1;
}

void print_tree(NODE* cursor, char buffer[], int depth)
{
    if (cursor ->end_of_word==1) 
    {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }
    for (int i = 0; i < MAX_ALPHA; i++)
    {
        if (cursor->children[i] != NULL) 
        {
            //printf("%c ", i + 'a');
            buffer[depth] = i + 'a';
            print_tree(cursor->children[i], buffer, depth + 1);
        }
    }
}

int main()
{
    NODE* root = create_node();
    //insert("Calcium", root);
    insert("Helium", root);
    insert("Hell", root);
    insert("Hella", root);
    char buffer[50];
    //printf("%d", count_nodes);
    print_tree(root, buffer, 0);
    return 0;
}