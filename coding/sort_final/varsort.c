// Copyright [2016] <Kan Wu>
// see header file in varsort.h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <assert.h>
#include <sys/stat.h>

#define MAX_NAME 100
#define MAX_DATA_INTS USHRT_MAX

int R;


typedef struct {
    unsigned int key;
    unsigned int size;
    int * data;
} RECORD;

void get_file_names(char * argv[],
    char * input_file_name,
    char * output_file_name);
int open_file(char * file_name, int type);
void get_R(int input_file);
void readin(int input_file, RECORD * record_arr);
RECORD ** my_sort(RECORD * record_arr);
int qsort_cmp(const void * a, const void * b);
void writeout(int output_file, RECORD ** record_pointer_arr);
void free_everything(RECORD * record_arr, RECORD ** record_pointer_arr);
void die(char * message);



int main(int argc, char * argv[]) {
  extern int R;
  char * input_file_name;
  char * output_file_name;
  int input_file;
  int output_file;
  RECORD * record_arr;


  // input file
  if (argc != 5) {
    die("usage: ./sort -i xxx -o xxx");
  }

  input_file_name = (char *)malloc(MAX_NAME * sizeof(char));
  if (input_file_name == NULL) {
    die("malloc fail for input_file_name");
  }
  output_file_name = (char *)malloc(MAX_NAME * sizeof(char));
  if (output_file_name == NULL) {
    die("malloc fail for output_file_name");
  }
  get_file_names(argv, input_file_name, output_file_name);


  // file operations
  input_file = open_file(input_file_name, 0);
  output_file = open_file(output_file_name, 1);
  free(input_file_name); free(output_file_name);


  // input  &  store  to the datastructure
  get_R(input_file);
  record_arr = (RECORD *)malloc(sizeof(RECORD)*R);
  if (record_arr == NULL) {
    die("malloc fail for record_arr");
  }
  readin(input_file, record_arr);

  // sort
  RECORD ** record_pointer_arr;
  record_pointer_arr = my_sort(record_arr);


  // output to file
  writeout(output_file, record_pointer_arr);



  // close files  free mem
  free_everything(record_arr, record_pointer_arr);

  close(input_file);
  close(output_file);


  return 0;
}



// get file names to read from and to write in from the input
void get_file_names(char * argv[],
  char * input_file_name, char * output_file_name) {
    // -i
        // judge
        if (strcmp(argv[1], "-i") != 0) {
            die("the first option should be -i");
        }
        // get name
        int ret = snprintf(input_file_name, MAX_NAME, "%s", argv[2]);
    // -o
        // judge
        if (strcmp(argv[3], "-o") != 0) {
            die("the third option should be -o");
        }
        // get name
        ret = snprintf(output_file_name, MAX_NAME, "%s", argv[4]);

    return;
}

// open the input file and the output file according to type argument
int open_file(char * file_name, int type) {
    int file_handler;
    int ret;
    switch (type) {
        // read
        case 0:
            file_handler = open(file_name, O_RDONLY);
            if (file_handler < 0) {
                char message[MAX_NAME+20];
                ret = snprintf(message, MAX_NAME+20,
                 "%s %s", "Cannot open file", file_name);
                die(message);
            }
            break;
        // write
        case 1:
            file_handler = open(file_name, O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU);
            if (file_handler < 0) {
                die("fail to open output_file");
            }
            break;

        default:
            die("Wrong type input to open_file");
    }
    return file_handler;
}

// read the R from the input file
void get_R(int input_file) {
    extern int R;
    int rc;

    rc = read(input_file, &R, sizeof(int));
    if (rc != sizeof(R)) {
        die("fail to read R");
    }
    return;
}

// read in R records from the input file into the record_arr data structure
void readin(int input_file, RECORD * record_arr) {
    extern int R;
    int rc, i;
    // each read in
    for (i = 0; i < R; i++) {
        // Key
        rc = read(input_file, &(record_arr[i].key), sizeof(unsigned int));
        if (rc != sizeof(unsigned int)) {
            die("fail to read");
        }
        // Size
        rc = read(input_file, &(record_arr[i].size), sizeof(unsigned int));
        if (rc != sizeof(unsigned int)) {
            die("fail to read");
        }
        // Data
        record_arr[i].data = (int *)malloc(sizeof(int)*(record_arr[i].size));
        assert(record_arr[i].size <= MAX_DATA_INTS);
        rc = read(input_file, record_arr[i].data,
         record_arr[i].size * sizeof(unsigned int));
        if (rc != record_arr[i].size * sizeof(unsigned int)) {
            die("fail to read");
        }
    }
    return;
}


// using qsort to sort
RECORD ** my_sort(RECORD * record_arr) {
    int i;
    // initialize address array
    RECORD ** record_pointer_arr;
    record_pointer_arr = (RECORD **)malloc(sizeof(RECORD *) * R);
    if (record_pointer_arr == NULL) {
        die("malloc fail for record_pointer_arr");
    }
    for (i = 0; i < R; i++) {
        record_pointer_arr[i] = record_arr+i;
    }
    // quicksort on the array
    qsort(record_pointer_arr, R, sizeof(RECORD *), qsort_cmp);
    return record_pointer_arr;
}


// compare function for qsort
int qsort_cmp(const void * a, const void * b) {
    RECORD * tmp_a;
    RECORD * tmp_b;
    tmp_a = *(RECORD **)a;
    tmp_b = *(RECORD **)b;
    return (tmp_a->key - tmp_b->key);
}

// output the sorted data structure to the output file
void writeout(int output_file, RECORD ** record_pointer_arr) {
    // R
    int rc, i, j;
    rc = write(output_file, &R, sizeof(R));
    if (rc != sizeof(R)) {
        die("fail to write");
    }
    // Each record
    for (i = 0; i < R; i++) {
        // key
        rc = write(output_file, &((record_pointer_arr[i])->key),
         sizeof(unsigned int));
        if (rc != sizeof(unsigned int)) {
            die("fail to write");
        }
        // size
        rc = write(output_file, &((record_pointer_arr[i])->size),
         sizeof(unsigned int));
        if (rc != sizeof(unsigned int)) {
            die("fail to write");
        }
        // data
        for (j = 0; j < (record_pointer_arr[i])->size; j++) {
            rc = write(output_file, ((record_pointer_arr[i])->data)+j,
             sizeof(unsigned int));
            if (rc != sizeof(unsigned int)) {
                die("fail to write");
            }
        }
    }

    return;
}

// free record_arr and record_pointer_arr
void free_everything(RECORD * record_arr, RECORD ** record_pointer_arr) {
    int i;
    // free every data of records
    for (i = 0; i < R; i++) {
        free(record_arr[i].data);
    }
    // free record_arr
    free(record_arr);
    // free record_pointer_arr
    free(record_pointer_arr);

    return;
}



void die(char * message) {
    fprintf(stderr, "Error: %s\n", message);
    exit(1);
    return;
}
