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
	vector<int> l;
	l.push_back(0);
	l.push_back(0);
	int m = 1;
	int n = fastscan();
	int i, ii;
	int num;
	for (i = 1; i <= n; i++){
		num = fastscan();
		while(m < num){
			m++;
			l.push_back(numeric_limits<int>::max());
			if (m % 3 == 0){
				ii = m / 3;
				l[m] = l[ii] + 1;
			}
			if (m % 2 == 0){
				ii = m / 2;
				l[m] = min(l[ii] + 1, l[m]);
			}
			l[m] = min(l[m], l[m-1] + 1);
		}
		printf("Case %i: %i\n", i, l[num]);
	}
}
