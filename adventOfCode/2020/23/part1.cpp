#include <iostream>
#include <memory>
#include <set>
#include <unordered_map>

using namespace std;

struct cup {
   int val;
   shared_ptr<cup> next;
   cup(int value) : val(value) {};
};

shared_ptr<cup> read_input(){
    string line;
    getline(cin, line);
    shared_ptr<cup> head = NULL, last = NULL;
    for (const auto& c : line){
        if (head == NULL){
            head = make_shared<cup>(c - '0');
            last = head;
        } else {
            last->next = make_shared<cup>(c - '0');
            last = last->next;
        }
    }
    last->next = head;
    return head;
}

void print_cups(shared_ptr<cup> head){
    while(head->val != 1){
        head = head->next;
    }
    while(head->next->val != 1){
        head = head->next;
        cout << head->val;
    }
    cout << endl;
}

shared_ptr<cup> grab_cups(shared_ptr<cup> head){
    auto first = head->next;
    auto last = first;
    for (int i = 0; i < 2; ++i){
        last = last->next;
    }
    head->next = last->next;
    last->next = NULL;
    return first;
}

int get_destination(int curr_val, shared_ptr<cup> grabed){
    set<int> vals = {grabed->val, grabed->next->val, grabed->next->next->val};
    int destination = curr_val - 1;
    while (destination == 0 || vals.find(destination) != vals.end()){
        destination = destination == 0 ? 9 : destination - 1;
    }
    return destination;
}

void place_cups(shared_ptr<cup> dest, shared_ptr<cup> grabed){
    auto last = dest->next;
    dest->next = grabed;
    while (grabed->next != NULL){
        grabed = grabed->next;
    }
    grabed->next = last;
}

void run_iterations(shared_ptr<cup> head, int iterations){
    unordered_map<int, shared_ptr<cup>> val2cup;
    auto curr = head;
    val2cup[head->val] = head;
    for (auto it = head->next; it != head; it = it->next){
        val2cup[it->val] = it;
    }
    for (int i = 0; i < iterations; ++i){
        auto grabed = grab_cups(curr);
        auto dest_cup = val2cup[get_destination(curr->val, grabed)];
        place_cups(dest_cup, grabed);
        curr = curr->next;
    }
}

int main(int argc, char** argv){
    int iterations = argc < 2 ? 100 : stoi(argv[1]);
    auto head = read_input();
    run_iterations(head, iterations);
    print_cups(head);
}

