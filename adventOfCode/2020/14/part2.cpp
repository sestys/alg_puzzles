#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

pair<uint64_t, uint64_t> parseLine(string &line, string& mask){
    if (line[1] == 'a'){
        line.erase(0, 7);
        mask = line;
        return {-1, -1};
    }
    auto pos = line.find("= ");
    uint64_t idx = stol(line.substr(4, string::npos));
    line.erase(0, pos + 2);
    uint64_t val = stol(line);
    return {idx, val};
}

void applyMask(uint64_t& val, string& mask){
    auto n = mask.size() - 1;
    for (const auto& c : mask){
        if (c == '1'){
            val |= 1UL << n;
        } 
        --n;
    }
}
void insertFloating(uint64_t& val, uint64_t& addr, string& mask, unordered_map<uint64_t, uint64_t>& mem, size_t id){
    while (id <= mask.size()){
        if (id == mask.size()) {
            mem[addr] = val;
            break;
        }
        if (mask[mask.size() - 1 - id] == 'X'){
            addr |= 1UL << id;
            insertFloating(val, addr, mask, mem, id + 1);
            addr &= ~(1UL << id);
            insertFloating(val, addr, mask, mem, id + 1);
            break;
        }
        ++id;
    }
}


int main(){
    unordered_map<uint64_t, uint64_t> mem{};
    string mask{};
    pair<uint64_t, uint64_t> in{}; 
    for (string line; getline(cin, line);){
        in = parseLine(line, mask);
        if (in.first == -1) {
            continue;
        }
        applyMask(in.first, mask);
        insertFloating(in.second, in.first, mask, mem, 0);
        
    }
    uint64_t count = 0;
    for (const auto& [k, v] : mem){
        count += v;
    }
    cout << count << endl;
}
