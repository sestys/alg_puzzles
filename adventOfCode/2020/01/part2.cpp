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
    int s, j ,k;
    for (int i = 0; i < entries.size(); ++i){
        j = i + 1;
        k = entries.size() - 1;
        while (j < k){
            s = entries[i] + entries[j] + entries[k];
            if (s == 2020){
                cout << entries[i] * entries[j] * entries[k] << endl;
                return 0;
            } else if (s < 2020) {
                ++j;
            } else {
                --k;
            }
        }
    }
    return -1;

}
