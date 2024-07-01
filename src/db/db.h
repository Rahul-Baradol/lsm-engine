#include <string>
#include "memtable/memtable.h"

class DB {
private:
    Memtable *memtable;

public:
    DB();
    ~DB();

    void put(const string key, const string value);

    string get(const string key);

    void remove(const string key);
};