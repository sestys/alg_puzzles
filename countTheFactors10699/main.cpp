#include <stdio.h>
#include <stdlib.h>
 
/* The main program */
int main(int argc, char *argv[])
{
    long n;
    int l = 1000000, i, j, load, counter = 0;
    int primes[1000003];
    int all_primes[78498];
     
    for(i = 0; i<l+3; ++i) {
        primes[i] = 0;
    }
    for (i = 2; i <= l; ++i) {
        if (primes[i] == 0) {
            all_primes[counter] = i;
            counter++;
            for(j = 2; i*j <= l; ++j) {
                primes[j*i] = 1;
            }
        }
        continue;
    }
    while ((load = scanf("%li", &n)) == 1) {
        if (n == 0) {
           return 0;
        }
        if (n == 1) {
            printf("1 : 1\n");
        }
        else {
            printf("%li : ", n);
            counter = 0;
            for (int i = 0; i < n; i++) {
                if (all_primes[i] > n / all_primes[i]) {
                    counter++;
                    break;
                }
                if (n % all_primes[i] == 0){
                    counter++;
                }
                while (n % all_primes[i] == 0) {
                    n = n / all_primes[i];
                }
            }
            printf("%i\n", counter);;
        }
    }
    if (load != EOF) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        return 100;
    }
    return 0;
}
