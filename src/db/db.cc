#include <iostream> 

#include "db.h"

using namespace std;
  
DB::DB() {
    memtable = new Memtable();
    commitlog = new CommitLog(memtable);
    sstable = new SSTable();
}

DB::~DB() {
    delete memtable;
    delete commitlog;
    delete sstable;
}

void DB::put(const string key, const string value) {
    commitlog->append(key);
    commitlog->append(value);
    commitlog->flush();

    memtable->put(key, value);
   
    if (memtable->is_full()) {
        sstable->flush(memtable);
        memtable->clear();
        commitlog->clear();
    }
}

string DB::get(const string key) {
    string answer = memtable->get(key);

    if (answer != "") {
        return answer;
    }

    answer = sstable -> get(key);
    return answer;
}

void DB::remove(const string key) {
    commitlog->append(key);
    commitlog->append("");
    commitlog->flush();

    memtable->remove(key);

}