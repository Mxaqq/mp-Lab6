#include <iostream>
#include "tablichka.h"
using namespace std;



template <class Key, class Value>
class LinearOnArray : public table<Key, Value> {
private:
    vector<Line<Key, Value>> storage;
    int current_index = 0;

public:
    Value* Find(Key key) override {
        for (Line<Key, Value>& line : storage) {
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

        for (Line<Key, Value>& line : storage) {
            if (line.key == key) {
                return false;
            }
        }

        storage.push_back({ key, value });
        count++;
        return true;
    }

    virtual bool Delete(Key key) override {
        if (IsEmpty()) {
            return false;
        }

        for (int i = 0; i < storage.size(); i++) {
            if (storage[i].key == key) {
                storage[i] = storage[count - 1];
                storage.pop_back();
                count--;
                return true;
            }
        }

        return false;
    }

    Key GetKey(void) const override {
        return storage[current_index].key;
    }

    Value GetValuePtr(void) override {
        return &storage[current_index].value;
    }

    void Reset(void) override {
        current_index = 0;
    }

    bool IsTabEnded(void) override {
        return current_index == count;
    }

    void GoNext(void) override {
        if (current_index == count) {
            current_index = 0;
        }
        else {
            current_index++;
        }
    }
};