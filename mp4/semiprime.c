/*ziada2 
the errors found in semiprime.c:
in is_prime:
-returning 1 when number == 1 meaning that 1 is a prime number (change it to return 0)
when remainder is 0 it means that there is a numebr that can be divided by another numeber 
which is not 1 due to first test case, therefore should return 0, and if condition is not met then
return 1

in print_semiprimes:
-the nested for loop's condition should not be j <= i 
to ensure that line 49 executes when i and j are not equal, so it's not the same value
i.e i =2 and j =2
-change k = i%j to i/j, since you want to check quotient not the remainder
-set ret = 1, to indicate that it's prime, since ret was never changed before initalizing it to 0
-break out of inner loop to  prevent reprinting semi primes. */

#include <stdlib.h>
#include <stdio.h>


/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        }
    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j < i; j++) { 
         
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j; //check if quotient is prime 
                    if (is_prime(k)) {
                    
                        printf("%d ", i);
                        ret = 1;
                        break;
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
