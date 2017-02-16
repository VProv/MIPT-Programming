#include "User_data.h"
using namespace std;

void User::add_phone(const string& phone) {
    phone_num.insert(phone);
}

void User::delete_phone(const string& phone) {
    phone_num.erase(phone);
}
