#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "../headers/my_modular_arith.h"
#include "../headers/key_generate.h"
#define MIN 16500
#define MAX 32500
//This range is defined so, to generate
//p and q(randomly generated initial primes)
//with same bit-length(i.e. 15 bits). As it is necessary
//that 'p' and 'q' should be of same bit-length.

void key_generate(long int *d,long int *e,long int *n)
{
    long int PRIME_P,PRIME_Q,count,MODULUS,PHI;
    long int prime1_index,prime2_index;
    long int prime_array[1600];

count=generate_primes(prime_array);
//There are total 1575(which is value of 'count' variable at this PRIME_Point)
//primes between this range, And the program will randomly select any
//2-primes from those generated primes.

//randomize();     //This intializes seed for random numbers from clock.
                   //That's why 'time.h' is included. :)

prime1_index=prime2_index=2;
int low=1000;
while(prime1_index==prime2_index)
    {   srand(time(NULL));
	prime2_index = (rand() % (count-low) ) + low;
	prime1_index = rand() % low;
    }

PRIME_P=prime_array[prime1_index];
PRIME_Q=prime_array[prime2_index];

printf("PRIME_P:%10ld ( 0x%lx )\n",PRIME_P,PRIME_P);
printf("PRIME_Q:%10ld ( 0x%lx )\n",PRIME_Q,PRIME_Q);
//Here 2-primes numbers of same bit-length(15 bit) are choosen randomly

MODULUS=PRIME_P*PRIME_Q;   //This is our MODULUS for 'private' and 'public' key generation
PHI=(PRIME_P-1)*(PRIME_Q-1);  //This is 'Euler's Totient Function
printf("\nMODULUS:%10ld ( 0x%lx )\n",MODULUS,MODULUS);
printf("PHI(n) =%10ld ( 0x%lx )\n\nNOTE:phi(n) = phi(p)*phi(q) = (p-1)*(q-1)\n",PHI,PHI);

//Now, let public Key Exponent(e)=65537
//Thus, e is coprime to phi(n).(i.e. gcd(e,phi(n)) = 1)
//So, the public key is declared as: (e,n)
long int PUBLIC_KEY_EXPONENT=65537,PRIVATE_KEY_EXPONENT;
//FILE *fp;
//fp=fopen("public_key.txt","w+");
PRIVATE_KEY_EXPONENT=mul_inv(PUBLIC_KEY_EXPONENT,PHI);
printf("\nThe Public Key(e,n) is: ( %ld ( 0x%lx ), %ld ( 0x%lx ) )\n",PUBLIC_KEY_EXPONENT,PUBLIC_KEY_EXPONENT,MODULUS,MODULUS);
printf("\nThe Private Key(d,n) is: ( %ld ( 0x%lx ), %ld ( 0x%lx ) )\n",PRIVATE_KEY_EXPONENT,PRIVATE_KEY_EXPONENT,MODULUS,MODULUS);

//Putting Public Key for Public access.
//fprintf(fp,"%ld\n%ld",PUBLIC_KEY_EXPONENT,MODULUS);
//fclose(fp);
*e = PUBLIC_KEY_EXPONENT;
*d=PRIVATE_KEY_EXPONENT;  //Giving up private key as a
*n=MODULUS;               //Result of this function.
}


long int generate_primes(long int prime_array[])
{
    long int i,j,count=0;
    for(i=MIN+1;i<MAX;i+=2)
    {
	for(j=2;j<i/2;j++)
	    {
		if(i%j == 0)
		    break;
	    }
	if(j>=i/2)
	    prime_array[count++]=i;
    }
    return count;
}
