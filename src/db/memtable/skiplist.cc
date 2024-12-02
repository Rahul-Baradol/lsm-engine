#include <random>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "skiplist.h"

using namespace std;

RandomNumberGenerator::RandomNumberGenerator() : gen(rd()), dis(0.0, 1.0) {}

double RandomNumberGenerator::generate() {
    return dis(gen);
}

Skiplist::Skiplist() {
    head = (Node*) malloc(sizeof(Node));
    head -> key = "";
    head -> value = "";
    head -> next = NULL;
    head -> down = NULL;
}

string Skiplist::search(string target) {
    // display("search");
    Node *cur = head;

    while (cur != NULL) {
        while (cur -> next != NULL && cur -> next -> key < target) {
            cur = cur -> next;
        }

        if (cur -> next != NULL && cur -> next -> key == target) {
            return cur -> next -> value;
        }
        cur = cur -> down;
    }

    return "";
}

void Skiplist::add(string key, string value) {
    // display("add before");
    
    Node *cur = head;
    vector<Node*> v;

    while (cur != NULL) {
        while (cur -> next != NULL && cur -> next -> key < key) {
            cur = cur -> next;
        }

        if (cur -> next != NULL && cur -> next -> key == key) {
            cur -> next -> value = value;
        } else {
            v.push_back(cur);
        }
        cur = cur -> down;
    }

    bool insert = true;
    Node *down = NULL;

    while (insert && !v.empty()) {
        Node *last = v.back();
        v.pop_back();

        Node *newNode = (Node*) malloc(sizeof(Node));
        newNode -> key = key;
        newNode -> value = value;
        newNode -> next = last -> next;
        newNode -> down = down;

        last -> next = newNode;
        down = newNode;

        double rn = rng.generate();
        insert = rn < 0.5;
    }

    if (insert) {
        Node *newNode = (Node*) malloc(sizeof(Node));
        newNode -> key = "";
        newNode -> value = "";
        newNode -> next = NULL;
        newNode -> down = head;

        head = newNode;
    }
}

bool Skiplist::erase(string num) {
    bool found = false;
    Node *cur = head;

    while (cur != NULL) {
        while (cur -> next != NULL && cur -> next -> key < num) {
            cur = cur -> next;
        }

        if (cur -> next != NULL && cur -> next -> key == num) {
            cur -> next = cur -> next -> next;
            found = true;
        }

        cur = cur -> down;
    }
    return found;
}