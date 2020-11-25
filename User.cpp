#include <cstdio>
#include "User.hpp"
#include <iomanip>

void User::set(string d, string r, string p) {
    id = d;
    dir = r;
    pwd = p;
}

void User::display() {
    cout<<setw(20) << id << setw(20) << dir << setw(5) << "*" << endl;
}

