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
    long tree_total = 1, tree_slope;
    int coords[5][2] = {{1,1}, {3, 1}, {5,1}, {7, 1}, {1, 2}};
    for (const auto& coor : coords){
        tree_slope = 0;
        for (int r = 0, c = 0; r < rows; r = r + coor[1], c = (c + coor[0]) % cols){
            if (map[r][c] == '#') {
                ++tree_slope; 
            }
        }
        tree_total *= tree_slope;
    } 
    cout << tree_total << endl;
}
