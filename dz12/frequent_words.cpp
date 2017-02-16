/*
#include <algorithm>
#include <ctype.h>
#include <map>
#include <set>

using namespace std;

map<string, int>  dict;

int isrusalpha(char c) {
    return isalpha(c) || (c >= 'À' && c <= 'ß') || (c >= 'à' && c <= 'ÿ');
}

int main() {
    char word[1024];
    int answer_size = 20;
    int min_word_length = 5;
    int c, i;

    while ((c = getchar()) != EOF) {
        if (isrusalpha(c)) {
            i = 0;
            do {
                word[i++] = c;
                c = getchar();
            } while (isrusalpha(c) && i < 1023);
            word[i] = 0;
            if (i >= min_word_length) {
                string s = word;
                if (dict.find(s) == dict.end())
                    dict[s] = 1;
                else
                    dict[s] += 1;
            }
        }
    }

    set< pair<int, string> > ans;
    map<string, int>::iterator it;

    for (it = dict.begin(); it != dict.end(); it++) {
        ans.insert(make_pair(it->second, it->first));
        if (ans.size() > answer_size) {
            ans.erase(ans.begin());
        }
    }

    set< pair<int, string> >::reverse_iterator it2;

    for (it2 = ans.rbegin(); it2 != ans.rend(); it2++) {
        printf("%20s %d\n", it2->second.c_str(), it2->first);
    }

    return 0;
}
*/