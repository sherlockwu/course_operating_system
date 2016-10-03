#include "varsort.h"

extern int R;

int main(int argc, char * argv[]){
	extern int R;
	char * input_file_name;
	char * output_file_name; 	
	int input_file;
	int output_file;
	RECORD * record_arr;


	// TODO use tool to test mem leak
	// input file    
	if ( argc != 5){
		die("usage: ./sort -i xxx -o xxx"); 
	}
	
	input_file_name = (char *)malloc(MAX_NAME * sizeof(char));
	if (input_file_name == NULL){
		die("malloc fail for input_file_name");
	}
	output_file_name = (char *)malloc(MAX_NAME * sizeof(char));
	if (output_file_name == NULL){
		die("malloc fail for output_file_name");
	}
	get_file_names(argv, input_file_name, output_file_name);

	
	//file operations
	input_file = open_file(input_file_name, 0);
	output_file = open_file(output_file_name, 1);
	free(input_file_name); free(output_file_name);
	

	//input  &  store  to the datastructure 
	get_R(input_file);
	record_arr = (RECORD *)malloc(sizeof(RECORD)*R);      //TODO fails!
	if (record_arr == NULL){
		die("malloc fail for record_arr");
	}
	readin(input_file, record_arr); 

	// sort   
	RECORD ** record_pointer_arr;
	record_pointer_arr = sort(record_arr);

	
	// output to file 
	writeout(output_file, record_pointer_arr); 

	

	// close files  free mem 
	free_everything(record_arr, record_pointer_arr);
	
	close(input_file);
	close(output_file);
	

	return 0; 
}

