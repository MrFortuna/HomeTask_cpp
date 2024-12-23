#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <utility>

using namespace std;
ostream& operator << (ostream& os, map<string,string> m){
    string line;
    for (auto& pair : m) {
        line += pair.first + " : " + pair.second + "\n";
    }
    return os << line;
}

class LZW {
private:
    map <string, string> short_d;
public:
    string balance(string num, int ln) {
        string new_num;
        if (num.length() > ln) {
            return num;
        }
        for (int i = 0; i < (ln - num.length()); i++) {
            new_num += '0';
        }
        return new_num + num;
    }
    map <string, string> mix(map <string, string> d) {
        map <string, string> new_d;
        for (auto& pair : d) {
            new_d[pair.second] = pair.first;
        }
        return new_d;
    }
    map <string, string> make_short(map <string, string> d, int start, int end) {
        int index = 0;
        map <string, string> new_d;
        for (auto& pair : d) {
            if (start <= index and index < end) {
                new_d[pair.first] = pair.second;
            }
            index += 1;
        }
        return new_d;
    }
    map <string, string> balance_dict(map <string, string> d,int mx) {
        vector <string> keys;
        vector <string> values;
        for (auto& pair : d) {
            keys.push_back(pair.first);
            values.push_back(pair.second);
        }
        map <string, string> new_d;
        for (auto& pair : d) {
            new_d[pair.first] = balance(pair.second, mx);
        }
        return new_d;
    }
    vector<string> balance_arr(vector<string> arr, int mx) {
        vector <string> new_arr;
        for (string value : arr) {
            new_arr.push_back(balance(value, mx));
        }
        return new_arr;
    }
    bool in_map(string value, map<string, string> d) {
        for (auto& pair : d) {
            if (value == pair.first) {
                return true;
            }
        }
        return false;
    }
    string makeWhole(pair<string, map<string, string>> data) {
        string result;
        for (auto& p : data.second) {
            result += "(" + p.first + ":" + p.second + ")";
        }
        result += "###!!!###" + data.first;
        return result;
    }
    map <string, string> makeMap(string line) {
        map <string, string> d;
        bool for_key = false;
        string key;
        bool for_value = false;
        string value;
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == '(') {
                for_key = true;
                continue;
            }
            else if (line[i] == ':') {
                for_key = false;
                for_value = true;
                continue;

            }
            else if (line[i] == ')') {
                for_value = false;
                d[key] = value;
                key = "";
                value = "";
                continue;
            }
            if (for_key) {
                key += line[i];
            }
            if (for_value) {
                value += line[i];
            }
        }
        return d;
    }
    pair <string, map<string, string>> makeSeparate(string data) {
        pair < string, map<string, string>> output;
        int start_of_separate = data.find("###!!!###");
        string line = data.substr(start_of_separate + 9);
        output.first = line;
        output.second = makeMap(data.substr(0, start_of_separate + 1));
        return output;
    }
    string compression_with_pair(string line) {
        map<string, string> d;
        int index = 0;
        vector<string> output;
        for (int i = 0; i < line.length(); i++) {
            string letter(1, line[i]);
            if (!in_map(letter, d)) {
                d[letter] = to_string(index);
                index += 1;
            }
        }
        map<string, string> short_d_for_pair(d);
        string pref = "";
        int mx = 0;
        for (int i = 0; i < line.length(); i++) {
            string letter(1, line[i]);
            if (in_map(pref + letter, d)) {
                pref += letter;
            }
            else {
                output.push_back(d[pref]);
                d[pref + letter] = to_string(index);
                pref = letter;
                index += 1;
                mx = max(mx, int(to_string(index).length()));
            }
            if (line.length() - 1 == i) {
                output.push_back(d[pref]);
            }
            cout << line.length() - i << endl;
        }

        output = balance_arr(output, mx);
        string new_line = "";
        for (string code : output) {
            new_line += code;
        }
        pair<string, map<string, string>> p;
        p.first = new_line;
        p.second = balance_dict(short_d_for_pair,mx);
        return makeWhole(p);
    }
    string decompression_with_pair(string line) {
        pair <string, map<string, string>> p = makeSeparate(line);
        map <string, string> d = p.second;
        string code = p.first;
        d = mix(d);
        int step;
        for (auto& pair : d) {
            step = pair.first.length();
            break;
        }
        string output;
        output += d[code.substr(0, step)];
        int index = d.size();
        for (int i = step; i < code.length(); i = i + step) {
            if (!in_map(code.substr(i, step), d)) {
                d[balance(to_string(index), step)] = d[code.substr(i - step, step)] + d[code.substr(i - step, step)][0];
                output += d[balance(to_string(index), step)];
                index += 1;
            }
            else {
                output += d[code.substr(i, step)];
                d[balance(to_string(index), step)] = d[code.substr(i - step,step)] + d[code.substr(i, step)][0];
                index += 1;
            }
        }
        return output;
    }
    map <string, string> show_short_d() {
        return short_d;
    }
    string compression(string line) {
        map<string, string> d;
        int index = 0;
        vector<string> output;
        for (int i = 0; i < line.length(); i++) {
            string letter(1, line[i]);
            if (!in_map(letter, d)) {
                d[letter] = to_string(index);
                index += 1;
            }
        }
        short_d = d;
        string pref = "";
        int mx = 0;
        for (int i = 0; i < line.length(); i++) {
            string letter(1, line[i]);
            if (in_map(pref + letter, d)) {
                pref += letter;
            }
            else {
                output.push_back(d[pref]);
                d[pref + letter] = to_string(index);
                pref = letter;
                index += 1;
                mx = max(mx, int(to_string(index).length()));
            }
            if (line.length() - 1 == i) {
                output.push_back(d[pref]);
            }
            cout << line.length() - i << endl;
        }
        short_d = balance_dict(short_d, mx);
        output = balance_arr(output, mx);
        string new_line = "";
        for (string code : output) {
            new_line += code;
        }
        return new_line;
    }
    string decompression(string code) {
        map<string,string> d = short_d;
        d = mix(d);
        int step;
        for (auto& pair : d) {
            step = pair.first.length();
            break;
        }
        string output;
        output += d[code.substr(0, step)];
        int index = d.size();
        for (int i = step; i < code.length(); i = i + step) {
            if (!in_map(code.substr(i, step), d)) {
                d[balance(to_string(index), step)] = d[code.substr(i - step, step)] + d[code.substr(i - step, step)][0];
                output += d[balance(to_string(index), step)];
                index += 1;
            }
            else {
                output += d[code.substr(i, step)];
                d[balance(to_string(index), step)] = d[code.substr(i - step, step)] + d[code.substr(i, step)][0];
                index += 1;
            }
            cout << code.length() - i << endl;
        }
        return output;
    }
};