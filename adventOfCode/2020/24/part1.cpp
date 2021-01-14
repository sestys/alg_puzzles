#include <iostream>
#include <set>

using namespace std;


pair<int, int> getTile(string dir){
    int x = 0, y = 0;
    for (int i = 0; i < dir.size(); ++i){
        if (dir[i] == 'e'){
            x += 2;
        } else if (dir[i] == 'w'){
            x -= 2;
        } else if (dir[i] == 's'){
            ++i;
            y -= 1;
            x = dir[i] == 'e' ? x + 1 : x - 1;
        } else if (dir[i] == 'n'){
            ++i;
            y += 1;
            x = dir[i] == 'e' ? x + 1 : x - 1;
        } else {
            cout << "wrong direction\n" << dir << endl << i << endl;
        }
    }

    return {x, y};
}

int main(){
    set<pair<int, int>> blackPosition;
    for (string line; getline(cin, line);){
        auto tile = getTile(line);
        if (blackPosition.find(tile) == blackPosition.end()){
            blackPosition.insert(tile);
        } else {
            blackPosition.erase(tile);
        }
    }
    cout << blackPosition.size() << endl;
}
