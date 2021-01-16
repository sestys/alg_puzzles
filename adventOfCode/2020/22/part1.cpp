#include <list>
#include <iostream>

using namespace std;

list<int> read_input(){
    list<int> cards;
    for (string line; getline(cin, line);){
        if (line == "") {
            break;
        } else if (line[0] == 'P'){
            continue;
        } else {
            cards.push_back(stoi(line));
        }
    }
    return cards;
}

void play_round(list<int> &a, list<int> &b){
    auto card_a = a.front();
    a.pop_front();
    auto card_b = b.front();
    b.pop_front();
    if (card_a > card_b){
        a.push_back(card_a);
        a.push_back(card_b);
    } else {
        b.push_back(card_b);
        b.push_back(card_a);
    }
}

int play_game(list<int> &a, list<int> &b){
    while (!a.empty() && !b.empty()){
        play_round(a, b);
    }
    auto winner = a.empty() ? b : a;
    unsigned long score = 0;
    int multiple = 1;
    for (auto it = winner.crbegin(); it != winner.crend(); ++it, ++multiple){
        score += multiple * (*it);
    }
    return score;
}

int main(){
    auto a = read_input(), b = read_input();
    auto score = play_game(a, b);
    cout << score << endl;
}
