#include <string>
#include <iostream>

using namespace std;

int main(){
    long  max = 0, row, col;
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
        max = max < row * 8 + col ? row * 8 + col : max; 
    }
    cout << max << endl;
}
