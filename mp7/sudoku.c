#include "sudoku.h"

int check_sudoku_filled(const int soduku[9][9]);

int find_empty(int *empty1,int *empty2, const int sudoku[9][9]);
/*
ziada2
Sudoku puzzle using recursive backtracking. A standard Sudoku puzzle contains 81 cells,
 in a 9 by 9 grid, and has 9 zones. Each zone is the intersection of 3 rows and 3 columns 
 (e.g. size 3x3). Each cell may contain a number from 1 to 9 and each number can only occur once in
  each 3x3 zone, row, and column of the grid. At the beginning of the game, several cells begin with numbers, 
  and the goal is to fill in the remaining cells with numbers satisfying the puzzle rules. Unfilled locations will be set to 0.
 
  There are four main functions in this program:
  int is_val_in_row:
  checks for validity of new sudoku digit given by num through a row, simply using a for loop

int is_val_in_col:
  checks for validity of new sudoku digit given by num through a coloumn, simply using a for loop

int is_val_in_3x3_zone:
  checks for validity of new sudoku digit given by num through a 3x3 box, using a nested for loop to iterate through 
  box and integer division to find where box is. 

int is_val_valid: 
    runs all three is_val_in_x comands to check overall validity, i.e. num is unqiue and a valid sudoku placement

int solve_sudoku:
recursive function, that calls back solve_sudoku and calls two helper functions check_sudoku_filled and check_empty, both perform similar functions 
check_sudoku_filled, ensures that all sudoku 'cells' are filled in from 1-9 (inclusive)
check_empty, finds the locations in the 9x9 sudoku table and gives the addresses using pointers empty1 and empty2

   */
// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);
  // 3x3 = 9, hence max cols
  for (int cols = 0; cols < 9; cols++){
    //check if col is found in val 
    if (sudoku[i][cols]==val)
    return 1;
  }
  return 0;

}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);
  //3x3 = 9, hence max rows
  for (int rows = 0; rows < 9; rows++){ 
    // check if col is found in val 
    if (sudoku[rows][j]==val)
    return 1;
  

}
return 0;
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9 && j>=0 && j<9);

// iterate through smaller boxes, or sub sudokus using the nested for loop
  for (int row_box = 0; row_box < 3; row_box++){
    for (int col_box = 0; col_box <3; col_box++){ 
      // integer division to check where i and j are located, which is given from solve_sudoku

      if (i/3 == row_box && j/3 == col_box ){ 
        for (int rows = (i/3)*3; rows <= (i/3)*3+2 ; rows++){ 
          //start at the beginning of the given box, and end at 3 after (giving one box)
          for (int cols = (j/3)*3; cols <= (j/3)*3+2 ; cols++ ){
              // check if val is in the box
              if (sudoku[rows][cols] == val){
                return 1;
            }        
          } 
        }
       } 
      }
    }
     return 0;
  }




// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);
  //run all is_val_in_x and if zero then return 1 since value can be filled.
  if(
  is_val_in_row(val, i, sudoku) == 0 &&
  is_val_in_col(val, j, sudoku) == 0  &&
  is_val_in_3x3_zone(val, i, j, sudoku) == 0){

  return 1;

} else {
  return 0;
}
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]){
  
  //call helper function to check if there are any zeros, i.e. empty cells.
  if (check_sudoku_filled(sudoku)){
    return 1;
  }
    int empty1;
    int empty2;
    //call find empty, to give back locations in the suduku of the fhe empty cells to fill in later on 
  if (find_empty(&empty1, &empty2, sudoku)){
    
    //these are the numbers that are filled in the sudoku
  for (int num = 1; num <= 9; num++) { 

    //call is_val_valid, to check if space is valid according to sudoku rules
    if (is_val_valid(num, empty1, empty2, sudoku)){ 
      //if meets sudoku rules then replace with num
      sudoku[empty1][empty2] = num; 
      //recursive function, giving back the new sudoku matrix that has been adjusted. 
      if (solve_sudoku(sudoku)){
        
        return 1;

      }
      //if solve_sudoku is invalid, then fill in with zero. 
      sudoku[empty1][empty2] = 0; 

      }

    }
  }
  return 0;
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  //print out sudoku using nested for loop to iterate through matrix. 
  int i, j;
  //3x3 = 9, so size of max column and max row
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}

//helper function to check if sudoku is filled up, i.e. doesn't have any zeros.
int check_sudoku_filled( const int sudoku[9][9]){
  //3x3 = 9, so size of max column and max row
  for (int i = 0; i < 9; i++){  
    for (int j = 0 ; j < 9; j++){
      //check if it's zero, since zero indicates empty array 
      if (sudoku[i][j] == 0){
        return 0;
    }
   }
  }
  return 1;
}
//helper function to locate empty cells in sudoku matrix.
int find_empty(int *empty1, int *empty2, const int sudoku[9][9]){
  
  //3x3 = 9, max column and max rows = 9
  for(int i = 0; i < 9; i++){
    for (int j = 0 ; j < 9; j++){
      
      if (sudoku[i][j]==0){
        //set to empty 1 to get back in solve_sudoku
        *empty1 = i;
        *empty2 = j;
        return 1;
      }

  
  }
  }
  return 0;
}




 