#include <iostream>
#include <string>

const char* BOTTLES[] = {"BCG", "BGC", "CBG", "CGB", "GBC", "GCB"};

int main(int argc, char const *argv[]) {
    int b1, b2, b3, g1, g2, g3, c1, c2, c3;
    int min[6], i, m;
    std::string sequence = "";

    while(std::cin >> b1 >> g1 >> c1 >> b2 >> g2 >> c2 >> b3 >> g3 >> c3){
        m = 0;
        min[0] = b2+b3 + g1+g2 + c1+c3;
        min[1] = b2+b3 + g1+g3 + c1+c2;
        min[2] = c2+c3 + g1+g2 + b1+b3;
        min[3] = c2+c3 + g1+g3 + b1+b2;
        min[4] = g2+g3 + b1+b3 + c1+c2;
        min[5] = g2+g3 + b1+b2 + c1+c3;

        for(i = 1; i < 6; i++){
            if(min[i] < min[m]){
                m = i;
            }
        }
        std::cout << BOTTLES[m] << ' ' << min[m] << std::endl;
    }

    return 0;
}
