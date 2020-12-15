#include <unordered_map>
#include <iostream>

using namespace std;

int main() {
    unordered_map<int, int> mem;
    char p;
    int spoken = 0, before = -1;
    for (int i = 1, num; cin >> num; ++i){
        mem[num] = i;
        spoken = num;
        cin >> p;
    }
    auto turn = mem.size();
    while (turn < 2020){
        ++turn;
//        cout << "t: " << turn ;
        spoken = before == -1 ? 0 : turn - 1 - before;
        before = mem.find(spoken) != mem.end() ? mem[spoken] : -1;
        mem[spoken] = turn;
//        cout << " s " << spoken << " b " << before << endl;;
    }
    cout << spoken << endl;

}
