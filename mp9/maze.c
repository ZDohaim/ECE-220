/*
 ziada2, yahme6
 The goal of this MP is to implement a maze solver using a recursive depth-first search, as well as a couple of functions that can be used to verify a correct solution. You will be given text files that contain the unsolved mazes in the following format:
 The first two numbers are the width and height of the maze, followed by the structure of the maze. ‘%’ represents walls within the maze while a space represents an empty cell. ‘S’ indicates the starting position of the maze and ‘E’ indicates the ending position of the maze.

Your program will attempt to solve the maze by finding a path from ‘S’ to ‘E’ by only moving up, down, left, or right (no diagonal moves or moving through walls), print out the maze marked with the solution path and all cells visited during the search. A solved maze will look something like this:


‘*’ represents the cells that make up the solution for the maze and ‘~’ represents the cells that aren't a part of the solution but were visited during the search.

there are four different functions:
maze_t * createMaze(char * fileName);
void destroyMaze(maze_t * maze);
void printMaze(maze_t * maze);
int solveMazeDFS(maze_t * maze, int col, int row)
*/


#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/* 
from maze.h:
*typedef struct {
    int width;
    int height;
    int startColumn;
    int startRow;
    int endColumn;
    int endRow;
    char ** cells;
} maze_t;
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
 /*
 psuedocode:
 open maze file 
 allcoate memory for maze
 read dimension for maze
 allocate memory for maze cells 
 parse through the maze file and fill in maze cells
 close the maze file */
maze_t * createMaze(char * fileName)
{
    //open file using file pointer fp, on read only mode.
    FILE *fp = fopen(fileName, "r"); 
    if (fp == NULL){
        //makes sure pointer is not NULL before contuining with everything else
        return NULL;
    }
    //allocates memory of entire struct using maze_t
    maze_t *maze = malloc(sizeof(maze_t)); 
    int width, height;
    //scans the file, using file pointer, fp, for first two chars, which is found on top of each file.

    fscanf(fp, "%d %d\n", &width, &height); // gets rows and cols from file top of file
    
    //init width and height from maze
    maze->width = width;
    maze->height = height; 

    //allocate memory for each entire size of entire maze or array, hence, height * size of char. 
    maze->cells = (char**)malloc(height* sizeof(char*));
    

    //allocate memory for each cell individually through a for loop
    for (int i=0; i < height; i++){
        maze->cells[i] = (char*)malloc(width * sizeof(char)); //gives the total number of bytes you need to allocate to store width number of characters.
    }
    
    char test_maze;
    
    // itererate through entire file
    for(int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
             // get next character and store in test_maze
             test_maze = fgetc(fp);
           
            //  increments fp to ensure not characters.
            // if(test_maze != 'S' && test_maze != ' ' && test_maze != 'E' && test_maze != '%'){
            //     continue;
            // }

            // if character is S, i.e START
            if(test_maze == 'S'){
                // set start column and start row to the row and column when START was found
                maze->startColumn = j;
                maze->startRow = i;
            }if(test_maze =='E'){
            // set start column and start row to the row and column when END was found

                maze->endColumn = j;
                maze->endRow = i;
                //does this work
            } if(test_maze == '\n'){
                //break 
            } 
            
            //if test_maze passes all, then set to whatever the char is
            maze->cells[i][j] = test_maze;            
        }
        //make sure that this is in the outer loop since, this skips the new line, since the fgetc increments fp pointer
        test_maze = fgetc(fp);

    }
    
    fclose(fp);

   return maze;
}
    

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{

    
    // int width = maze->width;
    // init height from maze
    int height = maze->height; 

    // go in oposite order you malloced in
    //free each array
    for (int i = 0 ; i < height; i++){
            free(maze->cells[i]);
        }
    
    // //free the pointer of cells:
    free(maze->cells);
    
    //free the entire struct
    free(maze);

}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
 for (int i=0; i < maze->height; i++){//looping through prints all cells in ascii format
        for (int j=0; j< maze->width; j++){
            printf("%c", maze->cells[i][j]);
            }
            printf("\n");//print new line
        }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
// (col, row) outside bounds of the maze return false

if((col > (maze->width)) || (col < 0) || (row > (maze->height))|| (row < 0)){
 
    return 0;
   }
if(maze->cells[row][col] == END){
    maze->cells[maze->startRow][maze->startColumn] = START;
    return 1;
}
// if (col, row) is not an empty cell return false (empty is represented with space)

if(maze->cells[row][col] != EMPTY && maze->cells[row][col]!= START){

        return 0;
}



//if (col, row) is the end of the maze return true

//set (col, row) as part of the solution path in the maze
if (maze->cells[row][col]!= START) {
    maze->cells[row][col] = PATH;
}
//if (solveMaze(left of (col, row)) == true) return true
if (maze->cells[row][col-1]!= START && solveMazeDFS(maze, col-1, row) == 1){
    return 1;
}
//if (solveMaze(right of (col, row)) == true) return true
if (maze->cells[row][col+1]!= START && solveMazeDFS(maze, col+1,row) == 1){
    return 1;
}
//if (solveMaze(up of (col, row)) == true) return true
if (maze->cells[row-1][col]!= START && solveMazeDFS(maze,col, row -1) == 1){
    return 1;
}
//if (solveMaze(down of (col, row)) == true) return true
if (maze->cells[row+1][col]!= START && solveMazeDFS(maze,col,row + 1 ) == 1){
    return 1;
}
//unmark (col, row) as part of solution and mark as visited, 
// since it's a useless path because it went over everything above and it's not start or end.
if ((maze->cells[row][col] != START)){
    maze->cells[row][col] = VISITED;
}
    return 0;
}
