#include <iostream>
#include <stdio.h>
#include <string>

int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
std::string t = "test";
void clearTable(char* table, int size){
    int i = 0;
    while(i < size){
        table[i] = 'O';
        i++;
    }
}

char* createTable(char* table, int m, int n){
    if(table != nullptr){
        delete[] table;
    }
    table = new char[m*n];
    clearTable(table, m*n);
    return table;
}

void saveTable(char* table, int width, int height, std::string name){
    std::cout << name << std::endl;
    if(table == nullptr){
        std::cout << "table is null" << '\n';
        return;
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            putchar(table[i*width + j]);
        }
        putchar('\n');
    }
}
void colorArea(char* table,int x, int y, int width, int height, char color, char areaColor){
    if(x >= 0 && x < width && y >= 0 && y < height){ // check bounds
        if(table[x + y * width] == areaColor){
            table[x + y * width] = color;
            for(int i = 0; i< 4; i++){ // check neigbours
                colorArea(table, x + directions[i][0], y + directions[i][1], width, height, color, areaColor);
            }
        }
    }

}

int main(int argc, char const *argv[]) {
    char *table;
    table = nullptr;
    char command, color, tmp;
    int width = 0, height = 0, x = 0, y =0, xx = 0, yy = 0;
    std::string buff;

    while(1){
        command = getchar();
        // std::cout << "command: " << command << std::endl;
        switch (command) {
            case 'I': // create new table
                std::cin >> width >> height;
                table = createTable(table, width, height);
                break;
            case 'C': // clear table
                clearTable(table, width*height);
                break;
            case 'L': // color given pixel
                std::cin >> x >> y >> color;
                table[x - 1 + width * (y - 1)] = color;
                break;
            case 'V': // color vertical line
                std::cin >> x >> y >> yy >> color;
                for(int i = std::min(y, yy) -1 ; i < std::max(y, yy); i++){
                    table[x-1 + width * i] = color;
                }
                break;
            case 'H': // color horizontal line
                std::cin >> x >> xx >> y >> color;
                for(int i = std::min(x, xx)-1; i < std::max(x, xx); i++){
                    table[i + width*(y-1)] = color;
                }
                break;
            case 'K': // draw rectangle
                std::cin >> x >> y >> xx >> yy >> color;
                for(int i = std::min(y, yy) -1 ; i < std::max(y, yy); i++){
                    for(int j = std::min(x, xx)-1; j < std::max(x, xx); j++){
                        table[j + i * width] = color;
                    }
                }
                break;
            case 'F': // color region given (x,y)
                std::cin >> x >> y >> color;
                tmp = table[x-1 + width * (y-1)];
                if(color != tmp){
                    colorArea(table, x-1, y-1, width, height, color, tmp);
                }
                break;

            case 'S': // save table to stdout
                std::cin >> buff;
                saveTable(table, width, height, buff);
                break;
            case 'X': // terminate session
                if(table != nullptr){
                    delete[] table;
                }
                return 0;
        }
        while(getchar() != '\n'){} //get new line
    }
    return 0;
}
