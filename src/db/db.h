#include <string>

#include "commitlog/commitlog.h"
#include "sstable/sstable.h"

class DB {
private:
    Memtable *memtable;
    CommitLog *commitlog;
    SSTable *sstable;

public:
    DB();
    ~DB();

    void put(const string key, const string value);

    string get(const string key);

    void remove(const string key);
};