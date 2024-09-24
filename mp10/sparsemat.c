//yahme6, rkahley2
// The purpose of this program was to create a way to define matrices to maximize memory, as With a sparse matrix, 
// storing every element means wasting a lot of space storing zeroes. The add and multiply functions were written following the pseudocode.
// The save function saves the matrix. gv, returns the value of the element at the given row and column within the matrix, and the destroy function
//frees all memory associated with the matrix.
//  for Load, it opens 'input_file', reads data from the file and returns a matrix of the list of tuples type.
#include "sparsemat.h"
#include <stdio.h>
#include <stdlib.h>




sp_tuples * load_tuples(char* input_file)
{
// Open the file for reading.
  FILE* file = fopen(input_file, "r");
  char junk_char;
 // Allocate memory for the sp_tuples struct that will represent the sparse matrix.
  sp_tuples* ret = (sp_tuples* ) malloc(sizeof(sp_tuples)); 
 // Read the dimensions of the matrix from the file and store them in the sp_tuples struct.
  fscanf(file,"%d%d%c",&(ret->m), &(ret->n), &junk_char);  
  // Initialize the head of the linked list and the non-zero count to NULL and 0, respectively.
  ret->tuples_head = NULL; 
  ret->nz = 0; 
  int checks = 4; 
  int row; 
  int col;
  double value;
  // Continue reading lines from the file until fscanf does not return 4 (which means EOF or error).
  while (checks == 4){
  checks = fscanf(file,"%d%d%lf%c",&(row), &(col), &(value), &junk_char); 
// If 4 items were successfully read, insert/update the tuple in the matrix.
    if (checks == 4){ 
        //call set_tuples
      set_tuples(ret, row, col, value); 
    }
  }
 // Close the file after reading is complete.
  fclose(file);
  return ret;
}


//gv
double gv_tuples(sp_tuples * mat_t,int row,int col)

{
    // Check if the matrix pointer is NULL, which means the matrix doesn't exist.
    if (mat_t==NULL){
        return 0.0; // Return 0.0 since there's no matrix to get values from.
    }
    // Initialize a pointer to traverse the linked list starting from the head node.
    sp_tuples_node * curr = mat_t->tuples_head;

    if (curr == NULL){
        return 0.0;
    }
        // Loop through each node in the linked list to find the specified row and column.

while (curr!=NULL){
    // If the current node's row and column match the requested row and column...
if (row ==curr->row && col ==curr->col){
    return curr-> value;
}
// Move to the next node in the list to continue searching.
curr = curr->next;
}
    return 0.0;
}




void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
// Initially create a new node for possible insertion.
  sp_tuples_node* sp_matrix = (sp_tuples_node*) malloc(sizeof(sp_tuples_node));
  sp_matrix->row = row;
  sp_matrix->col = col;
  sp_matrix->value = value; 

 
  // Start at the head of the list.
  sp_tuples_node** node = &(mat_t->tuples_head); 
  int row_nodes = (*node)->row;
  int col_nodes = (*node)->col;

  // Iterate through the nodes to find the position where the new value should go.
  while (*node != NULL){
     // If the current node matches the specified row and column...
    if(row_nodes == row &&  col_nodes == col){ 
      free(sp_matrix); 
      // If the new value is non-zero, update the existing node.
      if (value != 0){ 
   (*node)->value = value; 
      }
      else{
 // If the new value is zero, remove the current node from the list.
  sp_tuples_node* temp = (*node)->next;
  free(*node); 
  *node = temp; 
  mat_t->nz --; 
      }
      return;
    }
    // If the current node is past the position where the new node should go
    else if (( row_nodes > row) || ((row_nodes == row) && (col_nodes  > col))){ 
      if (value != 0){
  sp_matrix->next = *node;
  *node = sp_matrix; 
  mat_t->nz ++;
  return; 
      }
      // Free the new node as its value is zero and hence not needed.
      free(sp_matrix); 
      return;
    }
      // If the end of the list is reached and no insertion has happened
    node = &((*node)->next);
  }
  if (*node == NULL){
    if (value != 0){
      sp_matrix->next = *node;
      *node = sp_matrix; 
      mat_t->nz ++; 
    // If the value is zero, there's no need to insert a node for it.

    } 
  } 
  return;
}

void save_tuples(char * file_name, sp_tuples * mat_t)
{
    if (mat_t != NULL){ // if the matrix is not empty... 
    FILE *stream = NULL; // begin a stream to write matrix into
    stream = fopen(file_name, "w"); // open the file for writing
    fprintf(stream, "%d %d\n", mat_t->m, mat_t->n); // print number of rows and columns
 
  sp_tuples_node *current = mat_t->tuples_head; //create a pointer to the first structure in linked list
  for (int i = 0; i < mat_t->nz; i++){ // cycle through each non-zero entry in the matrix
    fprintf(stream, "%d %d %1f\n", current->row, current->col, current->value); // print data to the file
    current = current->next; // go to the next item in the list
  }
  fclose(stream); // done writing to the file, so close it
  }
  return;
}

sp_tuples *add_tuples(sp_tuples *matA, sp_tuples *matB) {//
    if (matA->m != matB->m || matA->n != matB->n) {//if A does not have the same dimensions as B, return NULL
        return NULL;
    }

    sp_tuples *matrixC = (sp_tuples *)malloc(sizeof(sp_tuples));//malloc size of A for size of C
    matrixC->m = matA->m;//set rows of C as rows of A
    matrixC->n = matA->n;//set cols of C as cols of A
    matrixC->nz = 0;//set nonzeros to 0
    matrixC->tuples_head = NULL;

    sp_tuples_node *curr = matA->tuples_head;//initialize curr to head pointer
    while (curr != NULL) {//while curr is not NULL
        int Column = curr->col;//initialize Column to cols of A
        int Row = curr->row;//initialize Row to rows of A
        double value = curr->value;//initilaize value to value of A
        set_tuples(matrixC, Row, Column, value);//assigns the specific location of Row&Column the value
        curr = curr->next;//next item in linked list
    }

    curr = matB->tuples_head;//reinitializing curr to point to the head of matB
    while (curr != NULL) {
        int Column = curr->col;//reinitializing Column
        int Row = curr->row;//reinitializing Row
        double value = curr->value;//Reintitializing value
        set_tuples(matrixC, Row, Column, value + gv_tuples(matrixC, Row, Column));// assigning matrix C the value currently at C + value from B 
        curr = curr->next;//next item in linked list
    }

    return matrixC;
}



// sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ //this one will not be graded
//     return retmat;

//}


  
void destroy_tuples(sp_tuples * mat_t){
  if (mat_t != NULL){ // if the matrix is not empty... 
    sp_tuples_node *freer = NULL; // initialize a temporary variable to free memory for each item in matrix
    sp_tuples_node *current = mat_t->tuples_head; // make a pointer to the first item in list

    while (current != NULL){ // cycle through each element in the matrix
      freer = current->next; // set the temporary variable to the next element
      free(current); // free the memory for the current element
      current = freer; // set the current element to the one pointed to by temporary variable
    }
    free(mat_t); // free the structure itself
  }
  return;
// Less sure about this one. May need to change the for loop to:
// while (current != NULL){
// everything else the same
// }
    // return;
}  