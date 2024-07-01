#include <iostream>
#include <map>
#include <string>
#include "memtable.h"

using namespace std;

Memtable::Memtable() {}

Memtable::~Memtable() {}

void Memtable::put(const string key, const string value) {
    memtable[key] = value;
}

string Memtable::get(const string key) {
    return memtable[key];
}

void Memtable::remove(const string key) {
    memtable.erase(key);
}