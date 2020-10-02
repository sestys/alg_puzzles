#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;

vector<unsigned> SieveOfEratosthenes(unsigned long n) 
{ 
    // Create a boolean array "prime[0..n]" and initialize 
    // all entries it as true. A value in prime[i] will 
    // finally be false if i is Not a prime, else true. 
    bool prime[n+1]; 
    memset(prime, true, sizeof(prime)); 
  
    for (int p=2; p*p <= n; p++) 
    { 
        // If prime[p] is not changed, then it is a prime 
        if (prime[p] == true) 
        { 
            // Update all multiples of p 
            for (int i=p*2; i<=n; i += p) 
                prime[i] = false; 
        } 
    } 
  
    // Print all prime numbers
    vector<unsigned> res;
    for (unsigned p=2; p<n; p++) 
       if (prime[p]) 
          res.push_back(p);
    return res;
}

/* The main program */
int main(int argc, char *argv[])
{
    unsigned nn;
    unsigned max = 0;
    vector<unsigned> cases;
    while (true) {
        scanf("%i", &nn);
        if (nn == 0) {
           break;
        }
        if (nn > max) max = nn;
        cases.push_back(nn);
    }

    auto all_primes = SieveOfEratosthenes(max+1);
    for (unsigned j = 0; j < cases.size(); j++){
    unsigned n = cases[j];    
    int div = 1;
            for (unsigned i = 0; i < n; i++) {
                int counter = 0;
                while (n % all_primes[i] == 0) {
                    n = n / all_primes[i];
                    counter++;
                }
                if (counter > 0){
                    div *= (counter +1);
                }
            }
            if (div % 2) printf("yes\n");
            else printf("no\n");
    }
    return 0;
}
