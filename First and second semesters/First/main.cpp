#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <map>
#include <deque>

using namespace std;

// Задача про кэш с mipt acm.
int main() {
    unsigned int k;
    scanf("%d", &k);
    map<int, int> m; //id->time
    map<int, int> time; // time -> id
    int a = 0;
    unsigned int last;
    unsigned int timer = 0;
    int prev_time = 0;
    int prev_id;
    int size = 0;
    while (size < k) {
        if (scanf("%d",&a) == 1) {
            timer++;
            if (m.find(a) == m.end()) {
                size++;
                printf("%d ", 1);
                m[a] = timer;
                time[timer] = a;
            }
            else {
                printf("%d ", 0);
                prev_time = m[a];
                m[a] = timer;
                time.erase(prev_time);
                time[timer] = a;
            }
        }
        else 
            break;
    }   
    while (scanf("%d",&a) == 1) {
        timer++;
        if (m.find(a) == m.end()) {
            printf("%d ", 1);
            prev_id = time.begin()->second;
            m.erase(prev_id);
            time.erase(time.begin());
            m[a] = timer;
            time[timer] = a;
        }
        else {
            printf("%d ", 0);
            prev_time = m[a];
            m[a] = timer;
            time.erase(prev_time);
            time[timer] = a;
        }
    }
    
    return 0;
}