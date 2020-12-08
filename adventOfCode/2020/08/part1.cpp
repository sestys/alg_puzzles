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
    vector<bool> taken(instructions.size(), false);
    while (!taken[i]){
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
    cout << acc << endl;
}
