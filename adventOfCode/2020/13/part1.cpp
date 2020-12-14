#include <iostream>
#include <string>

using namespace std;

int main(){
    int time, curr = 0, id = 0, wait = 0, b_id = 0, b_wait = 100000;
    string line;
    cin >> time;
    getline(cin, line); // get end of line
    getline(cin, line);
    while (line.size() > 0){
        auto pos = line.find(',');
        auto num = line.substr(0, pos);
        pos = pos == string::npos ? pos : pos + 1;
        line.erase(0, pos);
        if (num == "x"){
            continue;
        }
        id = stoi(num);
        curr = id - (time % id);
        if (b_wait > curr){
            b_wait = curr;
            b_id = id;
        }
    }
    cout << b_id * b_wait << endl;
}
