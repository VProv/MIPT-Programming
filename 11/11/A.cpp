#include <iostream>
#include <string>

using namespace std;

int main() {
    string st;
    getline(cin,st);
    int size = st.size();
    int len1 = (size + 1) / 2;
    st += st.substr(0,len1);
    st.erase(0,len1);
    cout << st << endl;
    
    return 0;
}