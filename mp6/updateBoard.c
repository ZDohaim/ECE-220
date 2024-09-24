/*
ziada2
For each cell of the game board, a live cell is
 represented as 1, a dead cell is represented as 0. 

Each cell has eight surrounding neighbors. 

The game board is updated step by step (each step is a generation).

For each step, a live cell keeps alive if it 
has 2 or 3 live neighbors. It turns into a dead
 cell if it has more than 3, or less than 2, live neighbors.

A dead cell turns into a live cell only if it has 
exactly three live neighbors.

Notice that at step i, the status of a cell at step i+1 is 
determined only based on the status of itself and its surrounding neighbors at step i.

updateBoard.C has three functions 
countLiveNeighbor:
counts the number of live neihbors represented by 1 
using row major order to iterate through 1D array, by checking left right above and below array.




updateBoard:
This function updates the game board 
Where a live cell stays alive if it has 2 or 3 alive neighbors, otherwise the cell dies. 
A dead cell turns alive if it has exactly 3 live neighbors. 
A live cell is represented as 1, a dead cell is represented as 0.
Do so through IF statements to see if number of live nieghbors by calling the countLiveNeighbor function. 



aliveStable
he function returns 1 if the current board stays
 the same for the next step. Otherwise return 0.
 Do so by calling deep copying the array and calling UpdateBoard then seeing if any has changed

 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){

     int count_live_neighbor = 0, curRow = 0, curCol = 0; //init to 0

    for (curRow = (row - 1); curRow <= (row + 1); curRow++){ //starts at row - 1 
        if ( curRow < boardRowSize && curRow >= 0){ // should I check negative as well!?
            for (curCol = (col - 1) ; curCol <= (col + 1); curCol ++){
                if (curCol < boardColSize && curCol >= 0 ){
                    if(curRow != row || curCol != col){ // check if cell isn't at specific point, it could be one or the other hence the OR
                        if (board[curRow*boardColSize+curCol] == 1){ //check if alive
                        count_live_neighbor++; //increment neighbor
                     }
                  }
                }
            }
        }
    }
return count_live_neighbor;   
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
/*The game board is updated to the next step.  
 
A live cell is represented as 1, a dead cell is represented as 0.*/
int deepcopy[boardRowSize*boardColSize]; 

//create deep copy of board
for (int curRow = 0 ; curRow < boardRowSize; curRow++){
    for (int curCol = 0; curCol < boardColSize; curCol++){
        //deepcopy is now the old one, while we change board in the following logic
        deepcopy[curRow*boardColSize+curCol] = board[curRow * boardColSize + curCol]; 
    }
}
for (int curRow = 0; curRow < boardRowSize; curRow++){
    for (int curCol = 0; curCol < boardColSize; curCol++){
        int live = countLiveNeighbor(deepcopy, boardRowSize, boardColSize, curRow, curCol);
            //A live cell stays alive if it has 2 or 3 alive neighbors, otherwise the cell dies.
            if(((live == 3) || (live == 2)) && (deepcopy[curRow*boardColSize+curCol] == 1)){ // check the &&
                board[curRow*boardColSize+curCol] = 1;
            } 
            //A dead cell turns alive if it has exactly 3 live neighbors.
            else if ((live == 3) && (deepcopy[curRow*boardColSize+curCol] == 0)){ //check this
                board[curRow*boardColSize+curCol] = 1;
            } 
            else {
                //cell is dead
                board[curRow*boardColSize+curCol] = 0;
            }
    }
}

}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
    int deepcopy[boardRowSize*boardColSize]; 
    for (int curRow = 0 ; curRow < boardRowSize; curRow++){
        for (int curCol = 0; curCol < boardColSize; curCol++){
        //deepcopy is now the old one, while we change board in the following logic
        deepcopy[curRow*boardColSize+curCol] = board[curRow * boardColSize + curCol]; 
    }
    }
    //call updateBoard function
    updateBoard(deepcopy, boardRowSize, boardColSize);
    
    for (int curRow = 0 ; curRow < boardRowSize; curRow++){
        for (int curCol = 0; curCol < boardColSize; curCol++){
            //check if anything has changed, if the arrays changed, i.e. the original changed from 
            // new array then return 0, else return 1.
            if (board[curRow*boardColSize+curCol] != deepcopy[curRow*boardColSize+curCol]){
                return 0;
    
            }           
        }
        
    }
    return 1;
    }


				
				
			

