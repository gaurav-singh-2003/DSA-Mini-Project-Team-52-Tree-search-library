#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "node.h"

typedef node* Node;

Node SearchChild(Node* NodeArray, int state_number, int* N)
{
    for(int i = 0 ; i < *N ; i++)
    {
        if(NodeArray[i]->parent == state_number)
        {
            Node Child = (Node) malloc(sizeof(node));
            assert(Child != NULL);

            Child = NodeArray[i];

            for(int j = i ; j < *N - 1 ; j++)
                NodeArray[j] = NodeArray[j+1];

            NodeArray[*N-1] = NULL;  
            (*N)--;
            return Child;
        }
    }
    return NULL;
}

void generateTree(Node TreeNode, Node* NodeArray, int* N, int depth)
{
    Node Child = SearchChild(NodeArray,TreeNode->state_number,N);
    
    if(Child == NULL)
    {
        TreeNode->number_of_children = 0;
        return;
    }

    
    int i = 0;
    while(Child != NULL)
    {
        Child->depth = depth;
        TreeNode->children[i] = Child;
        generateTree(TreeNode->children[i],NodeArray,N,depth + 1);
        Child = SearchChild(NodeArray,TreeNode->state_number,N);
        i++;
    }

    TreeNode->number_of_children = i;
}


Node inputTree()
{
    int NoOfNodes,Depth = 0;
    scanf("%d",&NoOfNodes);

    Node* NodeArray = (Node*) malloc(NoOfNodes*sizeof(node));

    for(int i = 0 ; i < NoOfNodes ; i++)
    {
        NodeArray[i] = (Node) malloc(sizeof(node));
        assert(NodeArray != NULL);
        input_node(NodeArray[i]);
    }

    Node Root = SearchChild(NodeArray,-1,& NoOfNodes);
    Root->depth = 0;
    generateTree(Root,NodeArray,& NoOfNodes, Depth + 1);
    return Root;
}

void printTree(Node TreeNode)
{
    if(TreeNode->number_of_children == 0)
    {
        printf("%d: No Children Depth: %d\n",TreeNode->value,TreeNode->depth);
        return;
    }

    printf("%d: ",TreeNode->value);
    for(int i = 0 ; i < TreeNode->number_of_children ; i++)
        printf("%d ",TreeNode->children[i]->value);
    printf("Depth: %d\n",TreeNode->depth);

    for(int i = 0 ; i < TreeNode->number_of_children ; i++)
        printTree(TreeNode->children[i]);
}

int main()
{
    Node Root = inputTree();
    printTree(Root);    
}