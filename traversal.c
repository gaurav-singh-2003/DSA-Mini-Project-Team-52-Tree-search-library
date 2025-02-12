#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "node.h"
#define ll long long

int max(int a, int b)       //return the maximum of two integers
{
    if (a >= b)
        return a;
    else
        return b;
}

void swap(node **a, node **b)       //swaps two nodes
{
    node *c = *a;
    *a = *b;
    *b = c;
}

bool isempty(node *priority_queue[], int n) //checks if the priority queue is empty(1) or not(0)
{
    for (int i = 0; i < n; i++)
    {
        if (priority_queue[i] != NULL)
            return false;
    }
    return true;
}

void heapify(node **priority_queue, int i, int queue_size, char str[])      //maintains the properties of a heap by restructuring it in case of any change
{
    if ((i - 1) / 2 > 0)
    {
        if (node_comparator(str, priority_queue[i], priority_queue[(i - 1) / 2]))
        {
            swap(&priority_queue[i], &priority_queue[(i - 1) / 2]);
            heapify(priority_queue, (i - 1) / 2, queue_size, str);
            return;
        }
    }
    if (i * 2 + 1 < queue_size)
    {
        if (i * 2 + 2 >= queue_size)
        {
            if (node_comparator(str, priority_queue[i * 2 + 1], priority_queue[i]))
            {
                swap(&priority_queue[i], &priority_queue[i * 2 + 1]);
                heapify(priority_queue, i * 2 + 1, queue_size, str);
                return;
            }
        }
        else
        {
            if (node_comparator(str, priority_queue[i * 2 + 1], priority_queue[i * 2 + 2]) && node_comparator(str, priority_queue[i * 2 + 1], priority_queue[i]))
            {
                swap(&priority_queue[i], &priority_queue[i * 2 + 1]);
                heapify(priority_queue, i * 2 + 1, queue_size, str);
                return;
            }
            else if (node_comparator(str, priority_queue[i * 2 + 2], priority_queue[i * 2 + 1]) && node_comparator(str, priority_queue[i * 2 + 2], priority_queue[i]))
            {
                swap(&priority_queue[i], &priority_queue[i * 2 + 2]);
                heapify(priority_queue, i * 2 + 2, queue_size, str);
                return;
            }
            else if (node_comparator(str, priority_queue[i * 2 + 1], priority_queue[i]))
            {
                swap(&priority_queue[i], &priority_queue[i * 2 + 1]);
                heapify(priority_queue, i * 2 + 1, queue_size, str);
                return;
            }
        }
    }
}

void traversing_algo(node *root, int n, char str[])     //implements the traversal of a tree (or game tree) based on a selected comparator by the user 
{
    // we make a priority queue of n pointers of type node *
    node **priority_queue = (node **)malloc(n * sizeof(node *));
    assert(priority_queue != NULL);

    maxdepth = (int *)malloc(sizeof(int) * n);
    assert(maxdepth != NULL);

    avgdepth = (double *)malloc(sizeof(double) * n);
    assert(avgdepth != NULL);

    maxchildren = (int *)malloc(sizeof(int) * n);
    assert(maxchildren != NULL);

    traversal_order = (Node *)malloc(n * sizeof(Node *));
    assert(traversal_order != NULL);

    int iteration = 0;
    int queue_size = 0, seen_time = 0; // declaration and initialization of queue size and time as we go forward
                                       //seen_time updates the seen_time variable of each node when it is inserted into the priority queue
    for (int i = 0; i < n; i++)
        priority_queue[i] = NULL;
    assert(queue_size <= n);

    //root node is added to the priority queue
    priority_queue[queue_size] = root;
    root->seen_time = seen_time;
    seen_time++;
    queue_size++;
    int maxdepthsize = 0;

    // loop for traversal
    long int depths = 0; //keeps track of depth
    long int average_depth = 0;
    int numberofelems = 1;
    int trackchildren = 0;   //keeps track of maxchildren

    while (!isempty(priority_queue, queue_size)) // while priority queue is not empty
    {
        for (int i = 0; i < priority_queue[0]->number_of_children; i++)
        {
            priority_queue[queue_size] = priority_queue[0]->children[i]; //ith child of current node are added
            priority_queue[0]->children[i]->seen_time = seen_time;       //seen time of the child updated (will be used for comparators)
            seen_time++;
            queue_size++;
            
            heapify(priority_queue, queue_size - 1, queue_size, str); //the ith child is added to its correct location in the priority queue using comparator
        }
        
        swap(&priority_queue[0], &priority_queue[queue_size - 1]);   //pop the first element from the priority queue by swapping with last element
        
        traversal_order[iteration] = priority_queue[queue_size - 1]; // Add the node pointer to the traversal order array
        iteration++;
        //printNode(priority_queue[queue_size - 1]);                 //print the first element which has now been moved to the last
        average_depth += priority_queue[queue_size - 1]->depth;
        depths = max(depths, priority_queue[queue_size - 1]->depth);
        maxdepth[maxdepthsize] = depths;                          //max depth at each iteration
                                                                  // bfactor[maxdepthsize] = priority_queue[queue_size - 1]->number_of_children;
       
        if (priority_queue[queue_size - 1]->linktoparent != NULL) //max children at each iteration
        {

            priority_queue[queue_size - 1]->linktoparent->numberofchildrenvisited++;

            if (trackchildren < priority_queue[queue_size - 1]->linktoparent->numberofchildrenvisited)
                trackchildren = priority_queue[queue_size - 1]->linktoparent->numberofchildrenvisited;
        }
        maxchildren[maxdepthsize] = trackchildren;

        maxdepthsize++;
        avgdepth[numberofelems - 1] = (double)average_depth / numberofelems; //avg depth at each iteration
        numberofelems++;

        priority_queue[queue_size - 1] = NULL;
        queue_size--;
        
        heapify(priority_queue, 0, queue_size, str);
    }
    free(priority_queue);
}

void printstats(int N) //prints the statistical parameters of a tree wiz. avgdepth, maxdepth and maxchildren
{
    assert(traversal_order != NULL);
    assert(maxchildren != NULL);
    assert(maxdepth != NULL);
    assert(avgdepth != NULL);
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("│ Iteration      │ State Number  │     Value     │ Maximum Depth │ average-depth   │  maxchildren  │\n");
    printf("----------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < N; i++)
    {

        printf("│%16d│%15d│%15d│%15d│%17.3lf│%15d│\n", i + 1, traversal_order[i]->state_number, traversal_order[i]->value, maxdepth[i], avgdepth[i], maxchildren[i]);
    }
    printf("----------------------------------------------------------------------------------------------------\n");
}