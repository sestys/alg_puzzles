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
    for (int i = 10; i <= 1000000; ++i){
        last->next = make_shared<cup>(i);
        last = last->next;
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
        cout << head->val << " ";
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
        destination = destination == 0 ? 1000000 : destination - 1;
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

shared_ptr<cup> run_iterations(shared_ptr<cup> head, int iterations){
    unordered_map<int, shared_ptr<cup>> val2cup;
    auto curr = head;
    val2cup[head->val] = head;
    for (auto it = head->next; it != head; it = it->next){
        val2cup[it->val] = it;
    }
    cout << "VAL2CUP INIT DONE\n";
    for (int i = 0; i < iterations; ++i){
        auto grabed = grab_cups(curr);
        auto dest_cup = val2cup[get_destination(curr->val, grabed)];
        place_cups(dest_cup, grabed);
        curr = curr->next;
        if ((i + 1) % 1000000 == 0){
            cout << "#" << i + 1 << " DONE\n";
        }
    }
    return val2cup[1];
}

int main(int argc, char** argv){
    int iterations = argc < 2 ? 10000000 : stoi(argv[1]);
    auto head = read_input();
    cout << "CUPS INIT DONE\n";
    head = run_iterations(head, iterations);
    cout << "ITERATIONS DONE\n";
    long solution = static_cast<long>(head->next->val) * static_cast<long>(head->next->next->val);
    cout << head->next->val << " * " << head->next->next->val << " = " << solution << endl;
}

