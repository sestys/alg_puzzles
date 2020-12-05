#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main(){
    long  max = 0, min = 10000, row, col, id;
    vector<bool> seats(1000, false);
    static unsigned char ind[7] = {64, 32, 16, 8, 4, 2, 1};
    string line;
    while (getline(cin, line)){
        row = 0;
        col = 0;
        for (int i = 0; i < 7; ++i){
            row += line[i] == 'F' ? 0 : ind[i];
        }
        for (int i = 0; i < 3; ++i){
            col += line[7 + i] == 'L'? 0 : ind[4 + i]; 
        }
        id = row * 8 + col;
        seats[id] = true;
        min = min > id ? id : min;
        max = max < id ? id : max; 
    }
    id = min;
    while (seats[id++]);
    cout << --id << endl;
}
