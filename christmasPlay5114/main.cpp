#include <bits/stdc++.h>


using namespace std;

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
	int i, n, k, j, m,mindif;
	
	for (i = 0; i < t; i++){
		n = fastscan();
		k = fastscan();
		mindif = numeric_limits<int>::max();
		vector<int> h(n);
		for (j = 0; j < n; j++){
			h[j] = fastscan();
		}
		sort(h.begin(), h.end());
		for (j = 0; j <= n-k; j++){
			m = (h[j+k-1]-h[j]);
			mindif = min(mindif, m);
		}
		printf("%i\n", mindif);
	}
}
