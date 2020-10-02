#include <iostream>
#include <vector>


int values[] = {4, 9, 15, 3, 21, 4, 6, 7, 11, 13, 2};
int size = 11;

void printArray(int* v, int size){
    for(int i = 0; i < size; i++){
        std::cout << v[i] << ' ';
    }
    std::cout << std::endl;
}
void insertSort(int* v, int size){
    int tmp, id;
    for(int i = 1; i < size; i++){
        id = i;
        while(v[id] < v[id-1] && id >= 0){
            tmp = v[id];
            v[id] = v[id-1];
            v[id-1] = tmp;
            id--;
        }
    }
}

int main(int argc, char const *argv[]) {
    std::cout << "Unsorted array: ";
    printArray(values, size);
    //sort values
    insertSort(values, size);
    std::cout << "Sorted array: ";
    printArray(values, size);
    return 0;
}
