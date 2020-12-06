#include <iostream>
#include <unordered_map>
#include <numeric>

using namespace std;

int main(){
    auto line = string();
    auto count = 0;
    auto p = 0;
    auto s = unordered_map<char, size_t>(); 
    while (getline(cin, line)){
        if (line == "") {
            for (const auto &[key, val] : s){
                if (val == p) {
                    ++count;
                }
            }
            s.clear();
            p = 0;
            continue;
        }
        ++p;
        for (const auto& c : line){
            s[c] += 1;
        }
    }
    for (const auto &[key, val] : s){
        if (val == p) {
                ++count;
            }
    }
    cout << count << endl;
}
