#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>  // Для манипуляторов вывода
#include <limits>   // Для numeric_limits
#include <utility>  // Для std::pair
#include "arithmetic_coding.h"

using namespace std;

void printLongDouble(long double value) {
    cout << fixed << setprecision(numeric_limits<long double>::max_digits10) << value << endl;
}

pair<map<long double, string>, string> code_to_arithmetic(string a) {
    map<long double, std::string> key; // Изменено на long double -> std::string
    vector<string> chars;
    vector<long double> p;
    string na{a + '*'};
    string na2 = na;
    //cout << na << endl;

    // Подсчет вероятностей
    while (na.length() > 0) {
        string word{na[0]};
        unsigned count = 0;

        for (unsigned i{}; i <= na.length() - word.length();) {
            int position = na.find(word, i);
            if (position == string::npos) break;
            ++count;
            i = position;
            na.erase(position, 1);
        }

        //cout << "p[" << word << "] = " << (long double)(count) / (long double)(a.length() + 1) << endl;

        chars.push_back(word);
        p.push_back((long double)(count) / (long double)(a.length() + 1));
    }

    // Накопление вероятностей
    long double intr = 0.0;
    for (int i = 0; i < p.size(); i++) {
        p[i] += intr;
        intr = p[i];
    }

    // Заполнение карты вероятностей
    for (int i = 0; i < p.size(); i++) {
        //cout << p[i] << "--- " << chars[i] << endl;
        key[p[i]] = chars[i]; // Вероятность -> символ
    }

    long double l = 0;
    long double r = 1;
    //printLongDouble(l);
    // Кодирование
    while (na2.length() > 0) {
        
        //cout << l << "-" << r << endl;
        std::string cur = {na2[0]};
        long double savedl = l;
        auto asd = find(chars.begin(), chars.end(), cur);
        if (distance(chars.begin(), asd) != 0) {
            l = (r - savedl) * p[distance(chars.begin(), asd) - 1] + savedl;
        }
        r = (r - savedl) * p[distance(chars.begin(), asd)] + savedl;
        na2.erase(0, 1);
    }

    // Итоговый диапазон
    
    string sl = to_string(l);
    string sr = to_string(r);
    string itog{};
    for (int i = 2; i < sl.length(); i++) {
        if (sl[i] == sr[i]) {
            itog.append({sl[i]});
        } else {
            itog.append({sr[i]});
            break;
        }
    }
    //cout << itog << " - coded text" << setprecision(numeric_limits<long double>::max_digits10) << endl;

    return make_pair(key, itog); // Возвращаем карту и закодированный текст
}
string decode_from_arithmetic (map<long double, string> keys, string a) {

    string decoded = "";
    long double coded = stold("0." + a);

    double currentl = 0.0;
    double currentr = 1.0;
    double savedl = 0.0;
    bool flag = true;
    pair<long double, string> prepairz = {0.0, "-"}; 
    int i = 0;
    while(flag) {
    //for (int i = 0; i < 100000; i++) {
        prepairz = {0.0, "-"}; 
        for (const auto& pairz : keys) {
            if (flag) {
                
            
            //cout << (currentr - currentl) * pairz.first + currentl << " sravnivaem s "  << coded << endl;
            if (coded <= (currentr - currentl) * pairz.first + currentl) {

                savedl = currentl;
                
                //cout << prepairz.first << "|| "<< pairz.first << endl;
                if (pairz.first != keys.begin()->first || prepairz.first != 0.0) {
                    currentl = (currentr - savedl) * prepairz.first + savedl;
                }
                currentr = (currentr - savedl) * pairz.first + savedl;

                //cout << currentl << "---" << currentr << endl;
                if (pairz.first == 1.0 || pairz.second == "*") {
                    flag = false;
                    //cout << "end" <<endl;
                    break;
                        
                }
                else {
                    decoded.append(pairz.second);
                    //flag = false;
                    break;
                }
            }
            prepairz = pairz;
            ////cout << "-------" << endl;
            }
            else {
                //cout << decoded <<endl;
                return decoded;
                
            }
        }
    }
    //cout << "Decoded text: "<<decoded <<endl;
    return decoded;
}
/*
int main() {

    string a = "hey you";

    auto coded_a =  code_to_arithmetic(a); 

    cout << coded_a.second << endl;
    for (auto& a: coded_a.first) {
        cout << a.second << " --- " << a.first << endl;
    }
    cout << decode_from_arithmetic(coded_a.first, coded_a.second);

    return 0;
}
*/
