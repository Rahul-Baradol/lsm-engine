#include <iostream>
#include "../db/db.h"

using namespace std;

int main() {
    DB db;

    db.put("a", "2");
    db.put("b", "10");
    db.put("c", "20");

    cout << db.get("a") << endl;
    cout << db.get("b") << endl;
    cout << db.get("c") << endl;

    db.remove("a");

    cout << db.get("a") << endl;
    cout << db.get("b") << endl;
    cout << db.get("c") << endl;
    return 0;
}