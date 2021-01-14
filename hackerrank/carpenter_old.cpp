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
class Cabinet{
 public:
  Cabinet(const long capacity) : capacity_(capacity) {};

  int getItem(int key) {
      if (map_.find(key) != map_.end()){
          auto itr = map_[key];
          cache_.erase(itr);
          map_.erase(key);
          return key;
      } else {
          throw invalid_argument("Key is not in the cabinet when it should!");
      }
  }
  int putItem(int key) {
      cache_.push_front(key);
      map_[key] = cache_.begin();
      if (cache_.size() > capacity_) {
          int last = cache_.back();
          cache_.pop_back();
          return last;
      }
      return -1; // TODO return what if id is -1?
  }

  void printCabinet() const{
      for (const int& i : cache_) {
          cout << i << ", ";
      }
      cout << endl;
  }
 private:
  long capacity_;
  list<int> cache_;
  unordered_map<int, list<int>::iterator> map_;
};

class Workshop{
 public:
  Workshop(const vector<long>& cabinets) {
      for (const long& c : cabinets){
          cabinets_.emplace_back(c);
      }
      cabinets_.emplace_back(2e9);
  }
  /**
   *
   * @param key
   * @return int    cabinet id <0, ..., N - 1> where the item was, -1 if NEW, -2 if OUTSIDE, other if ERROR
   */
  int workOnItem(int key) {
      int return_value;
      if (item2cabinet_.find(key) == item2cabinet_.end()) {
          // NEW
          return_value = -1;
          int ret = cabinets_[0].putItem(key);
          item2cabinet_[key] = 0;
          int id = 0;
          while (ret != -1) {
              ++id;
              item2cabinet_[ret] = id;
              ret = cabinets_[id].putItem(ret);
          }
      } else {
          int cab_id = item2cabinet_[key];
          if (cab_id == cabinets_.size() - 1) {
              return_value = -2;
          } else {
              return_value = cab_id;
          }
          cabinets_[cab_id].getItem(key);
          int ret = cabinets_[0].putItem(key);
          item2cabinet_[key] = 0;
          int id = 0;
          while (ret != -1) {
              ++id;
              item2cabinet_[ret] = id;
              ret = cabinets_[id].putItem(ret);
          }
      }
      return return_value;
  }
  void printWorkshop() const{
      int i = 1;
      for (const Cabinet& c : cabinets_){
          if (i == cabinets_.size()) {
              cout << "OUTSIDE" << endl;
          } else {
              cout << "Cabinet " << i++ << endl;
          }
          c.printCabinet();
      }
  }
 private:
  vector<Cabinet> cabinets_;
  unordered_map<int, int> item2cabinet_;
};

class SingleWorkshop {
 public:
  explicit SingleWorkshop(vector<long> cabinets) : capacities_(move(cabinets)) {}

  // O(sum cabinets capacities)
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
//      int dis = distance(items_.begin(), map_[key]);
//
//      for (int i = 1; i < capacities_.size(); ++i) {
//          if (capacities_[i] > dis) {
//              return i;
//          }
//      }
//      return capacities_.size();
  }

  // O(1) if return_previousCabint == false else O(sum cabinets capacities)
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
    chrono::steady_clock::time_point begin, end;
    vector<long> cabinets;
    vector<long> cabinets_old;
    char delimeter = ' ';
    long tmp;
    int n_test;
    int ret = -1;
    size_t pos;

    string cabinets_temp;
    getline(cin, cabinets_temp);
    cabinets.push_back(0);
    int idx = 0;
    while (!cabinets_temp.empty()){
        pos = cabinets_temp.find(delimeter);
        tmp = stol(cabinets_temp.substr(0, pos));
        if (tmp < 1) {
            cout << "INPUT_ERROR" << endl;
            return 0;
        }
        cabinets.push_back(tmp + cabinets[idx]);
        cabinets_old.push_back(tmp);
        ++idx;
        pos = pos == string::npos ? pos : pos + 1;
        cabinets_temp.erase(0, pos);
    }

    Workshop shop_old = Workshop(cabinets_old);
    SingleWorkshop shop = SingleWorkshop(cabinets);

    cin >> n_test;

    vector<long> items;
    for (int i = 0; i < n_test; ++i){
        cin >> tmp;
        items.push_back(tmp);
    }
    bool ret_cab = false;
    begin = chrono::steady_clock::now();
    for (int i = 0; i < n_test; ++i){
        ret = shop_old.workOnItem(items[i]);
    }
    end = chrono::steady_clock::now();
    cout << "Time Workshop_old = " << std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count() << "[ns]" << std::endl;

    begin = chrono::steady_clock::now();
    for (int i = 0; i < n_test; ++i){
        ret_cab = (i == n_test - 1);
        ret = shop.workOnItem(items[i], ret_cab);
    }
    end = chrono::steady_clock::now();
    cout << "Time singleWorkshop = " << std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count() << "[ns]" << std::endl;

    if (ret == cabinets.size()) {
        cout << "OUTSIDE" << endl;
    } else if (ret > 0) {
        cout << ret << endl;
    } else if (ret == 0) {
        cout << "NEW" << endl;
    } else {
        cout << "INPUT_ERROR" << endl;
    }
    return 0;
}