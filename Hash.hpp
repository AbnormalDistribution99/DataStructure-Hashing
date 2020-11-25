#include <string>
#include <iostream>
#include "User.hpp"

using namespace std;

class Hash
{
public:
    enum EntryType {
        Unmodified, Modified, Filled
    };
    Hash();
    ~Hash();
    
    void init(int ncap);
    void insert(User nUser);
    void insert(string id, string dir, string pwd);
    void remove(string id);
    void home(string id, string home);
    void pwd(string id, string pwd);
    void display();
    void display(string id);
    void save(string file);
    void verify(string id, string pwd);

private:
    bool isPrime(int n);
    int nextPrime(int n);
    int hash_s(string s);
    void rehash();
    int find(string id);
    int posFor(string id);

    int cap;
    User *cells;
    enum EntryType *state;
};

