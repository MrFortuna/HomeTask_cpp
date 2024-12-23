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
    pair<string,map<string,string>> compression(string line) {
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
        map<string, string> short_d(d);
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
        }

        output = balance_arr(output, mx);
        string new_line = "";
        for (string code : output) {
            new_line += code;
        }
        pair<string, map<string, string>> p;
        p.first = new_line;
        p.second = balance_dict(short_d,mx);
        return p;
    }
    string decompression(string code, map<string, string>d) {
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
};

int main()
{
    LZW lzw;
    string line = "";
    pair<string, map<string, string>> p = lzw.compression(line);
    cout << (lzw.decompression(p.first, p.second) == line);
    
}
