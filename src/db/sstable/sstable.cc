#include <iostream>
#include <unistd.h>
#include "./sstable.h"

SSTable::SSTable() {
    SSTInfoFileName = "sstinfo.txt";

    // checking if the file exists
    SSTInfoFile = fopen(SSTInfoFileName.c_str(), "a+");
    if (SSTInfoFile == NULL) {
        perror("fopen");
        exit(1);
    }

    SSTInfoFile = fopen(SSTInfoFileName.c_str(), "r+");
    if (SSTInfoFile == NULL) {
        perror("fopen");
        exit(1);
    }

    fseek(SSTInfoFile, 0, SEEK_END);
    long fileSize = ftell(SSTInfoFile);
    
    if (fileSize == 0) {
        fwrite("0", 1, 1, SSTInfoFile);
        fflush(SSTInfoFile);
    }
}

SSTable::~SSTable() {
    fclose(SSTInfoFile);
}

void SSTable::flush(Memtable *memtable) {
    int sstId;
    fseek(SSTInfoFile, 0, SEEK_SET);
    fscanf(SSTInfoFile, "%d", &sstId);

    // create a new sstable with the id "sstId"
    string sstName = "sstable" + to_string(sstId) + ".sst"; 
    FILE *sst = fopen(sstName.c_str(), "w");
    if (sst == NULL) {
        perror("fopen");
        exit(1);
    }

    int fd = fileno(SSTInfoFile);
    if (fd == -1) {
        perror("Error getting file descriptor");
        fclose(SSTInfoFile);
        return;
    }

    // Truncate the file to zero length
    if (ftruncate(fd, 0) == -1) {
        perror("Error truncating file");
        fclose(SSTInfoFile);
        return;
    }

    fseek(SSTInfoFile, 0, SEEK_SET);
    fwrite(to_string(sstId + 1).c_str(), 1, to_string(sstId).size(), SSTInfoFile);
    fflush(SSTInfoFile);

    memtable -> dump(sst);
    fclose(sst);
}

string SSTable::get(const string neededKey) {
    int sstId;
    fseek(SSTInfoFile, 0, SEEK_SET);
    fscanf(SSTInfoFile, "%d", &sstId);

    for (int i = sstId-1; i >= 0; i--) {
        string sstName = "sstable" + to_string(i) + ".sst";
        FILE *sst = fopen(sstName.c_str(), "r");
        if (sst == NULL) {
            perror("fopen");
            exit(1);
        }

        char* line = NULL;
        size_t len = 0;
        ssize_t read;

        fseek(sst, 0, SEEK_SET);
        while ((read = getline(&line, &len, sst)) != -1) {
            string key(line);

            read = getline(&line, &len, sst);
            if (read == -1) {
                break;
            }

            string value(line);

            // remove newline character
            key.pop_back(); 
            value.pop_back(); 

            if (neededKey == key) {
                free(line);
                return value;
            }
        }
        free(line);
    }
    return "";
}   