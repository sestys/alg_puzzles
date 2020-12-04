#include <iostream>
#include <string>
#include <set>

using namespace std;

const string req[7] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

bool checkPassport(string& pass){
    set<string> s;
    size_t pos;
    while (!pass.empty()){
        pos = pass.find(":");
        s.insert(pass.substr(0, pos));
        pos = pass.find(" ");
        pos = pos == string::npos ? string::npos : pos + 1;
        pass.erase(0, pos);
    }
    for (const auto& r : req){
        if (s.find(r) == s.end()){
            return false;
        }
    }
    return true;
}

int main(){
    string line, data;
    size_t n = 0;
    while (getline(cin, line)){
        if (line != ""){
            data = data + line + " ";
        } else {
            n += checkPassport(data);
            data = "";
        }
    }
    n += checkPassport(data);
    cout << n << endl;    
}
