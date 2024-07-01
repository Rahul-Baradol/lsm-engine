#include <map>
#include <string>

using namespace std;

class Memtable {
private:
    map<string, string> memtable;

public:
    Memtable();
    ~Memtable();

    void put(const string key, const string value);

    string get(const string key);
    
    void remove(const string key);
};