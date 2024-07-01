#include <string>

#include "commitlog/commitlog.h"

class DB {
private:
    Memtable *memtable;
    CommitLog *commitlog;

public:
    DB();
    ~DB();

    void put(const string key, const string value);

    string get(const string key);

    void remove(const string key);
};