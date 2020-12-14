#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
    vector<pair<int, uint64_t>> bus;
    uint64_t t = 0, m = 0;
    string line;
    getline(cin, line); // get end of line
    getline(cin, line);
    for (uint64_t i = 0; line.size() > 0; ++i){
        auto pos = line.find(',');
        auto num = line.substr(0, pos);
        pos = pos == string::npos ? pos : pos + 1;
        line.erase(0, pos);
        if (num == "x"){
            continue;
        }
        auto n = stoi(num);
        if (i == 0){
            m = n;
        } else {
            bus.emplace_back(n, n - (i % n));
        }
    }
    t = 0;
    for (const auto& [b, w] : bus){
        while (t % b != w){
            t += m;
        }
        m *= b;
    }
        
    cout << t << endl;
}
