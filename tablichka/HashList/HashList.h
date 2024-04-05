#include <iostream>
#include "../tablichka.h"
using namespace std;



template <class Key, class Value>
class HashList : public table<Key, Value> {
private:
    vector<vector<Line<Key, Value>>> table;

    struct Index {
        int vector_id = 0;
        int list_id = 0;
        bool end = false;
    } index;

public:
    int HashFunction(const string& key) {
        int result = 0;
        for (char c : key) {
            result += c;
        }
        return result;
    }

    Value* Find(Key key) override {
        int vector_id = HashFunction(key);
        if (vector_id >= table.size()) {
            return nullptr;
        }

        for (auto& line : table[vector_id]) {
            if (line.key == key) {
                return &line.value;
            }
        }

        return nullptr;
    }

    virtual bool Insert(Key key, Value value) override {
        if (IsFull()) {
            return false;
        }

        int vector_id = HashFunction(key);
        if (vector_id >= table.size()) {
            table.resize(vector_id + 1);
        }

        for (auto& line : table[vector_id]) {
            if (line.key == key) {
                return false;
            }
        }

        table[vector_id].push_back({ key, value });
        count++;
        Reset();
        return true;
    }

    virtual bool Delete(Key key) override {
        if (IsEmpty()) {
            return false;
        }

        int vector_id = HashFunction(key);
        if (vector_id >= table.size()) {
            return false;
        }

        for (auto it = table[vector_id].begin(); it != table[vector_id].end(); it++) {
            if (it->key == key) {
                table[vector_id].erase(it);
                count--;
                Reset();
                return true;
            }
        }

        return false;
    }

    Key GetKey(void) const override {
        return table[index.vector_id][index.list_id].key;
    }

    Value GetValuePtr(void) override {
        return table[index.vector_id][index.list_id].value;
    }

    void Reset(void) override {
        index.end = false;
        int i = 0;
        while (i < table.size() && table[i].empty()) {
            i++;
        }
        if (i == table.size()) {
            index.end = true;
            return;
        }
        index.vector_id = i;
        index.list_id = 0;
    }

    bool IsTabEnded(void) override {
        return index.end;
    }

    void GoNext(void) override {
        if (table[index.vector_id].size() <= index.list_id + 1) {
            int i = index.vector_id + 1;
            while (i < table.size() && table[i].empty()) {
                i++;
            }
            if (i == table.size()) {
                index.end = true;
                return;
            }
            index.vector_id = i;
            index.list_id = 0;
        }
        else {
            index.list_id++;
        }
    }
};