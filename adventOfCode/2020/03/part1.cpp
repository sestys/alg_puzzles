#include <vector>
#include <iostream>

using namespace std;

int main(){
    vector<string> map;
    string line;
    while(getline(cin, line)){
        map.push_back(line);
    }
    int rows = map.size();
    int cols = map[0].size();
    int tree_n = 0;
    for (int r = 0, c = 0; r < rows; ++r, c = (c + 3) % cols){
        if (map[r][c] == '#') {
            ++tree_n; 
        }
    }
    cout << tree_n << endl;
}
