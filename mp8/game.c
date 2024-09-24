/* ziada2, yahme6
This implementation of the 2048 game is game on a variable sized grid.  
Upon launching the game, the program will ask the user for dimensions. 
This input is expected as 2 integers (rows and columns) separated by a space 
(e.g. '4 4' for the standard 4x4 grid).  After configuring board size, the game beings.  
In addition to the directional controls (w,a,s,d), your version will use n to reset the game, and q to quit the game.  '
n' will recreate the game board with new dimensions, setting all cells to negative one, and randomly adding one tile.
 'q' will output a "Quitting.." message and terminate the program.

 This program is split up into different functions, we worked on:
game * make_game(int rows, int cols);
void remake_game(game ** _cur_game_ptr, int new_rows, int new_cols);
cell * get_cell(game * cur_game, int row, int col);
int move_w(game * cur_game);
int move_s(game * cur_game);
int move_a(game * cur_game);
int move_d(game * cur_game);
int legal_move_check(game * cur_game);
 

 */

#include "game.h"


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    int rows;
	int cols
    cell * cells;
	int score;
    The needed memory should be dynamically allocated with the malloc family
    of functions.
    */
{

    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    int score = 0;
    mygame->score = score; // Whenever 2 tiles merge, their sum is added to the total score.
    mygame->rows = rows; // get rows from mygame, and set to rows in make_game
    mygame->cols= cols; // get cols from my game and set to cols in make_game
    


    //moving through board using a nested forloop
    for (int i = 0; i < rows; i++){ 
        for (int j =0 ; j < cols; j++){
            mygame->cells[i*cols+j] = -1; // fill in with -1, which represents empty cell.
        }
       
    }
    //return the mygame struct.
    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
    (*_cur_game_ptr)->rows = new_rows; //set *_cur_game_ptr i.e. the pointer of the mygame struct to new_rows
    (*_cur_game_ptr)->cols = new_cols; //set *_cur_game_ptr i.e. the pointer of the mygame struct to new_cols 
    (*_cur_game_ptr)-> score = 0; // set score to 0
        

        //move through array using nested for loop
       for (int i = 0; i < new_rows; i++){ 
            for (int j =0; j < new_cols; j++){
                (*_cur_game_ptr)->cells[i*new_cols+j] = -1; // fill in with -1, which represents empty cell.
        }
    }

	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    // free allocated memory of cur_game->cells:
    free(cur_game->cells);
    //free allocated memory of entire cur_game
    free(cur_game);
    // you free in this order since cells is an array within cur_game, if you were to do free(cur_game) first, 
    //you will have empty memory which is used up by cur_game->cells and will not be able to access it 
    //set cur_game to NULL
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    //check if out of bounds for rows, i.e if less than 0 so negative or greater than or equal to the max rows
    if (row < 0 || row >= cur_game->rows){ 
        return NULL;
    }
    //check if out of bounds for cols, if less than 0 so negative or greater than or equal to the max cols
    if (col < 0 || col >= cur_game->cols){
        return NULL;
    }
    //return the address of the cell after ensuring it is inbound.
    return &(cur_game->cells[row*(cur_game->cols)+col]);
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. 
   A tile can not merge twice in one turn. 
   If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //split up into three sections, slide, merge, slide.
    //YOUR CODE STARTS HERE

    //create flag array: flag array ensures that there is no over mergering, i.e. merging more than once  
    int flag_array[(cur_game->rows)*(cur_game->cols)];
    ///clear flag array using nested for loops
    for (int i = 0; i < (cur_game->rows); i++){
        for (int j = 0; j < (cur_game->cols); j++){
        flag_array[i*cur_game->cols+j] = 0; //initialize flag array to zero
    }
    }
    // init max_rows and max_cols just for the for loop conditions to look more organized
    int max_rows = 0;
    int max_cols = 0;
    // set max rows and max cols to cur_game's respective value. 
    max_rows = cur_game->rows;
    max_cols = cur_game->cols;
    //initialize flag, this flag ensures that move is valid or not for legal_move function
    int flag = 0; 
    //sliding from LAB:
    for (int j = 0; j < max_cols;j++){ //every columm
        for (int i = 0 ; i < max_rows; i++){ //every row
            if(cur_game->cells[i*max_cols+j] != -1){ //cell not empty
                    for (int k = 0; k < i; k++){ //find empty cell, this is the current cell. 
                        if(cur_game->cells[k*max_cols+j] == -1){ //if the current cell,k, is empty then:
                            cur_game->cells[k*max_cols+j] = cur_game->cells[i*max_cols+j]; //copy from i,j to k,j, i.e move it to one space below
                            cur_game->cells[i*max_cols+j] = -1; //erase value in i,j.
                            flag = 1; // flag for legal move checker
                        } 
                }
            }
        }
        
    }
    
  for (int j = 0; j < (cur_game->cols); j++) {
    //int merged = 0; // Use this flag to track if a merge has occurred in the current column
    for (int i = 0; i < (cur_game->rows); i++) {

        // if current cell is empty
        if ((cur_game->cells[(i)*cur_game->cols+j]) != -1){
            // and if cur cell is equal to cell below it (after sliding) and flag array of both cell positions is 0, i.e. has not been merged there before
            if((cur_game->cells[i*cur_game->cols+j] == cur_game->cells[(i+1)*cur_game->cols+j])){
                //and flag array of both cell positions is 0, i.e. has not been merged there before
                if((flag_array[(i+1)*cur_game->cols+j]== 0) && (flag_array[i*cur_game->cols+j] == 0)){
                // Merge logic
                    //add the old cell value to the value to above, i.e one row above (i+1)
                    cur_game->cells[(i+1)*cur_game->cols+j] += cur_game->cells[i*cur_game->cols+j];
                    // make old value empty after 'adding'
                    cur_game->cells[i*cur_game->cols+j] = -1;
                    // add to total score to the sum found above to 
                    cur_game->score += cur_game->cells[(i+1)*cur_game->cols+j];
                    // set merge and merged cells position to 1 in flag array 
                    flag_array[(i+1)*cur_game->cols+j] = 1;
                    flag_array[(i)*cur_game->cols+j] = 1; 
            }
        }
    }
  }
}

 for (int j = 0; j <max_cols;j++){//every columm, colomn is first since you iterate through every row, then check next column, so row by row. 
        for (int i = 0; i < max_rows; i++){// from top to bottom
                if(cur_game->cells[i*max_cols+j] != -1){ // cell not empty
                    for (int k = 0; k < i; k++){ //find empty cell position 
                        if(cur_game->cells[k*max_cols+j] == -1){ //found an empty cell
                            cur_game->cells[k*max_cols+j] = cur_game->cells[i*max_cols+j]; //copy form i,j to k,j
                            cur_game->cells[i*max_cols+j] = -1; //erase value in i,j
                            flag = 1; // set flag to 1 for legal move checker
                        } 
                }
            }
        }
    }
 return flag;
};

