#include <string>

#include "../memtable/memtable.h"

class SSTable {
private:
    string SSTInfoFileName;
    FILE *SSTInfoFile;

public:
    SSTable();
    ~SSTable();

    void flush(Memtable *memtable);
    string get(const string key);
};