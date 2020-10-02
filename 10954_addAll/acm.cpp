#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

#define REP(i, n)   for(int i=0; i<n; i++)
#define FOR(i,s,e)  for(int i=s; i<e; i++)
#define mp          make_pair
#define pb          push_back
#define db(x)       cout << (#x) << " = " << x << endl;

int fastscan()
{
        int number = 0;
        char c = getchar();
        while(c>=58 || c<=47) c=getchar();
        for (; (c>47 && c<58); c=getchar())
                number = number *10 + c - 48;
        return number;
}



int main(){
    int n, a, b, s;
    n = fastscan();
    while (n != 0){
        priority_queue<int, vi, greater<int>> numbers;
        for (int i = 0; i < n; i++){
            numbers.push(fastscan());
        }
        int sum = 0;
        while (numbers.size() > 1){
            a = numbers.top(); numbers.pop();
            b = numbers.top(); numbers.pop();
            s = a + b;
            sum += s;
            numbers.push(s);
        }
        cout << sum << endl;
        n = fastscan();
    }

}

