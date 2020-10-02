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

pi p0;

int fastscan()
{
        int number = 0;
        char c = getchar();
        while(c>=58 || c<=47) c=getchar();
        for (; (c>47 && c<58); c=getchar())
                number = number *10 + c - 48;
        return number;
}

void swap(pi &p1, pi &p2)
{
    pi temp = p1;
    p1 = p2;
    p2 = temp;
}

int distSq(pi p1, pi p2)
{
    return (p1.first - p2.first)*(p1.first - p2.first) +
          (p1.second - p2.second)*(p1.second - p2.second);
}

int orientation(pi p, pi q, pi r)
{
    int val = (q.second - p.second) * (r.first - q.first) -
              (q.first - p.first) * (r.second - q.second);

    if (val == 0) return 0;
    return (val > 0)? 1: 2;
}


int compare(const void *vp1, const void *vp2)
{
   pi *p1 = (pi *)vp1;
   pi *p2 = (pi *)vp2;

   // Find orientation
   int o = orientation(p0, *p1, *p2);
   if (o == 0)
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;

   return (o == 2)? -1: 1;
}


vector<pi> convexHull(vector<pi> points){
    size_t size = points.size();
    int ymin = points[0].second;
    int min = 0;
    for (int i = 1; i < size; i++){
        int y = points[i].second;
        if(y<ymin){
            ymin = y;
            min = i;
        }
    }

}

void solve(vector<pi> points){

}


int main(){
    int points,x,y;
    points = fastscan();
    while (0 < points){
        vector<pi> p;
        for(int i =0;i<points;i++){
            x = fastscan();
            y = fastscan();
            p.emplace_back(x,y);
        }
        points = fastscan();
    }
}

