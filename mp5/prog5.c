/*ziada2

The codebreaking game is very similar to the board game Mastermind and NY Times game Wordle, but played with numbers from 1-8.
To play the game, the user first enters a "seed" value, which is an integer. This seed value initializes a pseudo-random number generator. 
Using the pseudo-random number generator, a solution code sequence of four numbers from 1 to 8 is chosen at "random." T
his solution is kept hidden from the player.

There are three different functions in prog5.c:

set_seed: simply sets the seed using srand, and checks the validity of the input using sscanf

set_game: sets solutions to a psuedo randomly generated number using rand % 8 + 1 to insure that the solution is between 1-8

make_guess: gets guesses from user, checks if 4 integers that are between 1 - 8, there are two cases, perfect and mistmatch. 

have to consider edge cases, such as if the guessed value is guessed more than once


*/


#include <stdio.h>
#include <stdlib.h>
#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid.
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[])
{
    //    Example of how to use sscanf to read a single integer and check for anything other than the integer
    //    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
    //    The user should enter only an integer, and nothing else, so we will check that only "seed" is read.
    //    We declare
    //    int seed;
    //    char post[2];
    //    The sscanf statement below reads the integer into seed.
    //    sscanf (seed_str, "%d%1s", &seed, post)
    //    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
    //    The return value of sscanf indicates the number of items read succesfully.
    //    When the user has typed in only an integer, only 1 item should be read sucessfully.
    //    Check that the return value is 1 to ensure the user enters only an integer.
    //    Feel free to uncomment these statements, modify them, or delete these comments as necessary.
    //    You may need to change the return statement below

    
    int check; //flag
    int seed;
    char post[2];
    check = sscanf (seed_str, "%d%1s", &seed, post);
    if (check==1) //checks if int
    {
        //generate random seed given the integers from user
        srand(seed);
        return 1;
    }
    else
    {
        printf("set_seed: invalid seed\n");
        return 0;
    }
    return 0;
}

/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above.
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    //your code here
   
    solution1 = (rand() % 8) + 1; //because the remainder can only be in the range of 0 to 7 when divided by 8.
    solution2 = (rand() % 8) + 1;
    solution3 = (rand() % 8) + 1;
    solution4 = (rand() % 8) + 1;
    
    guess_number = 0;

    *one = solution1;
    *two = solution2;
    *three = solution3;
    *four = solution4; // set *one,two,three,four to the solution. you derefernce to accesss value
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str.
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess)
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two,
        int* three, int* four)
{
    //initialize
    int w,x,y,z;
    int mismatch = 0;
    int perfect_match = 0;
    int flag;
    static int sol_str[4];
    char post[2]; 
    //get guess string form user
    flag = sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);
   
    
    
    //check if all between 1 and 8 and flag is 4, flag here checks if value is exactly 4 integers
    if ((w > 0 && w < 9) && (x > 0 && x < 9) && (y > 0 &&   y < 9) && (z > 0 && z < 9) && flag == 4){ 
        *one = w;
        *two = x;
        *three = y;
        *four = z;

        guess_number++;
       
        int temp_guess_array[4] = {0,0,0,0};
        int temp_sol_array[4] = {0,0,0,0};
        // set solutions 1,2,3,4 into sol_str
        sol_str[0]= solution1;
        sol_str[1]= solution2;
        sol_str[2]= solution3;
        sol_str[3]= solution4;

        int guess_arr[4];
        //set guess_arr to individual string values, i.e turn string into array 
        guess_arr[0] = w; 
        guess_arr[1] = x; 
        guess_arr[2] = y; 
        guess_arr[3] = z; 



        
        //perfect case, checks if sol is the same as guesss then increment perfect_match
        for (int i = 0 ; i < 4; i++){
            if(guess_arr[i] == sol_str[i]){
                perfect_match++;
                temp_guess_array[i]=1;
                temp_sol_array[i]=1;
            }
        }
        
        
        //mismatch, using temp array to flag if guess is made and matched, i.e. flags solution and guess to insure it doesn't go same value twice.
        // then increment mismatch
        for (int j= 0; j < 4; j++){
            for (int i = 0; i < 4; i++){
            if (temp_guess_array[i] == 0 && guess_arr[i] == sol_str[j] && temp_sol_array[j] == 0){
                temp_guess_array[i]= 1;
                temp_sol_array[0] = 1;
                mismatch++; 
            }
        }
    }
        printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect_match, mismatch);
        return 1;
        
        
        
    } else {
        printf("make_guess: invalid guess\n");
        return 0;
    }
}

    
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed