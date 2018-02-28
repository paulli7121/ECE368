#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sorting.h"

int find_long_size(char* Filename);
Node* build_link_node(long value, Node* next);
void add_link_node(Node** head, long value);
void move_node(Node** node, int step);
void print_link_list(Node* head);
List* build_list_node(Node* element, List* next);
void add_list_node(List** head, Node* element);
List* next_node(int gap, List* current_node);
void bubble_sort_list(List* start_node, int gap, double* N_Cmp);
void free_list(List* head);
//void free_link(Node* head);

long* Load_Into_Array(char* Filename, int* Size){
	int num = find_long_size(Filename);
	long* array = malloc(sizeof(long) * num);
	FILE* fp = fopen(Filename, "r");
	int ret;

	for(int i = 0; i < num; i++){
		ret = fread(&array[i], sizeof(long), 1, fp);
	}
	*Size = num;
	fclose(fp);
	return array;
}

int Save_From_Array(char* Filename, long* Array, int Size){
	FILE* fp = fopen(Filename, "wb");
	int count = 0;
	for(int i = 0; i < Size; i++){
		fwrite(&Array[i], sizeof(long), 1, fp);
		count++;
	}
	fclose(fp);
	return count;
}

void Shell_Sort_Array(long *Array, int Size, double *N_Cmp){
	int i;
	int j;
	int k = 1;
	long temp;
	while(k < Size){
		k = k * 3 + 1;
	}                         //right now k is larger than size


	for(k = (k - 1)/3; k > 0; k = (k - 1)/3 ){
		for(i = k; i < Size; i++){
			temp = Array[i];
			for( j = i; j >= k && Array[j-k] > temp; j = j - k){
				Array[j] = Array[j-k];
				*N_Cmp = *N_Cmp + 1;
			

			}
			Array[j] = temp;
		}
	}

}

Node* Load_Into_List(char* Filename){
	FILE* fp = fopen(Filename, "r");
	Node* head = NULL;
	int size = find_long_size(Filename);
	long value;
	int ret;
	for(int i = 0; i < size; i++){	
		ret = fread(&value, sizeof(long), 1, fp);
		add_link_node(&head, value);
	}
	fclose(fp);
	return head;
	
}

int find_long_size(char* Filename){    //find the file size
	int ret;
	int count = 0;
	long* num = NULL;
	FILE* fp = fopen(Filename, "r");
	
	while(!feof(fp)){
		ret = fread(&num, sizeof(long), 1, fp);
		count++;
	}
	count = count - 1;   //while loop count for one more 
	fclose(fp);
	return count;
}

void add_link_node(Node** head, long value){
	if(*head == NULL){
		Node* new_node = build_link_node(value, NULL);
		*head = new_node;
	}
	else{
		Node* tem_pointer = *head;
		while(tem_pointer -> next != NULL){
			tem_pointer  = tem_pointer -> next;
		}
		Node* new_node = build_link_node(value, NULL);
		tem_pointer -> next = new_node;
	}
}

Node* build_link_node(long value, Node* next){
	Node* new_node = malloc(sizeof(Node));
	new_node -> value = value;
	new_node -> next = next;
	return new_node;
}

void print_link_list(Node* head){
	printf("current link list is:\n");
	Node* tem_pointer = head;
	while(tem_pointer -> next != NULL){
		printf("%ld\n", tem_pointer -> value);
		tem_pointer = tem_pointer -> next;
	}
	printf("%ld", tem_pointer -> value);
	printf(".\n");
}

void print_list(List* head){
	printf("current list is:\n");
	List* tem_pointer = head;
	while(tem_pointer -> next != NULL){
		printf("%ld\n", tem_pointer -> node -> value);
		tem_pointer = tem_pointer -> next;
	}
	printf("%ld", tem_pointer -> node -> value);
	printf(".\n");
}

void move_node(Node** node, int step){
	for(int i = 0; i < step; i++){
		*node = (*node) -> next;
	}
}

