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
void printMap(unordered_map<T, vector<pair<T, int>>>& m){
    for (const auto& [k, v] : m){
        cout << "Key: " << k << endl;
        for (const auto& [val, c] : v){
            cout << val << " " << c << endl;
        }
        cout << endl;
    }
}

void parseLine(string& line, unordered_map<string, vector<pair<string,int>>>& rules){
    string bag = splitString(line, " bags contain ");
    vector<pair<string, int>> con;
    string rule, c;
    while (!line.empty()){
        rule = splitString(line, " bag");
        if (rule != "no other"){
            c = splitString(rule, " ");
            con.emplace_back(rule, stoi(c));
        }
        splitString(line, " ");
    }
    if (!con.empty()){
        rules[bag] = con;
    }
}
int countBags(const unordered_map<string, vector<pair<string, int>>>& rules, unordered_map<string, int>& cache,const string& bag){
    auto it = rules.find(bag);
    if (it == rules.end()){
        return 1;
    }
    if (cache.find(bag) != cache.end()){
        return cache[bag];
    }
    int r = 1, curr = 0;
    for (const auto& [b, n] : it->second){
        curr = countBags(rules, cache, b);
        cache[b] = curr;
        r += n * curr;
    }
    return r;

}

int main(){
    auto line = string();
    auto n = 0;
    unordered_map<string, vector<pair<string, int>>> rules;
    while (getline(cin, line)) {
        parseLine(line, rules);
    }
//    printMap(rules);
    unordered_map<string, int> used;
    n = countBags(rules, used, myBag) - 1;
    cout << n << endl;
}
