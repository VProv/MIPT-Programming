#pragma once
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

class Cmp {
public:
    bool operator () (pair<int, string> a, pair<int, string> b) {
        if (a.first < b.first)
            return true;
        else if (b.first < a.first)
            return false;
        else {
            return (a.second > b.second);
        }
    }
};

vector<pair<string,int> > most_frequent_words(map<string, int> dict, int ans_number = 4) {
    set< pair<int, string>, Cmp > ans;
    map<string, int>::iterator it;

    for (it = dict.begin(); it != dict.end(); it++) {
        ans.insert(make_pair(it->second, it->first));
        if (ans.size() > ans_number) {
            ans.erase(ans.begin());
        }
    }
    
    set< pair<int, string> >::reverse_iterator it2;
    vector<pair<string, int> > answer;
    for (it2 = ans.rbegin(); it2 != ans.rend(); it2++) {
        answer.push_back(make_pair(it2->second, it2->first));
    }
    
    return answer;
}