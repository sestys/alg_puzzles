#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main(){
    vector<int> entries;
    int n;
    while (cin >> n){
        entries.push_back(n);
    }
    sort(entries.begin(), entries.end());
    int i = 0, j = entries.size() - 1;
    int s;
    while (i < j){
        s = entries[i] + entries[j];
        if (s == 2020){
            cout << entries[i] * entries[j] << endl;
            return 0;
        } else if (s < 2020){
            ++i;
        } else {
            --j;
        }
    }
    return -1;

}
