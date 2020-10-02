#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>

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

pi slope(pi a, pi b){
    return mp(a.first-b.first, a.second - b.second);
}

int solve(vector<pi> points){
    int ret = 0;
    
    size_t sizePoint = points.size();
    for(unsigned i = 0; i < sizePoint; i++){
        for (unsigned j = i+1; j < sizePoint; j++){
          continue;  
        }
    }
    return 0;
}


int main(){
    int cases;
    string line;
    cin >> cases;
    getline(cin, line);
    getline(cin, line);

    for (int i = 0; i < cases; i++) {
        vector<pi> points;
        while (getline(cin, line) && line.length() > 0){
            vector<string> spl;
            boost::split(spl, line, boost::is_any_of(" "));
            points.emplace_back(stoi(spl[0]), stoi(spl[1]));
        }
    }
}

