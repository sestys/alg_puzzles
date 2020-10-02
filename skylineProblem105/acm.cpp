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
    vvi h;
    int w = 0;
    int s = 10000000;
    int x, y, z;
    while(cin >> x >> y >> z){
        h.pb({x, y, z});
        if (x < s) s = x;
        if (z > w) w = z;
    }
    x = 0;
    int high = 0;
    int end = 10000000;
    vi ret;
    size_t count = h.size();
    for (int i = s; i <= w; i++){
        int cur_h = high;
        if (end == i) cur_h = 0;
        for (int j = 0; j < count; j++){
            auto& cur_house = h[j];
            if (cur_house[0] > i) break;
            if (cur_house[0] <= i && cur_house[2] > i){
                if (cur_house[1] > cur_h){
                    cur_h = cur_house[1];
                    end = cur_house[2];
                }
            }
        }
        if (cur_h != high){
            high = cur_h;
            ret.pb(i);
            ret.pb(high);
        }
    }
    bool f = true;
    for (auto& num : ret){
        if (f){
            cout << num;
            f = false;
        } else {
            cout << " " << num;

        }
    }
    cout << endl;
}

