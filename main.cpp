/*
 Student Name: Abhishek Regmi.
 Student NetID: ar2818.
 Compiler Used: X-code.
 Program Description: Implementation of Hash table to store users, home directory and passwords.
 
 */


#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <fstream>
#include <list>
#include "Hash.hpp"

using namespace std;

Hash _hash;

void printInputDescription() {
    cout << ">> ";
}

void printErrorCommand() {
    cout << "Error! Please check your input." << endl;
}
void handleCommand(stringstream &ss, string cmd) {
    if (cmd == "exit") {
        // exit program
        exit(0);
    } else if (cmd == "load") {
        string tp;
        getline(ss, tp, ' ');
        if (tp == "pwd") {
            string file;
            getline(ss, file, ' ');
            ifstream fin(file.c_str());
            while (true) {
                string id, dir, pwd;
                getline(fin, id, ' ');
                getline(fin, dir, ' ');
                getline(fin, pwd, '\n');
                if (id == "") break;
                _hash.insert(id, dir, pwd);
            }
            cout << "Successfully loaded the table.\n";
        } else {
            cout << "Executing your script file.\n";
            // parses the contents of the file
            string file, str;
            file = tp;
            ifstream fin(file.c_str());
            while (true) {
                str = "";
                getline(fin, str);
                if (str == "") break;
                stringstream fs(str);
                getline(fs, cmd, ' ');
                /* Call handleCommand function recursively so that
                commands in file including "load" will be executed properly */
                handleCommand(fs, cmd);
            }
        }
    } else if (cmd == "save") {
        string s, file;
        getline(ss, s, ' ');
        getline(ss, file, ' ');
        _hash.save(file);
    } else if (cmd == "new") {
        string id, pwd;
        getline(ss, id, ' ');
        getline(ss, pwd, ' ');
        string dir = "/users/" + id;
        _hash.insert(id, dir, pwd);
    } else if (cmd == "remove") {
        string id;
        getline(ss, id, ' ');
        _hash.remove(id);
    } else if (cmd == "clear") {
        _hash.init(23);
        cout << "Resetting the user table\n";
    } else if (cmd == "display" ) {
        string id;
        getline(ss, id, ' ');
        if (id =="") {
            _hash.display();
        } else {
            _hash.display(id);
        }
    } else if (cmd == "verify") {
        string id, pwd;
        getline(ss, id, ' ');
        getline(ss, pwd, ' ');
        _hash.verify(id, pwd);
    } else if (cmd == "home") {
        string id, home;
        getline(ss, id, ' ');
        getline(ss, home, ' ');
        _hash.home(id, home);
    } else if (cmd == "passwd") {
        string id, passwd;
        getline(ss, id, ' ');
        getline(ss, passwd, ' ');
        _hash.pwd(id, passwd);
    } else {
        // Input commands may be wrong command then display this message
        printErrorCommand();
    }
}

int main() {
    string str;
    string cmd;
    while (true) {
        // Print Input description
        printInputDescription();
        // Input command line
        getline(cin, str);
        stringstream ss(str);
        //Get command token
        getline(ss, cmd, ' ');
        // Do actions according to command category
        handleCommand(ss, cmd);
    }
    return 0;
}
