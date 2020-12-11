#include <iostream>
#include <vector>


using namespace std;

int main(){
    vector<vector<string>> map(2, vector<string>());
    int dir[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    string line;
    while(getline(cin, line)){
        map[0].push_back(line);
        map[1].push_back(line);
    }
    size_t o = 0, n = 1, taken = 0;
    auto rows = map[0].size();
    auto cols = map[0][0].size();
    bool changed = true;
    char c;
    int ii, jj;
    cout << rows << " " << cols << endl;
    while (changed){
        changed = false;
        for (int i = 0; i < rows; ++i){
            for (int j = 0; j < cols; ++j){
                c = map[o][i][j];
                if (c == '.'){
                    continue;
                }
                taken = 0;
                for (const auto& [v, h] : dir){
                    ii = i + v;
                    jj = j + h;
                    while (ii >= 0 && ii < rows && jj >= 0 && jj <= cols) {
                        if (map[o][ii][jj] == '#'){
                            ++taken;
                            break;
                        } else if (map[o][ii][jj] == 'L'){
                            break;
                        } else {
                            ii += v;
                            jj += h;
                        }
                    }
                }
                if (taken == 0 && c == 'L'){
                    map[n][i][j] = '#';
                    changed = true;
                } else if (taken >= 5 && c == '#'){
                    map[n][i][j] = 'L';
                    changed = true;
                } else {
                    map[n][i][j] = c;
                }

            }
        }
        o = (o + 1) % 2;
        n = (n + 1) % 2;
    }
    size_t count = 0;
    for (const auto& l : map[o]){
        for (const auto& ll : l){
            if (ll == '#'){
                ++count;
            }
        }
    }
    cout << count << endl;
}
