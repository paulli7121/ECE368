#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sorting.h"


//int find_long_size(char* Filename);
//void print_link_list(Node* head);
//void print_list(List* head);
void free_link(Node* head);


int main(int argc, char** argv){
	double N_Cmp = 0;
	int count = 0;
	double io = 0;
	double sort = 0;
	
	if(strcmp(argv[1],"-l") == 0){
		clock_t start_read = clock();
		Node* array = Load_Into_List(argv[2]);
		clock_t end_read = clock();
	
		clock_t start_sort = clock();
		array = Shell_Sort_List(array, &N_Cmp);
		clock_t end_sort = clock();
	
		clock_t start_save = clock();
		count = Save_From_List(argv[3], array);
		clock_t end_save = clock();
		io = ((double)end_read - (double)start_read + (double)end_save - (double)start_save)/(double)CLOCKS_PER_SEC;
		sort = ((double)end_sort - (double)start_sort)/(double)CLOCKS_PER_SEC;
		free_link(array);
		
	}
	else if(strcmp(argv[1],"-a") == 0){
		int size = 0;
		clock_t start_read = clock();
		long* array = Load_Into_Array(argv[2], &size);
		clock_t end_read = clock();
	
		clock_t start_sort = clock();
		Shell_Sort_Array(array, size, &N_Cmp);
		clock_t end_sort = clock();
	
		clock_t start_save = clock();
		count = Save_From_Array(argv[3], array, size);
		clock_t end_save = clock();
		io = ((double)end_read - (double)start_read + (double)end_save - (double)start_save)/(double)CLOCKS_PER_SEC;
		sort = ((double)end_sort - (double)start_sort)/(double)CLOCKS_PER_SEC;
		free(array);
	}
	else{
		printf("Wrong argument.\n");
		return EXIT_FAILURE;
	}
	

	printf("I/O time: %le.\n", io);
	printf("Sorting time: %le.\n", sort);
	printf("Number of comparisions: %le.\n", N_Cmp);
	
	

	return EXIT_SUCCESS;
}

void free_link(Node* head){
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
}
