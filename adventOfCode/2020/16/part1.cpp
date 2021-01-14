#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<bool> parseFields(){
    vector<bool> taken;
    auto splitNum = [&taken](string nums) {
        size_t idx;
        auto start = stoi(nums, &idx);
        auto end = stoi(nums.substr(idx + 1, string::npos));
        if (end >= taken.size()){
            taken.resize(end + 1, false);
        }
        fill(taken.begin() + start, taken.begin() + end + 1, true);
    };
    size_t pos = 0;
    for (string line; getline(cin, line) && line != "";){
        pos = line.find(": ") + 2;
        line.erase(0, pos);
        pos = line.find(" ");
        splitNum(line.substr(0, pos));
        line.erase(0, pos + 4);
        splitNum(line);
    }
    return taken;
}

vector<vector<int>> parseTickets(){
    vector<vector<int>> tickets;
    auto splitTicket = [&tickets](string &tic){
        vector<int> ticket;
        istringstream tokenStream(tic);
        for (string token; getline(tokenStream, token, ',');){
            ticket.push_back(stoi(token));
        }
        tickets.push_back(ticket);
    };
    string line;
    getline(cin, line);
    while (getline(cin, line)){
        splitTicket(line);
    }
    return tickets;
}

vector<int> parseMyTicket(){
    string line, token;
    vector<int> ticket;
    getline(cin, line);
    getline(cin, line);
    istringstream tokenStream(line);
    while (getline(tokenStream, token, ',')){
        ticket.push_back(stoi(token));
    }
    getline(cin, line);
    return ticket;
}


int main(){
    auto taken = parseFields();
    auto myTicket = parseMyTicket();
    auto allTickets = parseTickets();
    int errorRate = 0;
    for (auto const &t : allTickets){
        for(auto const &v : t){
            if (!taken[v]){
                errorRate += v;
            }
        }
    } 
    cout << errorRate << endl;
}
