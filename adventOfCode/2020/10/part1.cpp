#include <iostream>
#include <vector>
#include <array>

using namespace std;

int main(){
    vector<int> outlets{0};
    array<int, 3> diff{0, 0, 0};
    int tmp;
    while (cin >> tmp){
        outlets.push_back(tmp);
    }
    sort(outlets.begin(), outlets.end());
    for (size_t i = 0; i < outlets.size() - 1; ++i){
        ++diff[outlets[i+1] - outlets[i] - 1];
    }
    ++diff[2];
    cout << diff[0] * diff[2] << endl;
}
