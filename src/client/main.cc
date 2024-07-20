#include <iostream>

#include "../db/db.h"

using namespace std;

int main() {
    DB *db = new DB();

    while (1) {
        cout << "put, get, delete?: ";
        string command;
        cin >> command;

        if (command == "put") {
            string key, value;
            cout << "key: ";
            cin >> key;

            cout << "value: ";
            cin >> value;   

            db -> put(key, value);
            cout << endl;
            continue;
        }

        if (command == "get") {
            string key;
            cout << "key: ";
            cin >> key;

            cout << db -> get(key) << endl;
            continue;
        }

        if (command == "delete") {
            string key;
            cout << "key: ";
            cin >> key;

            db -> remove(key);
            cout << endl;
            continue;
        }

        cout << "pls...don't mess me up!" << endl;
    }

    return 0;
}