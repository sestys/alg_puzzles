#include <string>
#include <iostream>

using namespace std;

string getSubAndErase(string& s, char del){
    auto pos = s.find(del);
    string sub = s.substr(0, pos);
    s.erase(0, pos + 1);
    return sub;
}


int main(){
    int valid = 0;
    int min, max, n;
    char c;
    bool contains;
    string line;
    while (getline(cin, line)){
        min = stoi(getSubAndErase(line, '-')) - 1;
        max = stoi(getSubAndErase(line, ' ')) - 1;
        c = getSubAndErase(line, ':')[0];
        line.erase(0, 1);
        if ((line[min] == c && line[max] != c) || (line[min] != c && line[max] == c)){
            ++valid;
        }  
       
    }
    cout << valid << endl;

}
