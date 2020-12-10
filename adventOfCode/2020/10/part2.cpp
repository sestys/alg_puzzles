#include <iostream>
#include <vector>
#include <array>

using namespace std;

int main(){
    vector<int> outlets{0};
    int tmp;
    while (cin >> tmp){
        outlets.push_back(tmp);
    }
    sort(outlets.begin(), outlets.end());
    vector<uint64_t> dp(outlets.back() + 1, 0);
    dp[0] = 1;
    uint64_t v1, v2, v3;
    for (size_t i = 1; i < outlets.size(); ++i){
        auto id = outlets[i];
        v1 = id - 1 < 0 ? 0 : dp[id-1];
        v2 = id - 2 < 0 ? 0 : dp[id-2];
        v3 = id - 3 < 0 ? 0 : dp[id-3];
        dp[id] = v1 + v2 + v3;
    }
    cout << dp.back() << endl;
}