int move_s(game * cur_game) //slide down
{
    int flag_array[(cur_game->rows)*(cur_game->cols)];
    for (int i = 0; i < (cur_game->rows)*(cur_game->cols); i++){
        flag_array[i] = 0; //initialize flag array to zero
    }
    int flag = 0;
    int max_rows = 0;
    int max_cols = 0;
    max_rows = cur_game->rows;
    max_cols = cur_game->cols;
    //sliding from LAB boundries adjusted
    for (int j = 0; j < max_cols; j++){//every columm
        for (int i = max_rows-1; i >= 0; i--){// from bottom to top 
                if(cur_game->cells[i*max_cols+j] != -1){ // cell not empty
                    for (int k = max_rows-1; k > i; k--){//find empty cell 
                        if(cur_game->cells[k*max_cols+j] == -1){//found an empty cell
                            cur_game->cells[k*max_cols+j] = cur_game->cells[i*max_cols+j]; //copy form i,j to k,j
                            cur_game->cells[i*max_cols+j] = -1; //erase value in i,j
                            flag = 1;
                            
                     } 
                }
            }
        }
    }
    
for (int j = 0; j < (cur_game->cols); j++) {
    for (int i = 0; i < (cur_game->rows); i++) {
        if ((cur_game->cells[i*cur_game->cols+j]) == (cur_game->cells[(i-1)*cur_game->cols+j]) && (cur_game->cells[(i-1)*cur_game->cols+j] != -1) 
        && (flag_array[(i-1)*cur_game->cols+j]==0) && (flag_array[(i)*cur_game->cols+j]==0))
          // if current cell is emptyand if cur cell is equal to
            //cell below it (after sliding) and flag array of both cell 
            //positions is 0, i.e. has not been merged there before:
         {
            // Merge logic
            // add the old cell value to the value to above, i.e one row above (i+1)                    
            // make old value empty after 'adding'                    
            // add to total score to the sum found above to                 
            // set merge and merged cells position to 1 in flag array 

            cur_game->cells[(i-1)*cur_game->cols+j] += cur_game->cells[i*cur_game->cols+j];
            cur_game->cells[i*cur_game->cols+j] = -1;
            cur_game->score += cur_game->cells[(i-1)*cur_game->cols+j];
            // Use this flag to track if a merge has occurred in the current column
            flag_array[(i-1)*cur_game->cols+j] =1;
            flag_array[(i)*cur_game->cols+j] = 1;
        }
    }
}

    for (int j = 0; j < max_cols; j++){//every columm
        for (int i = max_rows-1; i >= 0; i--){// from bottom to top 
                if(cur_game->cells[i*max_cols+j] != -1){ // cell not empty
                    for (int k = max_rows-1; k >= i; k--){//find empty cell 
                        if(cur_game->cells[k*max_cols+j] == -1){//found an empty cell
                            cur_game->cells[k*max_cols+j] = cur_game->cells[i*max_cols+j]; //copy form i,j to k,j
                            cur_game->cells[i*max_cols+j] = -1; //erase value in i,j
                            flag = 1;
                        } 
                            
                }
            }
        }
    }

    return flag;
};

