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
    vector<int> all;
    vector<int> nums (preamble);
    int tmp;
    for (int i = 0; i < preamble; ++i){
        cin >> tmp;
        nums[i] = tmp;
        all.push_back(tmp);
    }
    int replace = 0;
    while (cin >> tmp){
        if (!checkSum(nums, tmp)){
            break;
        }
        all.push_back(tmp);
        nums[replace] = tmp;
        replace = (replace + 1) % preamble;
    }
    int i = 0, j = 1, sum;
    sum = all[i] + all[j];
    while (sum != tmp){
        if (sum < tmp) {
            ++j;
            sum += all[j];
        } else if (sum > tmp) {
            sum -= all[i];
            ++i;
            if (i == j){
                ++j;
                sum += all[j];
            }
        }
    }
    auto mm = minmax_element(all.begin() + i, all.begin() + j);
    cout << *mm.first + *mm.second << endl;
}
