#include <map>
#include <iostream>
#include <set>
#include <string>
using namespace std;

// Task from acm mipt.(Заказ песен на радио.)
class Cmp {
public:
    bool operator () (pair<int, int> a, pair<int, int> b) { // pair(score, track_id)
        if (a.first < b.first)
            return true;
        else if (b.first < a.first)
            return false;
        else {
            return (a.second > b.second);
        }
    }
};

int main() {
    map<int, int> m; //track_id, score
    map<int, int> users_time; //ip,time
    set<pair<int, int>, Cmp > scores; //score, track_id
    for (int i = 1; i <= 100002; i++)
        scores.insert(make_pair(0,i));

    string st;
    while (st != "EXIT") {
        cin >> st;
        if (st == "EXIT") {
            cout << "OK" << endl;
            break;
        }
        else if (st == "VOTE") {
            int p;
            int ip = 0;
            char c;
            for (int i = 0; i < 4; i++) {
                cin >> p;
                if (i != 3)
                    cin >> c;
                if (i == 0)
                    ip += (p << 24);
                else if (i == 1)
                    ip += (p << 16);
                else if (i == 2)
                    ip += (p << 8);
                else 
                    ip += p;               
            }
            int track_id;
            cin >> track_id;
            int score;
            cin >> score;
            int time;
            cin >> time;
            int prevscore;
            if (m.find(track_id) == m.end())
                m[track_id] = 0;
            prevscore = m[track_id];
            if (users_time.find(ip) != users_time.end())
                if (time - users_time[ip] < 600) {
                    users_time[ip] = time;
                    cout << prevscore << endl;
                    continue;
                }
            users_time[ip] = time;
            m[track_id] += score;
            pair<int, int> pa = make_pair(prevscore, track_id);
            if (scores.find(pa) != scores.end())
                scores.erase(pa);
            scores.insert(make_pair(m[track_id], track_id));
            cout << m[track_id] << endl;
        }
        else if (st == "GET") {
            cout << scores.rbegin()->second << ' ' << scores.rbegin()->first << endl;
            int track_id = scores.rbegin()->second;
            m[track_id] = -1;
            scores.erase((*scores.rbegin()));
            scores.insert(make_pair(-1,track_id));
        }        
    }
    
    int n;
    cin >> n;
    
    return 0;
}
