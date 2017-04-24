#include <iostream>
#include <map>
#include <set>
#include <string>
#include "most_frequent_words.h"
using namespace std;

int main() {
    map<string, int> dict;
    string s;
    int ans_number = 4;
    while (cin >> s) {
        dict[s]++;
    }
    vector<pair<string, int> > ans = most_frequent_words(dict,ans_number); // our answer
    for (vector<pair<string, int> >::iterator it = ans.begin(); it != ans.end(); it++)
        cout << it->first << ' ' << it->second << endl;
    return 0;
}

