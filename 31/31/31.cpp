#define _CRT_SECURE_NO_WARNINGS
#include <map>
#include <iostream>
#include <set>
#include <string>
#include <cstdio>
using namespace std;

class Cmp {
public:
    bool operator () (pair<int, int> a, pair<int, int> b) { // pair(score, track_id)
        if (a.first > b.first)
            return true;
        else if (b.first > a.first)
            return false;
        else {
            return (a.second < b.second);
        }
    }
};

int main() {
    map<int, int> m; //track_id, score
    map<int, int> users_time; //ip,time
    set<pair<int, int>, Cmp > scores; //score, track_id
    for (int i = 1; i <= 100002; i++)
        scores.insert(make_pair(0, i));

    string st;
    while (st != "EXIT") {
        cin >> st;
        if (st == "EXIT") {
            printf("OK");
            break;
        }
        else if (st == "VOTE") {
            int p;
            unsigned int ip = 0;
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
            int score;
            int time;
            scanf("%d%d%d", &track_id, &score, &time);
            int prevscore;
            if (m.find(track_id) == m.end())
                m[track_id] = 0;
            prevscore = m[track_id];
            unsigned int prev_time = users_time[ip];
            if (prev_time == 0 || time - prev_time >= 600) {
                users_time[ip] = time;
                int lastscore = m[track_id];
                set<pair<int, int>, Cmp>::iterator i = scores.find(make_pair(lastscore, track_id));
                if (i != scores.end())
                    scores.erase(i);
                m[track_id] += score;
                scores.insert(make_pair(lastscore + score, track_id));
            }  
            printf("%d\n", m[track_id]);
        }
        else if (st == "GET") {
            printf("%d %d\n", scores.begin()->second, scores.begin()->first); // track_id, track_score
            int track_id = scores.begin()->second;
            m[track_id] = -1;
            scores.erase(scores.begin());
            scores.insert(make_pair(-1, track_id));
        }
    }

    return 0;
}
