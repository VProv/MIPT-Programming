#include <string>
#include <iostream>
#include <algorithm>
#include "TextEditor.h"

using namespace std;

int main() {
    string st;
    string str;
    char p;
    while (getline(cin, str)) {
        st += str;
        st += '\n';
    }
    cin.clear();
    TextEditor TE;
    TE._Editor(st);

    vector<string> vs = TE.get_text();
    int le = vs.size();
    for (int i = 0; i < le; i++)
        cout << vs[i];
    
    int n;
    cin >> n;
    return 0;
}