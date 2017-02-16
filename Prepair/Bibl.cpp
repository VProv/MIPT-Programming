#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

class Author {
    string title;
    int count;
public:
    Author (const string& t, int c) :title(t),count(c) {}
    Author ():title(),count() {}
    void set_count(int c) {
        count = c;
    }
    int get_count()const {
        return count;
    }
    string get_title()const {
        return title;
    }
};

class Func {
public:
    void operator() (pair<string,Author> p) {
        cout << p.second.get_title() << ' ' << p.second.get_count() << endl;
    }
};

class Cmp {
public:
    bool operator() (const Author& a, const Author& b) {
        return a.get_title() < b.get_title();
    }
};

int main() {
    multimap<string,Author > mapi; // Author name and data
    map<string, set<string> > mapa; // Autor and his books
    int m;
    cin >> m;
    string st1,title;
    int count;
    for (int i = 0; i < m; i++) {
        cin >> st1;
        if (st1 == "add") {
            cin >> st1;
            cin >> title;
            cin >> count;
            Author a(title, count);            
            mapi.insert(make_pair(st1,a));            
        }
        else if (st1 == "delete") {
            cin >> st1;
            cin >> title;
            cin >> count;
            int num;

            multimap<string,Author>::iterator it1 = mapi.equal_range(st1).first;
            multimap<string, Author>::iterator it2 = mapi.equal_range(st1).second;
            int num = 0;
            for (multimap<string, Author>::iterator it = it1; it != it2; it++) {
                if (it->second.get_title() == title) {
                    num = it->second.get_count() - count;
                    if (num < 0)
                        num = 0;
                    if (num == 0) {
                        mapi.erase(it);
                    }
                    else {
                        it->second.set_count(num);
                    }
                }
            }            
        }
        else if (st1 == "print") {
            cin >> st1;
            multimap<string, Author>::iterator it1 = mapi.equal_range(st1).first;
            multimap<string, Author>::iterator it2 = mapi.equal_range(st1).second;
            vector<Author> v;
            for (multimap<string, Author>::iterator it = it1; it != it2; it++)
                v.push_back(it->second);
            stable_sort(v.begin(), v.end(),Cmp());
            for (vector<Author>::iterator ite = v.begin(); ite != v.end(); ite++)
                cout << ite->get_title() << ' ' << ite->get_count() << endl;
        }
    }

    return 0;
}