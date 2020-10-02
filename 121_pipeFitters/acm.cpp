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

int skew(double a, double b) {
    if(b < 1)   return 0;
    int h, sum;
    h = 1 + (int)((b-1)/sqrt(3)*2);
    sum = (h - h/2)*(int)a + h/2*(int)(a-0.5);
    return sum;
}

int main(){
    double a, b;
    int grid, sk;
    while (scanf("%lf %lf", &a, &b) == 2){
        grid = (int)a * (int)b;
        sk = max(skew(a, b), skew(b,a));
        if (sk > grid) cout << sk << " skew\n";
        else cout << grid << " grid\n";
    }
}

