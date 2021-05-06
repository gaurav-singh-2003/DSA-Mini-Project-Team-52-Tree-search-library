#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "node.h"



bool node_comparator(char str[], node *a, node *b)
{
    if (strcmp(str, "DFS") == 0)
    {
        return a->seen_time > b->seen_time;
    }
    else if (strcmp(str, "BFS") == 0)
    {
        return a->seen_time < b->seen_time;
    }
    else if (strcmp(str, "Greedy") == 0)
    {
        return a->value < b->value;
    }
    else
        return a->seen_time > b->seen_time;
}
void input_node(node *a)
{
    // inputs the information of one node. Use this in a loop to input all the nodes.
    scanf("%d %d %d", &(a->state_number), &(a->value), &(a->parent));
}