void add_list_node(List** head, Node* element){
	if(*head == NULL){
		List* new_node = build_list_node(element, NULL);
		*head = new_node;
	}
	else{
		List* tem_pointer = *head;
		while(tem_pointer -> next != NULL){
			tem_pointer  = tem_pointer -> next;
		}
		List* new_node = build_list_node(element, NULL);
		tem_pointer -> next = new_node;
	}
}

List* build_list_node(Node* element, List* next){
	List* new_node = malloc(sizeof(List));
	new_node -> node = element;
	new_node -> next = next;
	return new_node;
}

void bubble_sort_list(List* start_node, int gap, double* N_Cmp){
	bool count_end = false;
	int size = 0;
	Node* temp = NULL;
	List* tem_node = start_node;
	while(count_end == false){
		for(int i = 0; i < gap; i++){
			if(tem_node == NULL){
				count_end = true;
				break;
			}
			tem_node = tem_node -> next;
		}

		if(tem_node == NULL){
				count_end = true;
		}
		size++;          
	}

	//begin to apply bubble sort in each subarray

	List* move_p = start_node;
	List* detect_p = move_p;
	while(size > 1){
		detect_p = next_node(gap, move_p);
		while( detect_p != NULL){
			if ((move_p -> node -> value) > (detect_p -> node -> value)) {   
            	temp = move_p -> node;   
            	move_p -> node = detect_p -> node;  
            	detect_p -> node = temp;  
            }  
            *N_Cmp = *N_Cmp + 1;
            move_p = next_node(gap, move_p);
            detect_p = next_node(gap, detect_p); 
		}
		size--;
		move_p = start_node;
	}

	

}

List* next_node(int gap, List* current_node){
	List* current = current_node;
	for(int i = 0; i < gap; i++){
		if(current == NULL){
			return NULL;
		}
		current = current -> next;
	}
	return current;
}

Node* Shell_Sort_List(Node* list, double* N_Cmp){
	Node* tem_node = list;
	Node* node_head = NULL;
	List* list_head = NULL;
	List* tem_list = NULL;
	int size = 0;
	int k = 0;
	
	
	while(tem_node != NULL){
		add_list_node(&list_head, tem_node);
		tem_node = tem_node -> next;
		size++;
	}
	
	while(k < size){                  
		k = k * 3 + 1;
	}  
	
	for(k = (k - 1)/3; k > 0; k = (k - 1)/3){
		tem_list = list_head;
		for(int i = 0; i < k; i++){
			bubble_sort_list(tem_list, k, N_Cmp);
			tem_list = tem_list -> next;
		}
	}
	
	//link the node together
	tem_list = list_head;
	node_head = list_head -> node;
	while(tem_list -> next != NULL){
		tem_list -> node -> next = tem_list -> next -> node;
		tem_list = tem_list -> next;
	}
	tem_list -> node -> next = NULL;

	free_list(list_head);
	return node_head;
}

int Save_From_List(char* Filename, Node* list){
	FILE* fp = fopen(Filename, "wb");
	Node* temp_node = list;
	int count = 0;
	while(temp_node != NULL){
		fwrite(&(temp_node -> value), sizeof(long), 1, fp);
		temp_node = temp_node -> next;
	}
	fclose(fp);
	return count;
}

void free_list(List* head){
	List* tem_list1 = head;
	List* tem_list2 = head;

	if(head == NULL){
		return;
	}
	tem_list2 = tem_list1 -> next;
	while(tem_list2 != NULL){
		free(tem_list1);
		tem_list1 = tem_list2;
		tem_list2 = tem_list2 -> next;		
	}
	free(tem_list1);
}

/*void free_link(Node* head){
	Node* tem_list1 = head;
	Node* tem_list2 = head;

	if(head == NULL){
		return;
	}
	tem_list2 = tem_list1 -> next;
	while(tem_list2 != NULL){
		free(tem_list1);
		tem_list1 = tem_list2;
		tem_list2 = tem_list2 -> next;		
	}
	free(tem_list1);
}*/
