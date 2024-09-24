/*
 ziada2
 this code implements Pascal’s triangle row printing. 
 It works by getting a value from the user and user the 
 mathematic formula of Π (number*(row+1-1) / i
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int row; // user input
  unsigned long int number = 1; // number is where the value of the pascal triangle is stored, unsigned long int to avoid integer overflow due to large numbers
    
  printf("Enter a row index: "); //ask user to enter row value
  scanf("%d",&row); // place user input into &row.
    
    printf("1 ");                            // print the first number of pascal manually before for loop


    // for loop starting at 1 and ending when i > row+1 since pascal ends at row+1 after input.
    for (int i = 1; i < (row+1); i++){    
        number = (number*(row + 1 - i));    // calculate first number of pascal without division part
       

        number = number/i; // divide first number of pascal
        printf("%lu ", number); //print out number, 
        // loop  back until for condition is broken
    }

  return 0; 

}
