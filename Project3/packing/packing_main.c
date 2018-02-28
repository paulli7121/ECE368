#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "packing.h"

int main(int argc, char** argv){
	FILE* fp1 = fopen(argv[1], "r");
	FILE* fp2 = fopen(argv[1], "r");
	FILE* fp3 = fopen(argv[2], "w");
	FILE* fp4 = fopen(argv[3], "w");
	FILE* fp5 = fopen(argv[4], "w");
	Node* head = NULL;
	double max_o1 = 0;
	double max_o2 = 0;
	double curr_o1 = 0;
	double curr_o2 = 0;
	
	load_file(fp1, fp2, &head);
	print_tree_post(head, fp3);
	
	add_dimension(head, &max_o1, &max_o2);
    print_dimension(head, fp4);
    
    change_coor(head, curr_o1, curr_o2, fp5);

    free_node(head);
    //print_packing(head, fp3);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);

	return 0;
}

