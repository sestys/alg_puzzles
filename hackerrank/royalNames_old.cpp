#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);


// Complete the getSortedList function below.

int roman2int(const char& numeral) {
    switch (numeral) {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        default:
            return 0;
    }
}

int decodeRoman(const string& number) {
    if (number.empty()) {
        return 0;
    }
    int sum = 0;
    int curr, next;
    curr = roman2int(number[0]);
    for (int i = 0; i < number.size(); ++i){
        next = i + 1 < number.size() ? roman2int(number[i + 1]) : 0;
        if (curr >= next) {
            sum += curr;
        } else {
            sum -= curr;
        }
        curr = next;
    }
    return sum;
}

struct stringIntSort{
  inline bool operator() (const pair<string, int> & a, const pair<string, int>& b){
      if (a.first == b.first){
          return a.second < b.second;
      } else {
          return a.first < b.first;
      }
  }
};

vector<string> getSortedList(const vector<string>& names) {
    vector<pair<string, int>> nameNum;
    unordered_map<string, string> map;
    for (const string& name : names){
        string num = name;
        size_t pos = num.find(' ');
        string first = num.substr(0, pos);
        num.erase(0, pos + 1);
        int n = decodeRoman(num);

        map[first + to_string(n)] = name;
        nameNum.emplace_back(first, n);
    }
    sort(nameNum.begin(), nameNum.end(), stringIntSort());
    vector<string> result;
    for(const pair<string, int> &king : nameNum){
        result.emplace_back(map[king.first + to_string(king.second)]);
    }
    return result;

}

int main()
{
    chrono::steady_clock::time_point begin, end;

    string names_count_temp;
    getline(cin, names_count_temp);

    int names_count = stoi(ltrim(rtrim(names_count_temp)));

    vector<string> names(names_count);

    for (int i = 0; i < names_count; i++) {
        string names_item;
        getline(cin, names_item);

        names[i] = names_item;
    }
    begin = chrono::steady_clock::now();
    vector<string> res = getSortedList(names);
    end = chrono::steady_clock::now();
    cout << "Time old = " << std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count() << "[ns]" << std::endl;
//    for (int i = 0; i < res.size(); i++) {
//        cout << res[i];
//
//        if (i != res.size() - 1) {
//            cout << "\n";
//        }
//    }
//
//    cout << "\n";

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
