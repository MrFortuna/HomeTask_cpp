#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>  // Для манипуляторов вывода
#include <limits>   // Для numeric_limits
#include <utility>  // Для std::pair
using namespace std;

void printLongDouble(long double value) {
    cout << fixed << setprecision(numeric_limits<long double>::max_digits10) << value << endl;
}

std::pair<std::map<long double, std::string>, std::string> code(string a) {
    std::map<long double, std::string> key; // Изменено на long double -> string
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
        string cur = {na2[0]};
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
    cout << itog << " - coded text" << setprecision(numeric_limits<long double>::max_digits10) << endl;

    return make_pair(key, itog); // Возвращаем карту и закодированный текст
}
int decode (std::map<long double, std::string> keys, string a) {

    string decoded = "";
    long double coded = stold("0." + a);

    double currentl = 0.0;
    double currentr = 1.0;
    double savedl = 0.0;
    bool flag = true;
    pair<long double, string> prepairz = {0.0, "-"}; 
    int i = 0;
    //while(flag) {
    for (int i = 0; i < 10; i++) {
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
                    break;
                }
            }
            prepairz = pairz;
            ////cout << "-------" << endl;
            }
            else {
                cout << decoded <<endl;
                return 0;
                
            }
        }
    }
    cout << "Decoded text: "<<decoded <<endl;
    return 0;
}
    /*
    while(!flag) {
        
        for (const auto& pairz : keys) {
            //cout << prepair.first << "!!!!!!" << endl;
            ////cout << currentl * pairz.first << " this is " <<endl;
            if (!flag) {
                if (coded <= (currentr - currentl)* pairz.first + currentl) {
                    //cout << currentl << "---" << currentr << "||" << prepair.first << "||" <<pairz.first << endl;
                    double savedl = currentl;
                    
                    if (prepair.first != keys.begin()->first || i == 0) {
                        //currentl = (currentr - savedl) * pair.first + savedl;
                        currentl = (currentr - savedl)* prepair.first + savedl;
                    }
                    currentr = (currentr - savedl)* pairz.first + savedl;

                    if (pairz.first == 1.0 || prepair.first == 0.9) {
                        flag = true;
                        //cout << "end" <<endl;
                        break;
                        
                    }
                    else {
                        decoded.append(pairz.second);
                        //break;
                    prepair = *keys.begin();
                    }
                 
                }
            prepair = *keys.begin();
            }
        prepair = *keys.begin();
        }
  
        i += 1;
    
    }
    cout<< decoded;
    return 0;
*/

        
int main() {

    string str;
    vector<string> s;

    cout << "Enter multiple lines of text: " << endl;

    while (getline(cin, str)) {
        if (str.empty()) {
            break;
        }
        s.push_back(str);
    }

    
    for (string& it : s) {
        cout << it << endl;
        cout << "text: " << it << endl;
        auto result = code(it);

        // Вывод результата 
        const auto& key = result.first;
        const auto& coded = result.second;

        //cout << "Coded text: " << coded << endl;
        //cout << "Key map:" << endl;
        for (const auto& [probability, character] : key) {
            //cout << probability << " -> " << character << endl;
        }
        //cout << "----------------------------------------------------" << endl;
        decode(key, coded);
    }
    return 0;
}