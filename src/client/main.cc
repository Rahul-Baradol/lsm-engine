#include <iostream>

#include "../db/db.h"

using namespace std;

int main() {
    DB *db1 = new DB();

    db1->put("a", "2");
    db1->put("b", "5");
    db1->put("c", "10");

    cout << "Before remove" << endl;
    cout << "a -> " << db1->get("a") << endl;
    cout << "b -> " << db1->get("b") << endl;
    cout << "c -> " << db1->get("c") << endl << endl;

    db1->remove("a");
    db1->remove("c");

    cout << "After remove" << endl;
    cout << "a -> " << db1->get("a")     << endl;
    cout << "b -> " << db1->get("b") << endl;
    cout << "c -> " << db1->get("c") << endl << endl;

    delete db1;

    cout << "After DB restarted" << endl;
    
    DB *db2 = new DB();
    cout << "a -> " << db2->get("a") << endl;
    cout << "b -> " << db2->get("b") << endl;
    cout << "c -> " << db2->get("c") << endl;

    return 0;
}