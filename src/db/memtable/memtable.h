#pragma once

#include <map>
#include <string>
#include <iostream>
#include "skiplist.h"

using namespace std;

class Memtable {
private:
    Skiplist *memtable;

public:
    Memtable();
    ~Memtable();

    void put(const string key, const string value);

    string get(const string key);
    
    void remove(const string key);

    void clear();

    void dump(FILE *file);

    bool is_full();
};