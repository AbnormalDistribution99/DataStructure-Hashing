#include "Hash.hpp"
#include <fstream>

Hash::Hash() {
    init (23);
}
Hash::~Hash() {
    free(state);
}
bool Hash::isPrime(int n) {
    if (n == 2 || n == 3) return true;
    if (n == 1 || n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}
int Hash::nextPrime(int n) {
    if (n <= 0)     n = 3;
    if (n % 2 == 0) n++;
    for (; !isPrime( n ); n += 2);
    return n;
}
int Hash::hash_s(string s) {
    int ret = 0;
    for (int i = 0; i < s.length(); i++) ret += s[i];
    return ret % cap;
}
void Hash::rehash() {
    User *old = cells;
    int ocap = cap;
    init(2 * cap);
    for (int i = 0; i < ocap; i++) insert(old[i]);
    free(old);
}

void Hash::init(int ncap) {
    cap = nextPrime(ncap);
    cells = new User[cap];
    state = new enum EntryType[cap];
    for (int i = 0; i < cap; i++) state[i] = Unmodified;
}

int Hash::find(string id) {
    int val = hash_s(id);
    int cols = 0;
    while (true) {
        if (state[val] == Unmodified) return -1;
        if (state[val] == Filled and cells[val].id == id) break;
        val = (val + 2 * ++cols - 1) % cap;
        if (cols == cap) return -1;
    }
    return val;
}

int Hash::posFor(string id) {
    int val = hash_s(id);
    int cols = 0;
    while (true) {
        if (state[val] == Unmodified) break;
        if (state[val] == Filled and cells[val].id == id) break;
        val = (val + 2 * ++cols - 1) % cap;
        if (cols == cap) return -1;
    }
    return val;
}
void Hash::insert(User nUser) {
    insert (nUser.id, nUser.dir, nUser.pwd);
}
void Hash::insert(string id, string dir, string pwd) {
    int val = posFor(id);
    while (val == -1) {
        rehash();
        val = posFor(id);
    }
    cells[val].set(id, dir, pwd);
    state[val] = Filled;
    cout << "Successfully added the user\n";
}

void Hash::remove(string id) {
    int val = find(id);
    if (val == -1) {
        cout << "That user was not found\n";
    } else {
        state[val] = Modified;
        cout << "User has been removed\n";
    }
}
void Hash::home(string id, string home) {
    int val = find(id);
    if (val == -1) {
        cout << "That user was not found\n";
    } else {
        cells[val].dir = home;
        cout << "Successfully changed the home directory\n";
    }
}
void Hash::pwd(string id, string pwd) {
    int val = find(id);
    if (val == -1) {
        cout << "That user was not found\n";
    } else {
        cells[val].pwd = pwd;
        cout << "Successfully changed the password\n";
    }
}

void Hash::display() {
    cout << "Displaying the user table\n";
    cout<< setw(20) << "Mod" << setw(20) << "User" << setw(20) << "Home Dir"
            << setw(5) << "Pwd" << endl;
    for (int i = 0; i < cap; i++) {
        string mod = "";
        if (state[i] == Modified) mod = "M";
        cout<< setw(10) << i << setw(10) << mod << endl;
        if (state[i] != Filled) {
            cout << "\n";
            continue;
        }
        cells[i].display();
    }
}
void Hash::display(string id) {
    int val = find(id);
    if (val == -1) {
        cout << "That user was not found\n";
    } else {
        cout << "That user was found\n";
        cout <<setw(20) << "Mod" << setw(20) << "User" << setw(20) << "Home Dir"<< setw(5) << "Pwd" << endl;
        string mod = "";
        if (state[val] == Modified) mod = "M";
        cout << setw(10) << val << setw(10) << mod << endl;
        cells[val].display();
    }
}
void Hash::verify(string id, string pwd) {
    int val = find(id);
    if (val == -1) {
        cout << "Validation has failed\n";
    } else {
        if (cells[val].pwd == pwd) cout << "User successfully validated\n";
        else cout << "Validation has failed\n";
    }
}
void Hash::save(string file) {
    ofstream fout;
    fout.open(file.c_str());
    for (int i = 0; i < cap; i++) {
        if (state[i] != Filled) continue;
        fout << cells[i].id << " " << cells[i].dir << " " << cells[i].pwd << '\n';
    }
    cout << "Successfully saved the entries in the table\n";
}

