#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);


// Complete the getSortedList function below.

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
    int value = 0;
    int current, next;
    current = roman2int(number[0]);
    for (int i = 1; i < number.size(); ++i){
        next = roman2int(number[i]);
        if (current >= next) {
            value += current;
        } else {
            value -= current;
        }
        current = next;
    }
    value += current;
    return value;
}

struct Name {
  const string full_name_;
  string first_name_;
  int ordinal_number_;

  explicit Name(const string& full_name) : full_name_(full_name) {
      size_t pos = full_name.find(' ');
      first_name_ = full_name.substr(0, pos);
      ordinal_number_ = decodeRoman(full_name.substr(pos + 1, string::npos));
  }
};

struct name_comparator {
  bool operator() (const Name &a, const Name &b) {
      if (a.first_name_ == b.first_name_) {
          return a.ordinal_number_ < b.ordinal_number_;
      } else {
          return a.first_name_ < b.first_name_;
      }
  }
};

vector<string> getSortedList(const vector<string>& names) {
    set<Name, name_comparator> sortedNames;
    for (const string& name : names){
        sortedNames.insert(Name(name));
    }

    vector<string> result;
    for(const Name& name : sortedNames){
        result.push_back(name.full_name_);
    }
    return result;
}

int main()
{
//    ofstream fout(getenv("OUTPUT_PATH"));
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
    cout << "Time new = " << std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count() << "[ns]" << std::endl;

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

