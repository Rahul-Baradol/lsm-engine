#include <string>

#include "../memtable/memtable.h"

using namespace std;

class CommitLog {
private:
    string filename;
    FILE* file;

public:
    CommitLog(Memtable *memtable);
    ~CommitLog();

    void append(string data);
    void loadMemTable(Memtable* memtable);   
    void clear();
    void flush();
};