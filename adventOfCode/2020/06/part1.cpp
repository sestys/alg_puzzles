#include <set>
#include <iostream>

using namespace std;

int main(){
    auto line = string();
    auto count = 0;
    auto s = set<char>();
    while (getline(cin, line)){
        if (line == "") {
            count += s.size();
            s.clear();
            continue;
        }
        for (const auto& c : line){
            s.insert(c);
        }
    }
    count += s.size();
    cout << count << endl;
}
