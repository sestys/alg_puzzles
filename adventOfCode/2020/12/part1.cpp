#include <vector>
#include <iostream>
#include <string>

using namespace std;

constexpr char sides[4] = {'E', 'S', 'W', 'N'};

struct state{
    int north;
    int east;
    int dir;
    state() : dir(0), north(0), east(0) {};
};
void move(state &s, char action, int distance){
    if (action == 'N') {
        s.north += distance;
    } else if (action == 'S'){
        s.north -= distance;
    } else if (action == 'E'){
        s.east += distance;
    } else if (action == 'W'){
        s.east -= distance;
    }
}


void rotate(state &s, char action, int distance){
    distance = action == 'R' ? distance : 360 - distance;
    while (distance > 0){
        distance -= 90;
        s.dir = (s.dir + 90) % 360;
    }

}


int main(){
    char action;
    int a_move;
    auto s = state();
    while (cin >> action >> a_move){
        if (action == 'F'){
            move(s, sides[s.dir / 90], a_move);
        } else if (action == 'R' || action == 'L'){
            rotate(s, action, a_move);
        } else {
            move(s, action, a_move);
        }
    }
    cout << abs(s.east) + abs(s.north) << endl;;

}
