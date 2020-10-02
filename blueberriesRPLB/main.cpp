#include <bits/stdc++.h>

using namespace std;

int knapsack(vector<int> bush, int m){
    vector<vector<int>> k(bush.size() + 2, vector<int>(m+1, 0));
    for(unsigned i = 2; i < bush.size() + 1; i++){
        for (unsigned j = 1; j < m + 1; j++){
            if (j == 0 || i == 0){
                k[i][j] = 0;
            } else if (bush[i] <= j){
                k[i][j] = max(bush[i] + k[i-2][j-bush[i]], k[i-1][j]);

            } else {
                k[i][j] = k[i-1][j];
            }
        }
    }
    return k[bush.size()+1][m];
}
int fastscan()
{
         char c;
         int number = 0;
         c = getchar();
         while(c>=58 || c<=47) c=getchar();
         // Keep on extracting characters if they are integers
         // i.e ASCII Value lies from '0'(48) to '9' (57)
         for (; (c>47 && c<58); c=getchar())
                 number = number *10 + c - 48;
         return number;
 }
int main(){
    int t = fastscan();
    int n, k;
    for (int i = 1; i <= t; i++){
        n = fastscan();
        k = fastscan();
        cout << n << " " << k << endl;
        vector<int> bush(n);
        for (int j = 0; j < n; j++) bush[j] = fastscan();
        for (auto q : bush) cout << q << endl;
        printf("Scenario #%i: %i\n", i, knapsack(bush, k));
    }
}
