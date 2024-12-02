#pragma once
#include <random>

using namespace std;

class RandomNumberGenerator {
public:
    RandomNumberGenerator();
    double generate();

private:
    random_device rd;
    mt19937 gen;
    uniform_real_distribution<> dis;
};

class Skiplist {
public:
    typedef struct Node {
        string key;
        string value;
        Node *next, *down;
    } Node;

    Node *head;
    RandomNumberGenerator rng;

    Skiplist();

    string search(string target);
    void add(string key, string value);
    bool erase(string target);
};