#include <iostream>
#include <string>
#include <set>

using namespace std;

const string req[7] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
set<string> hcl = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
bool checkData(string field, string val){
    int year;

        if (field == "byr"){
            int age;
            try {
                age = stoi(val);
                return (age >= 1920) && (age <= 2002);
            } 
            catch (invalid_argument i){
                return false;
            }
        }
       else if (field == "iyr") {
            try {
                year = stoi(val);
                return (year >= 2010) && (year <= 2020);
            } 
            catch (invalid_argument i){
                return false;
            }
       }
       else if (field == "eyr") {
            try {
                year = stoi(val);
                return (year >= 2020) && (year <= 2030);
            } 
            catch (invalid_argument i){
                return false;
            }
       }
       else if (field == "hgt") {
            try {
                size_t pos;
                int h = stoi(val, &pos);
                if (val.substr(pos) == "cm"){
                    return (h >= 150) && (h <= 193);
                } else if (val.substr(pos) == "in"){
                    return (h >= 59) && (h <= 76);
                } else {
                    return false;
                }
            } catch (invalid_argument i){
                return false;
            }
       }

       else if (field == "hcl") {
           return val[0] == '#' && val.size() == 7;
       }

       else if (field == "ecl"){
            return hcl.find(val) != hcl.end();
       }
        else if (field == "pid"){
            if (val.size() != 9){
                return false;
            }
            try{
                long num = stol(val);
                return true;
            }
            catch (invalid_argument i){
                return false;
            }
            return false;
        }
        else if (field == "cid"){
            return true;
        }
        return false;
}

bool checkPassport(string& pass){
    set<string> s;
    size_t f, v;
    string fet, val;
    while (!pass.empty()){
        f = pass.find(":");
        s.insert(pass.substr(0, f));
        v = pass.find(" ");
//        fet = pass.substr(0, f);
//        val = pass.substr(f + 1, v - f - 1);
//        cout << f << " " << v << endl;
//        cout << fet << " " << val << endl;
        if (!checkData(pass.substr(0, f), pass.substr(f+1, v - f - 1))){
            return false;
        }
        v = v == string::npos ? v : v + 1;
        pass.erase(0, v);
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
