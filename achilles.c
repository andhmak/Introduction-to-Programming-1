/*File: achilles.c*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COMPUTATIONS 10000000

int main(void) {
	unsigned int power, gcd, n, i, temp1, temp2, count, curtime, x, y, z;    /*(only positive integers will be used) "power" power of current prime factor, "gcd" greatest common divisor, "n, i" for loops, "temp1" temporary1 (the current number but divided by each factor)*/
	                                                                         /*"temp2" temporary2 (to use in Euclid's algorithm), "count" count of achilles numbers found, "curtime" current time, "x, y, z" to calculate pseudorandom number*/
	count = 0;                                                               /*Initialising "count"*/
	curtime = time(NULL);                                                    /*Getting current time*/
	printf("Current time is %d\n", curtime);                                 /*Printing current time*/
	srand((unsigned int) curtime);                                           /*Using current time in order for the "rand" function to later work*/
	printf("\n");                                                            /*Leaving an empty line*/
	for (n = 1 ; n <= COMPUTATIONS ; n++) {
		y = rand() % 32768 + 1;                              /*Calculating random number*/
		z = rand() % 32768 + 1;
		x = y*z + 1;
		gcd = 0;                                             /*Initialising "gcd"*/
		power = 0;                                           /*Initialising "power"*/
		temp1 = x;                                           /*Storing the random number in the "temp1" variable, which will be used for calculations and will be altered*/

		/*Process for 2*/
		while (temp1 % 2 == 0) {                             /*Step 1: Check how many times 2 is a factor*/
			temp1 /= 2;
			power++;
		}
		if (power == 1) {                                    /*Step 2: If power == 1, then the number isn't powerful, and therefore not achilles, so we ignore it and start checking the next one*/
			continue;
		}
		if (power != 0) {                                    /*Step 3: If power == 0, there is no point in storing its value. If power != 0, since there is no previous power to calculate the gcd, we store the "pawer" value in "gcd".*/
			gcd = power;
		}
		power = 0;

		/*Process for i, where i = 3, 5, 7, 9, 11..., up to sqrt(temp1)*/
		for (i = 3 ; i*i <= temp1 ; i += 2) {
			while (temp1 % i == 0) {                /*Step 1*/
				temp1 /= i;
				power++;
			}
			if (power == 1) {                       /*Step 2*/
				break;
			}
			if (power != 0) {                       /*Step 3: Calculating the current gcd.*/
				if (gcd == 0) {                     /*3.1: If gcd = 0, then this is first factor found, so we store the "power" value for later use.*/
					gcd = power;
					power = 0;
				}
				else {                              /*3.2: If gcd != 0, then we calculate the gcd between "power" (the current power) and "gcd" (the gcd of all previous powers).*/
					if (gcd < power) {              /*3.2.1: We use Euclid's algorithm to find the gcd of "gcd" and "power". We consider "gcd" to be the larger one initially, if it isn't, we change the values between "gcd" and "power".*/
						temp2 = gcd;
						gcd = power;
						power = temp2;
					}
					while (power != 0) {            /*3.2.1: Euclid's algorithm*/
						temp2 = power;
						power = gcd % power;
						gcd = temp2;
					}
				}
			}
		}
		if (power == 1) {                           /*For Step 2 to work inside the for loop (we want it to check the next number, so we use "break" to get out of the "for" loop and "continue" to move to the next number in the initial "while" loop)*/
			continue;
		}
		if (temp1 > 2) {                            /*To check if the number remaining is prime, in which case its power == 1 (it divides itself, and therefore the original undivided number, only once), so the original number isn't powerful, so we skip it and move on to the next number.*/
			continue;
		}
		if (gcd == 1) {                             /*If gcd == 1 in the end, then the number was an achilles number*/
			printf("%9d is Achilles number\n", x);
			count++;                                /*Each time we find an achilles number we add 1 to the count*/
		}
	}
	printf("\n");
	printf("Found %d achilles out of %d tested numbers\n", count, n - 1);    /*We print the total amount of achilles numbers found*/
	return 0;
}
