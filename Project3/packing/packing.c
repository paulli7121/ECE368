#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "packing.h"

double find_max(double num1, double num2);

void load_file(FILE* fp1, FILE* fp2, Node** head){
	char check_ch = 0;
	int ret = 0;
	while(!feof(fp1)){
		ret = fread(&check_ch, sizeof(char), 1, fp2);
		if((check_ch == 'H') || (check_ch == 'V')){
			(*head) = malloc(sizeof(Node));
			(*head) -> ch = 0;
			(*head) -> number = 0;
			(*head) -> o2 = 0;
			(*head) -> o1 = 0;
			fscanf(fp1, "%c\n", &((*head) -> ch));
			while(check_ch != '\n'){
				ret = fread(&check_ch, sizeof(char), 1, fp2);
			}
			//printf("loading node: %c.\n", (*head) -> ch);
			load_file(fp1, fp2, &((*head) -> left));
			load_file(fp1, fp2, &((*head) -> right));
			//printf("node go back.\n");
			return;
		}
		else{
			(*head) = malloc(sizeof(Node));
			(*head) -> left = NULL;
			(*head) -> right = NULL;
			(*head) -> ch = 0;
			fscanf(fp1,"%d(%le,%le)\n", &((*head) -> number), &((*head) -> o1), &((*head) -> o2));
			while(check_ch != '\n'){
				ret = fread(&check_ch, sizeof(char), 1, fp2);
			}
			//printf("loading leaf: %d(%f, %f).\n",(*head) -> number,(*head) -> o1,(*head) -> o2);
			//printf("leaf go back.\n");
			return;
		}
		
	}
	
	return;
}

void print_tree_post(Node* head, FILE*fp){
	
	if((head -> left == NULL) && (head -> right == NULL)){
		fprintf(fp,"%d(%le,%le)\n", head -> number, head -> o1, head -> o2);
		//printf("go back.\n");
		return;
	}
	else{		
		//printf("go left.\n");
		print_tree_post(head -> left, fp);
		//printf("go right.\n");
		print_tree_post(head -> right, fp);
		fprintf(fp, "%c\n", head -> ch);
	
	}
	return;
}

void add_dimension(Node* head, double* max_o1, double* max_o2){
	if((head -> left == NULL) && (head -> right == NULL)){
		/*if(head -> o1 > *max_o1){
			*max_o1 = head -> o1;
		}
		if(head -> o2 > *max_o2){
			*max_o2 = head -> o2;
		}*/
		return;
	}
	add_dimension(head -> left, max_o1, max_o2);
	add_dimension(head -> right, max_o1, max_o2);
	if(head -> ch == 'V'){
		head -> o1 = head -> left -> o1 + head -> right -> o1;
		head -> o2 = find_max(head -> left -> o2, head -> right -> o2);
	}
	if(head -> ch == 'H'){
		head -> o2 = head -> left -> o2 + head -> right -> o2;
		head -> o1 = find_max(head -> left -> o1, head -> right -> o1);
	}
	
	return;
}

void print_dimension(Node* head, FILE*fp){
	
	if((head -> left == NULL) && (head -> right == NULL)){
		fprintf(fp,"%d(%le,%le)\n", head -> number, head -> o1, head -> o2);
		//printf("go back.\n");
		return;
	}
	else{		
		//printf("go left.\n");
		fprintf(fp, "%c(%le,%le)\n", head -> ch, head -> o1, head -> o2);
		print_dimension(head -> left, fp);
		//printf("go right.\n");
		print_dimension(head -> right, fp);
		//printf("%c(%le,%le)\n", head -> ch, head -> o1, head -> o2);
	
	}
	return;
}

double find_max(double num1, double num2){
	if(num1 >= num2){
		return num1;
	}
	return num2;
}

void change_coor(Node* head, double curr_o1, double curr_o2, FILE* fp){
	if((head -> left == NULL) && (head -> right == NULL)){
		fprintf(fp, "%d(%le,%le)\n", head -> number, curr_o1, curr_o2);
		return;
	}
	if(head -> ch == 'H'){
		curr_o2 = curr_o2 + head -> right -> o2;
	}
	change_coor(head -> left, curr_o1, curr_o2, fp);
	if(head -> ch == 'V'){
		curr_o1 = curr_o1 + head -> left -> o1;
	}
	if(head -> ch == 'H'){
		curr_o2 = curr_o2 - head -> right -> o2;
	}
	change_coor(head -> right, curr_o1, curr_o2, fp);
	return;
}

void free_node(Node* head){
	if((head -> left == NULL) && (head -> right == NULL)){
		free(head);
		return;
	}
	free_node(head -> left);
	free_node(head -> right);
	free(head);
	return;
}
/*void print_packing(Node* head, FILE*fp){
	
	if((head -> left == NULL) && (head -> right == NULL)){
		printf("%d(%le,%le)\n", head -> number, head -> o1, head -> o2);
		//printf("go back.\n");
		return;
	}
	else{		
		//printf("go left.\n");
		//fprintf(fp, "%c(%le,%le)\n", head -> ch, head -> o1, head -> o2);
		print_packing(head -> left, fp);
		//printf("go right.\n");
		print_packing(head -> right, fp);
		//printf("%c(%le,%le)\n", head -> ch, head -> o1, head -> o2);
	
	}
	return;
}*/
