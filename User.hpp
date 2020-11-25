#include <string>
#include <iostream>

using namespace std;

class User
{
public:
    bool modified;
    string id, dir, pwd;
    void set (string d, string r, string p);
    void display();
};

