#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

pair<int, uint64_t> parseLine(string &line, unordered_map<int, bool>& mask){
    if (line[1] == 'a'){
        line.erase(0, 7);
        mask.clear();
        for (int i = 0, n = line.size() - 1; i <= n; ++i){
            if (line[n - i] != 'X'){
                mask[i] = line[n - i] == '1' ? 1 : 0;
            }
        }
        return {-1, -1};
    }
    auto pos = line.find("= ");
    auto idx = stoi(line.substr(4, string::npos));
    line.erase(0, pos + 2);
    uint64_t val = stol(line);
    return {idx, val};
}

void applyMask(uint64_t& val, unordered_map<int, bool>& mask){
    for (const auto& [id, bit] : mask){
        if (bit){
            val |= 1UL << id;
        } else {
            val &= ~(1UL << id);
        }
    }
}

int main(){
    unordered_map<int, uint64_t> mem;
    unordered_map<int, bool> mask;
    pair<int, uint64_t> in; 
    for (string line; getline(cin, line);){
        in = parseLine(line, mask);
        if (in.first == -1) {
            continue;
        }
        applyMask(in.second, mask);
        mem[in.first] = in.second;
    }
    uint64_t count = 0;
    for (const auto& [k, v] : mem){
        count += v;
    }
    cout << count << endl;
}
