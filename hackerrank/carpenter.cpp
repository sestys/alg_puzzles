#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#include <chrono>

using namespace std;
class Workshop {
 public:
  explicit Workshop(vector<long> cabinets) : capacities_(move(cabinets)) {}
  ~Workshop() = default;
  /**
   * Returns the cabinet the key is in. Key has to be in one of the cabinets or outside.
   * O(sum cabinets capacities)
   * @param key
   * @return int, cabinet id
   */
  int getItemsCabinet(long key) {
      int dis = _item_position(map_[key]);
      if (dis >= capacities_.back()){
          return capacities_.size();
      }
      for (int i = 1; i < capacities_.size(); ++i) {
          if (capacities_[i] > dis) {
              return i;
          }
      }
      return -1;
  }

  //
  /**
   * Represents work done a on item with id key.
   * O(1) if return_previousCabint == false else O(sum cabinets capacities)
   * @param key
   * @param returnPreviousCabinet
   * @return
   */
  int workOnItem(long key, bool returnPreviousCabinet = false){
      int return_value = 0;
      if (map_.find(key) != map_.end()) {
          if (returnPreviousCabinet) {
              return_value = getItemsCabinet(key);
          }
          items_.erase(map_[key]);
      }
      items_.push_front(key);
      map_[key] = items_.begin();
      return return_value;

  }
 private:
  /**
   * Used to get cabinet in which item is stored.
   * Returns item's distance from the first item in first cabinet.
   * If item is stored outside, it return the distance to first item outside from the start.
   * @param item
   * @return int
   */
  int _item_position(list<long>::iterator item) {
      int n = 0;
      auto start = items_.begin();
      long max_cabinet_capacity = capacities_.back();
      while ((start != item) && (n <= max_cabinet_capacity)) {
          ++start;
          ++n;
      }
      return n;
  }

  vector<long> capacities_;
  list<long> items_;
  unordered_map<long, list<long>::iterator> map_;
};

int main() {
    vector<long> cabinets;
    char delimeter = ' ';
    long tmp, n_test;
    int idx = 0;
    int return_value = -1;
    bool return_cabinet_id;
    unsigned long k_upper_limit = 1UL << 32;
    size_t position;
    string cabinets_temp;

    getline(cin, cabinets_temp);
    cabinets.push_back(0);
    while (!cabinets_temp.empty()){
        position = cabinets_temp.find(delimeter);
        tmp = stol(cabinets_temp.substr(0, position));
        if (tmp < 1 || tmp >= 1024 || idx >= 64) {
            cout << "INPUT_ERROR" << endl;
            return 0;
        }
        cabinets.push_back(tmp + cabinets[idx]);
        ++idx;
        position = position == string::npos ? position : position + 1;
        cabinets_temp.erase(0, position);
    }

    Workshop shop = Workshop(cabinets);

    cin >> n_test;
    if (n_test < 1 || n_test >= k_upper_limit) {
        cout << "INPUT_ERROR" << endl;
        return 0;
    }

    for (int i = 0; i < n_test; ++i){
        cin >> tmp;
        if (tmp < 0 || tmp >= k_upper_limit){
            cout << "INPUT_ERROR" << endl;
            return 0;
        }
        return_cabinet_id = (i == n_test - 1);
        return_value = shop.workOnItem(tmp, return_cabinet_id);
    }

    if (return_value == cabinets.size()) {
        cout << "OUTSIDE" << endl;
    } else if (return_value > 0) {
        cout << return_value << endl;
    } else if (return_value == 0) {
        cout << "NEW" << endl;
    } else {
        cout << "INPUT_ERROR" << endl;
    }
    return 0;
}