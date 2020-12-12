#include <vector>
#include <iostream>
#include <string>

using namespace std;

constexpr int sides[4][2] = {{-1, 1}, {-1, 1}, {-1, 1}, {-1, 1}};

struct state{
    int north;
    int east;
    state(int n, int e) : north(n), east(e) {};
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
        swap(s.north, s.east);
        s.north *= -1;
    }

}


int main(){
    char action;
    int a_move, dir;
    auto ship = state(0, 0);
    auto waypoint = state(1, 10);
    while (cin >> action >> a_move){
        if (action == 'F'){
            ship.north += a_move * waypoint.north; 
            ship.east += a_move * waypoint.east;
        } else if (action == 'R' || action == 'L'){
            rotate(waypoint, action, a_move);
        } else {
            move(waypoint, action, a_move);
        }
    }
    cout << abs(ship.east) + abs(ship.north) << endl;;

}
