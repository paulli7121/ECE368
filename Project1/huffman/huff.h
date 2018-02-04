#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	char ch;
	struct TreeNode* right_node;
	struct TreeNode* left_node;
} tree_node;

typedef struct LinkNode{
	tree_node* element;
	struct LinkNode* next;

}link_node;

