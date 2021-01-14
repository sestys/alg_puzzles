#include <iostream>
#include <set>
#include <vector>
#include <

using namespace std;
using pair<int, int> pos;

const vector<pos> neigbours = {{-2, 0}, {-1, 1}, {1, 1}, {2, 0}, {1, -1}, {-1, -1}};

pos getTile(string dir){
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

int shuffleTiles(set<pos> &start, int days){
    map<pos, int> neighbourCount;
    
    for (int i = 0; i < days; ++i){
        neighbourCount.clear();
        for (const auto &tile : start){
            for (const auto &p : neighbours){
                auto it = neighbourCount.find(p);
                if (it == neighbourCount.end()){
                    neighboutCount[p] = 1;
                } else {
                    it->second += 1;
                }
            }
        }
        for (auto &[p, count] : neighbourCount)
    }
    return tiles[old].size();
}

int main(){
    set<pos> blackPosition;
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
