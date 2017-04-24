#include <iostream>
#include <string>
#include <algorithm>
#include <list>
using namespace std;

class Ticket {
    string flight;
    string name;
    string date;
public:
    Ticket(const string& f, const string & n, const string & d):flight(),name(),date() {
        flight = f;
        name = n;
        date = d;
    }
    Ticket() :flight(), name(), date() {}
    void setTicket(const string& f, const string & n, const string & d) {
        flight = f;
        name = n;
        date = d;
    }

    string get_flight()const {
        return flight;
    }

    string get_name()const {
        return name;
    }

    string get_date()const {
        return date;
    }

    void print()const {
        cout << flight << ' ' << name << ' ' << date << endl;
    }
    bool operator == (const Ticket& a) {
        if (flight == a.flight && date == a.date && name == a.name)
            return true;
        else
            return false;
    }
};

int main() {
    int m;
    cin >> m;
    string fl;
    string na;
    string da;
    string st1;
    Ticket temp;
    list<Ticket> l;
    for (int i = 0; i < m; i++) {
        cin >> st1;
        if (st1 == "add") {
            cin >> fl;
            cin >> na;
            cin >> da;
            temp.setTicket(fl, na, da);
            l.push_back(temp);
            cout << "OK" << endl;
        }
        else if (st1 == "delete") {
            cin >> fl;
            cin >> na;
            cin >> da;
            temp.setTicket(fl, na, da);
            l.erase(find(l.begin(), l.end(), temp));
            cout << "OK" << endl;
        }
        else if (st1 == "print") {
            cin >> st1;
            if (st1 == "flight") {
                cin >> fl;
                for (list<Ticket>::iterator it = l.begin(); it != l.end(); it++) {
                    if (it->get_flight() == fl)
                        it->print();
                }
            }
            else if (st1 == "date") {
                cin >> da;
                for (list<Ticket>::iterator it = l.begin(); it != l.end(); it++) {
                    if (it->get_date() == da)
                        it->print();
                }
            }
            else if (st1 == "all") {
                for (list<Ticket>::iterator it = l.begin(); it != l.end(); it++)
                    it->print();
            }
        }
    }
    int n;
    cin >> n;

    return 0;
}