#include <iostream> 

#include "db.h"

using namespace std;

DB::DB() {
    memtable = new Memtable();
    commitlog = new CommitLog(memtable);
}

DB::~DB() {
    delete memtable;
    delete commitlog;
}

void DB::put(const string key, const string value) {
    commitlog->append(key);
    commitlog->append(value);

    memtable->put(key, value);
}

string DB::get(const string key) {
    return memtable->get(key);
}

void DB::remove(const string key) {
    commitlog->append(key);
    commitlog->append("");

    memtable->remove(key);
}