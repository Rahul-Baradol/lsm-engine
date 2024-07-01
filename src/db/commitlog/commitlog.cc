#include <iostream>

#include "commitlog.h"

CommitLog::CommitLog(Memtable *memtable) {
    filename = "commit.log";
    
    file = fopen(filename.c_str(), "a+");
    if (file == NULL) {
        perror("fopen");
        exit(1);
    }

    // if "commit.log" exists and has contents, populate the memtable
    fseek(file, 0, SEEK_END);
    if (ftell(file) != 0) {
        cout << "Loading memtable from commit log" << endl;
        loadMemTable(memtable);
    }
}

CommitLog::~CommitLog() {
    fclose(file);
}

void CommitLog::append(string data) {
    data += "\n";
    fwrite(data.c_str(), 1, data.size(), file);
}

void CommitLog::clear() {
    freopen(filename.c_str(), "w", file);
}

void CommitLog::loadMemTable(Memtable* memtable) {
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    fseek(file, 0, SEEK_SET);
    while ((read = getline(&line, &len, file)) != -1) {
        string key(line);

        read = getline(&line, &len, file);
        if (read == -1) {
            break;
        }

        string value(line);

        // remove newline character
        key.pop_back(); 
        value.pop_back(); 

        memtable->put(key, value);
    }
    free(line);
}