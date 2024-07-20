#include <iostream>
#include <map>
#include <string>

#include "memtable.h"

using namespace std;

#define MAX_MEMTABLE_SIZE 4

Memtable::Memtable() {}

Memtable::~Memtable() {}

void Memtable::put(const string key, const string value) {
    memtable[key] = value;
}

string Memtable::get(const string key) {
    if (memtable.find(key) == memtable.end()) {
        return "";
    }
    return memtable[key];
}

void Memtable::remove(const string key) {
    memtable.erase(key);
}

void Memtable::dump(FILE *file) {
    for (auto ele: memtable) {
        fprintf(file, "%s\n%s\n", ele.first.c_str(), ele.second.c_str());
    }
    fflush(file);
}

void Memtable::clear() {
    memtable.clear();
}

bool Memtable::is_full() {
    if (memtable.size() >= MAX_MEMTABLE_SIZE) {
        return true;
    }
    return false;
}