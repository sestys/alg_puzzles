#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


using namespace std;

static const string myBag = "shiny gold";

string splitString(string& s, string delimeter){
    auto pos = s.find(delimeter);
    string ret = s.substr(0, pos);
    pos = pos == string::npos ? string::npos : pos + delimeter.size();
    s.erase(0, pos);
    return ret;
}

template<class T>
void printMap(unordered_map<T, vector<T>>& m){
    for (const auto& [k, v] : m){
        cout << "Key: " << k << endl;
        for (const auto& val : v){
            cout << val << endl;
        }
        cout << endl;
    }
}

void parseLine(string& line, unordered_map<string, vector<string>>& rules){
    string bag = splitString(line, " bags contain ");
    string rule;
    while (!line.empty()){
        rule = splitString(line, " bag");
        if (rule != "no other"){
            splitString(rule, " ");
            auto it = rules.find(rule);
            if (it == rules.end()){
                rules[rule] = {bag};
            } else {
                it->second.push_back(bag);
            }
        }
        splitString(line, " ");
    }
}
void countBags(const unordered_map<string, vector<string>>& rules, unordered_set<string>& used,const string& bag, int& count){
    auto it = rules.find(bag);
    if (it == rules.end()){
        return;
    }
    for (const auto& other : it->second){
        if (used.find(other) == used.end()){
            ++count;
            used.insert(other);
            countBags(rules, used, other, count);
        }
    }

}

int main(){
    auto line = string();
    auto n = 0;
    unordered_map<string, vector<string>> rules;
    while (getline(cin, line)) {
        parseLine(line, rules);
    }

    unordered_set<string> used;
    countBags(rules, used, myBag, n);
    cout << n << endl;
}
