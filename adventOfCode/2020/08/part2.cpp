#include <iostream>
#include <string>
#include <vector>

using namespace std;

pair<string, int> parseInput(string& line){
    auto pos = line.find(" ");
    auto op = line.substr(0, pos);
    auto offset = stoi(line.substr(pos + 1, string::npos));
    return make_pair(op, offset);
}

int main(){
    string line;
    vector<pair<string, int>> instructions;
    int acc = 0, i = 0;
    while (getline(cin, line)){
        instructions.push_back(parseInput(line));
    }
    for (int j = 0; j < instructions.size(); ++j){
        if (instructions[j].first == "acc"){
            continue;
        }
        instructions[j].first = instructions[j].first == "nop" ? "jmp" : "nop";
        acc = 0;
        i = 0;
        vector<bool> taken(instructions.size(), false);
        while (i < instructions.size() && !taken[i]){
            taken[i] = true;
            if (instructions[i].first == "nop"){
                ++i;
            } else if (instructions[i].first == "acc"){
                acc += instructions[i].second;
                ++i;
            } else if (instructions[i].first == "jmp") {
                i += instructions[i].second;
            } else {
                throw out_of_range("wrong instruction " + instructions[i].first);
            }
        }
        if (i == instructions.size()){
            break;
        } else {
            instructions[j].first = instructions[j].first == "nop" ? "jmp" : "nop";
        }

    }
    cout << acc << endl;
}
