#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
	char ch;
	int number;
	double o1;
	double o2;
	struct _Node *left;
	struct _Node *right;
}Node;

void load_file(FILE* fp1, FILE* fp2, Node** node);
void print_tree_post(Node* head, FILE* fp);
void add_dimension(Node* head, double* max_o1, double* max_o2);
void print_dimension(Node* head, FILE*fp);
void change_coor(Node* head, double curr_o1, double curr_o2, FILE* fp);
void print_packing(Node* head, FILE*fp);
void free_node(Node* head);

