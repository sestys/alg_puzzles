#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool checkSum(vector<int> nums, int val){
    sort(nums.begin(), nums.end());
    int s = 0, e = nums.size() - 1, sum;
    while (s < e){
        sum = nums[s] + nums[e];
        if (sum == val) {
            return true;
        } else if (sum < val){
            ++s;
        } else {
            --e;
        }
    }
    return false;
}

int main(int argc, char** argv){
    if (argc < 2) {
        cout << "preamble lenght has to be stated!!" << endl;
        return -1;
    }
    auto preamble = stoi(argv[1]);
    vector<int> nums (preamble);
    int tmp;
    for (int i = 0; i < preamble; ++i){
        cin >> tmp;
        nums[i] = tmp;
    }
    int replace = 0;
    while (cin >> tmp){
        if (!checkSum(nums, tmp)){
            break;
        }
        nums[replace] = tmp;
        replace = (replace + 1) % preamble;
    }
    cout << tmp << endl;
}