int move_a(game * cur_game) //slide left
{
    int flag_array[(cur_game->rows)*(cur_game->cols)];
    for (int i = 0; i < (cur_game->rows)*(cur_game->cols); i++){
        flag_array[i] = 0; //initialize flag array to zero
    }
    //YOUR CODE STARTS HERE
    int flag = 0;
    int max_rows = 0;
    int max_cols = 0;
    max_rows = cur_game->rows;
    max_cols = cur_game->cols;
    //sliding from LAB boundries adjusted
for (int i = 0; i < max_rows; i++){//rows  
    for (int j = 0; j < max_cols ; j++){//from left to right
                if(cur_game->cells[i*max_cols+j] != -1){ // cell not empty
                    for (int k = 0; k < j ; k++){//find empty cell   
                        if(cur_game->cells[i*max_cols+k] == -1){//found an empty cell
                            cur_game->cells[i*max_cols+(k)] = cur_game->cells[i*max_cols+j]; //copy form i,j to k,j
                            cur_game->cells[i*max_cols+j] = -1; //erase value in i,j
                                flag = 1;
                        }    
                    }
                }
            }
        }
        

for (int i = 0; i < (cur_game->rows); i++) {
    for (int j = 0; j < (cur_game->cols); j++) {
        if ((cur_game->cells[i*cur_game->cols+j]) == (cur_game->cells[(i)*cur_game->cols+(j+1)]) && (cur_game->cells[i*cur_game->cols+(j+1)]!= -1)
        && (flag_array[i*cur_game->cols+(j+1)]== 0) && (flag_array[i*cur_game->cols+(j)] == 0))
        {
            // if current cell is emptyand if cur cell is equal to
            //cell below it (after sliding) and flag array of both cell 
            //positions is 0, i.e. has not been merged there before:

            // Merge logic
            // add the old cell value to the value to above, i.e one row above (i+1)                    
            // make old value empty after 'adding'                    
            // add to total score to the sum found above to                 
            // set merge and merged cells position to 1 in flag array 

            cur_game->cells[(i)*cur_game->cols+(j+1)] += cur_game->cells[i*cur_game->cols+j];
            cur_game->cells[i*cur_game->cols+j] = -1;
            cur_game->score += cur_game->cells[i*cur_game->cols+(j+1)];
            // Check if a merge has occurred in this column
            flag_array[(i)*cur_game->cols+j] =1;
            flag_array[(i)*cur_game->cols+(j+1)] = 1;
        }
    }
    
}
for (int i = 0; i < max_rows; i++){//rows  
    for (int j = 0; j < max_cols ; j++){//from left to right
                if(cur_game->cells[i*max_cols+j] != -1){ // cell not empty
                    for (int k = 0; k < j ; k++){//find empty cell   
                        if(cur_game->cells[i*max_cols+k] == -1){//found an empty cell
                            cur_game->cells[i*max_cols+(k)] = cur_game->cells[i*max_cols+j]; //copy form i,j to k,j
                            cur_game->cells[i*max_cols+j] = -1; //erase value in i,j
                                flag = 1;
                        }    
                    }
                }
            }
        }
        
    
    
    return flag;
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
    int flag_array[(cur_game->rows)*(cur_game->cols)];
    for (int i = 0; i < (cur_game->rows)*(cur_game->cols); i++){
        flag_array[i] = 0; //initialize flag array to zero
    }
    int flag = 0;
    int max_rows = 0;
    int max_cols = 0;
    max_rows = cur_game->rows;
    max_cols = cur_game->cols;
    //sliding from LAB boundries adjusted
for (int i = max_rows-1; i >=0; i--){ //rows, process each row first
    for (int j = max_cols-1; j >= 0  ; j--){ //from right to left 
                if(cur_game->cells[i*max_cols+j] != -1){ // cell not empty
                    for (int k = max_cols-1; k > j ; k--){//find empty cell   
                        if(cur_game->cells[i*max_cols+k] == -1){//found an empty cell
                            cur_game->cells[i*max_cols+k] = cur_game->cells[i*max_cols+j]; //copy form i,j to k,j
                            cur_game->cells[i*max_cols+j] = -1; //erase value in i,j
                                flag =1;
                        }    
                    }
                }
            }
        }
for (int j = max_cols-1; j >=0; j--) {        
    for (int i = max_rows-1; i >=0; i--) {

        if (cur_game->cells[i*cur_game->cols+j] == cur_game->cells[(i)*cur_game->cols+(j-1)] && (cur_game->cells[i*cur_game->cols+(j-1)]!= -1)
        && (flag_array[(i)*cur_game->cols+j]==0) && (flag_array[i*cur_game->cols+(j-1)] == 0))
        {
             // if current cell is emptyand if cur cell is equal to
            //cell below it (after sliding) and flag array of both cell 
            //positions is 0, i.e. has not been merged there before:
            
            
            // Merge logic  
            // add the old cell value to the value to above, i.e one row above (i+1)                    
            // make old value empty after 'adding'                    
            // add to total score to the sum found above to                 
            // set merge and merged cells position to 1 in flag array 
            
            cur_game->cells[(i)*cur_game->cols+(j-1)] += cur_game->cells[i*cur_game->cols+j];
            cur_game->cells[i*cur_game->cols+j] = -1;
            cur_game->score += cur_game->cells[i*cur_game->cols+(j-1)];
            flag_array[(i)*cur_game->cols+j] =1;
            flag_array[(i)*cur_game->cols+(j-1)] = 1;
        }
    }
}

for (int i = max_rows-1; i >=0; i--){//rows 
    for (int j = max_cols-1; j >= 0  ; j--){//from right to left 
                if(cur_game->cells[i*max_cols+j] != -1){ // cell not empty
                    for (int k = max_cols-1; k > j ; k--){//find empty cell   
                        if(cur_game->cells[i*max_cols+k] == -1){//found an empty cell
                            cur_game->cells[i*max_cols+k] = cur_game->cells[i*max_cols+j]; //copy form i,j to k,j
                            cur_game->cells[i*max_cols+j] = -1; //erase value in i,j
                                flag = 1;
                        }    
                    }
                }
            }
        }
return flag;
}
int legal_move_check(game * cur_game)
{
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.

    
	Return 1 if there are possible legal moves, 0 if there are none.
 */
 
//    for(int row = 0; row < (cur_game->rows); row++){
//         for(int col = 0; col < (cur_game->cols); col++){ // double for loop
            
//             if(row < (cur_game->rows-1) && cur_game->cells[row*(cur_game->cols) + col] == cur_game->cells[(row+1)*(cur_game->cols) + col]){
//                 return 1; 
//             }
//             if(row > 0 && cur_game->cells[row*(cur_game->cols) + col] == cur_game->cells[(row-1)*(cur_game->cols) + col]){
//                 return 1; 

//             }
//             if(col > 0 && cur_game->cells[row*(cur_game->cols) + col] == cur_game->cells[(row-1)*(cur_game->cols) + col-1]){
//                 return 1; 

//             }
//             if(col < (cur_game->cols-1) && cur_game->cells[row*(cur_game->cols) + col] == cur_game->cells[(row+1)*(cur_game->cols) + col+1]){
//                 return 1; 

//             }
            
//             if(cur_game->cells[row*(cur_game->cols) + col] == -1){
//                 return 1;
//             }
//         }
//     }

//     return 0;
// }
    game * deep_copy = malloc(sizeof(game));

    deep_copy->cells = malloc((cur_game->rows)*(cur_game->cols)*sizeof(cell));
    // create deep copy struct and set to same restrictions of cur_game using: 
    //mygame->cells = malloc(rows*cols*sizeof(cell)); from previous code

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    // int score =0;
    // int rows =0;
    // int cols =0;
    deep_copy->score = cur_game->score; // Whenever 2 tiles merge, their sum is added to the total score, you copy the same value from cur_game->score
    deep_copy->rows = cur_game->rows; // get rows from cur_game->rows
    deep_copy->cols = cur_game->cols;// get rows from cur_game->cols

    //nested for loop to copy deep copy cells to be like cur_game->cells 
    for (int i = 0; i < cur_game->rows; i++ ){
        for (int j= 0; j < cur_game->cols; j++){
            deep_copy->cells[i*(cur_game->cols)+j] = cur_game->cells[i*(cur_game->cols)+j];
        }
    }
        // call all move functions, if any one them moves, then there is a legal move
       if(move_w(deep_copy) ||  move_a(deep_copy) ||  move_s(deep_copy) || move_d(deep_copy)){
        free(deep_copy->cells); //free memory 
        free(deep_copy); // free memory
        deep_copy = NULL; 
        //hence return 1
        return 1;
        } else{
            free(deep_copy->cells);
            free(deep_copy);
            deep_copy = NULL; // free memory
            // if nothing moved, then return 0.
            return 0;
         }
            // free(deep_copy->cells);
            // free(deep_copy);
            // deep_copy = NULL;
         return 1;
    }



 
    //call every function, check return. 
    //YOUR CODE STARTS HERE


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if(legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
