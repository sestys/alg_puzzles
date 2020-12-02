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
    string line;
    while (getline(cin, line)){
        min = stoi(getSubAndErase(line, '-'));
        max = stoi(getSubAndErase(line, ' '));
        c = getSubAndErase(line, ':')[0];
        line.erase(0, 1);
        n = 0;
        for (const auto& l : line){
            if (c == l) {
                ++n;
            }
        }
        if (n >= min && n <= max) {
            ++valid;
        }
       
    }
    cout << valid << endl;

}
