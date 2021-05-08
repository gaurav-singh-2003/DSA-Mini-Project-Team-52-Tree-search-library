#ifndef NODE_H
#define NODE_H
/*
    The idea behind Tree Search Library is that, once given the 'comparator' function between nodes by 
    the user, the library can use this to perform any kind of search by the change of just one function.
    
    The comparator function takes as input the pointers of two nodes and outputs whether the first is 
    lesser than the other. You can use this comparator for deciding the order of 2 nodes in the priority 
    queue.
    This file will be what the user will edit, while trying to use your library. Once you complete writing
    the library, you have to (as an user of the library), write the comparators for DFS, BFS, greedy 
    search (A-star lite).
    Check out the input file ts_data_1.txt. It has input of format 
    <number_of_nodes>:n
    <state_number> <value> <parent_state_number>
    ...
    n times
    For now, write the main function and input the nodes, fill the values of number_of_children, children
    (in the struct) and try to write the priority queue using the comparator.
*/

#include <stdio.h>
#include <stdbool.h>

int *maxdepth;
double *avgdepth;
//int bfactor[10000];
int *maxchildren;

typedef struct node
{
    int state_number;
    int value;
    int parent;

    // You (as a developer) can add any extra information here [Will not be touched by user]
    int depth, seen_time, number_of_children, NoOfNodes;
    char game_state, TicTacToe[3][3];
    struct node *children[10000];
    struct node *linktoparent;   //links the node to its parent
    int numberofchildrenvisited; //number of children of the node visited during the search
} node;

typedef node *Node;

bool node_comparator(char str[], node *a, node *b);
void input_node(node *a);

void generateTree(Node *NodeArray, int N); //generates a tree out of the array of nodes
Node inputTree();                          //takes input from the user and returns a tree
void printNode(Node TreeNode);             //prints the attributes of a node
void printTree(Node TreeNode);             //traverses through each node of the tree and prints its attributes
void printTree2(Node TreeNode);            //shows the structure of the tree while printing minimal information (the state number and value)
void DeleteTree(Node TreeNode);            //Frees memory allocated to the tree

Node inputGameTree();
void generateGameTree(Node GameNode);
void printTree3(Node GameNode);

void swap(node **a, node **b);
bool isempty(node *priority_queue[], int n); //checks if the priority queue is empty(1) or not(0)
void heapify(node **priority_queue, int i, int queue_size, char str[]);
void traversing_algo(node *root, int n, char str[]);
void printTree2(Node TreeNode);
void printNodenoice(Node TreeNode, int what_to_do[]);
void printstats(int N);
void free_memory_alloc_stats();
#endif