#include <iostream> 
#include "db.h"

using namespace std;

DB::DB() {
    memtable = new Memtable();
}

DB::~DB() {
    delete memtable;
}

void DB::put(const string key, const string value) {
    memtable->put(key, value);
}

string DB::get(const string key) {
    return memtable->get(key);
}

void DB::remove(const string key) {
    memtable->remove(key);
}