#include <iostream>
#include <cmath>

int nonWorkingCats = 0;

float logBase(float base, float x){
    return (log(x)/log(base));
}

int countCatsHeight(int h, int n, int depth){
    int tmp = h/(n+1);
    if(tmp >= 1){
        nonWorkingCats += (int)pow((double) n, (double) depth);
        return h + n * countCatsHeight(tmp, n, depth + 1);
    }
    return h;
}

int main(int argc, char const *argv[]) {
    int h, m, n, height;
    std::cin >> h >> m;
    while((h != 0) && (m != 0)){
        // special case
        if(m == 1){
            n = 1;
        } else{
            // find number of cats in a hat
            n = 2;
            while(logBase((float) n, (float) m) != logBase((float) n+1, (float) h)) {
                n++;
            }
        }
        nonWorkingCats = 0;
        height = countCatsHeight(h, n, 0);

        std::cout << nonWorkingCats << ' ' << height << std::endl;
        // get next case
        std::cin >> h >> m;
    }
    return 0;
}
