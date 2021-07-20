//Anthony Dalia
//an694448

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "KindredSpirits.h"

typedef struct linkedNode
{
	int data;
	struct linkedNode *next;
} linkedNode;

typedef struct linkedList
{
	linkedNode *head;
	linkedNode *tail;
} linkedList;

int isReflection(node *a, node *b) //COMPLETE
{
	//Check if the nodes are both null or if just one node is null
	if (a == NULL && b == NULL)
	{
		return 1;
	}
	else if (a == NULL || b == NULL)
	{
		return 0;
	}

	//Check if the data at both nodes is equal
	if (a->data != b->data)
	{
		return 0;
	}

	//Check for structural miss-match in the children
	if (a->left != NULL && b->right == NULL || a->left == NULL && b->right != NULL)
	{
		return 0;
	}
	else if (a->right != NULL && b->left == NULL || a->right == NULL && b->left != NULL)
	{
		return 0;
	}

	//Loop through both subtrees looking for failures
	return(isReflection(a->left, b->right) && isReflection(a->right, b->left));
}

node *makeReflection(node *root) //COMPLETE
{
	node *newNode;

	//Ensure the current node is not null
	if (root == NULL)
		return NULL;

	//Create a new node with the same value as the previous node
	newNode = malloc(sizeof(node));
	newNode->data = root->data;

	//Recursively copy the rest of the tree
	newNode->left = makeReflection(root->right);
	newNode->right = makeReflection(root->left);

	return newNode;
}

linkedList *preOrder(node *root, linkedList *listy) //COMPLETE - Helper
{
	linkedNode *newNode;

	//Check for NULL
	if (root == NULL)
		return NULL;

	//Create a new node
	newNode = malloc(sizeof(linkedNode));
	newNode->data = root->data;

	//Update the tail of the list
	if(listy->tail == NULL)
	{
		listy->tail = newNode;
	}
	else
	{
		listy->tail->next = newNode;
		listy->tail = newNode;
	}

	//Recurse through the left subtree
	if(root->left != NULL)
	{
		listy = preOrder(root->left, listy);
	}

	//Recurse through the right subtree
	if (root->right != NULL)
	{
		listy = preOrder(root->right, listy);
	}

	//There is nothing left so say that we are the head and return
	listy->head = newNode;
	return listy;
}

linkedList *postOrder(node *root, linkedList *listy) //COMPLETE - Helper
{
	linkedNode *newNode;

	//Check for NULL
	if (root == NULL)
		return NULL;

	//Recurse through the left subtree
	if (root->left != NULL)
	{
		listy = postOrder(root->left, listy);
	}

	//Recurse through the right subtree
	if (root->right != NULL)
	{
		listy = postOrder(root->right, listy);
	}

	//We have no subtrees so generate a node
	newNode = malloc(sizeof(linkedNode));
	newNode->data = root->data;

	//Determine if we are the first node in the list
	if (listy->head == NULL)
	{
		listy->head = newNode;
	}

	//Add ourselves to the tail of the list
	if(listy->tail == NULL)
	{
		listy->tail = newNode;
	}
	else
	{
		listy->tail->next = newNode;
		listy->tail = newNode;
	}

	//Return to the next level up
	return listy;
}

void listyFree(linkedList *listy) //COMPLETE - Helper
{
	linkedNode *node, *temp;

	if (listy == NULL)
		return;

	node = listy->head;

	//Free all nodes associated with the listy
	while (node != NULL)
	{
		temp = node->next;
		free(node);
		node = temp;
	}

	//Free the actual struct
	free(listy);

	return;
}

int compareLists(linkedNode *preNode, linkedNode *postNode)
{
	//Loop through comparing the vals
	while (preNode !=NULL || postNode != NULL)
	{
		//Check if one node is NULL for unequal length
		if (preNode == NULL || postNode == NULL)
		{
			return 0;
		}

		//Check the value at both nodes
		if (preNode->data != postNode->data)
		{
			return 0;
		}

		//Continue onwards
		preNode = preNode->next;
		postNode = postNode->next;
	}

	//We have check the whole list so return true
	return 1;
}

int kindredSpirits(node *a, node *b) //COMPLETE
{
	linkedList *preList, *postList;
	linkedNode *preNode, *postNode;
	int check1, check2;

	//Check nulls to see if it is possible for them to be kindred
	if (a == NULL)
	{
		if (b == NULL)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (b == NULL)
	{
		return 0;
	}

	//Create two listy Structs
	preList = malloc(sizeof(linkedList));
	preList->head = NULL;
	preList->tail = NULL;

	postList = malloc(sizeof(linkedList));
	postList->head = NULL;
	postList->tail = NULL;

	//Pre-order node a
	preList = preOrder(a, preList);

	//Post-order node b
	postList = postOrder(b, postList);

	//Set up for first comparison
	preNode = preList->head;
	postNode = postList->head;

	//Run the first comparison
	check1 = compareLists(preNode, postNode);

	//Reset the two structs
	preList->head = NULL;
	preList->tail = NULL;

	postList->head = NULL;
	postList->tail = NULL;

	//Pre-order node b
	preList = preOrder(b, preList);

	//Post-order node a
	postList = postOrder(a, postList);

	//Set up for second comparison
	preNode = preList->head;
	postNode = postList->head;

	//Run the first comparison
	check2 = compareLists(preNode, postNode);

	//Free the lists as we no longer need them
	listyFree(preList);
	listyFree(postList);

	//Return the correct value
	return (check1 || check2);
}

double difficultyRating(void) //COMPLETE
{
	return 1.5;
}

double hoursSpent(void) //COMPLETE
{
	return 5.0;
}
