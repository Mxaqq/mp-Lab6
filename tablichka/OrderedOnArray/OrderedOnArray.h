#include <iostream>
#include "../tablichka.h"
#include <algorithm>
using namespace std;



template <class Key, class Value>
class OrderedOnArray : public table<Key, Value> {
private:
    vector <Line> arr; 
    int index = 0; 
public:

   
    Value* Find(Key key) override;

    virtual bool Insert(Key key, Value value) override;

    virtual bool Delete(Key key) override;

    Key GetKey(void) const override;

    Value GetValuePtr(void) override;

    void Reset(void) override;

    bool IsTabEnded(void) override;

    void GoNext(void) override;
};

template<class Key, class Value>
inline Value* OrderedOnArray<Key, Value>::Find(Key key)
{
    bool fl = false;
    int l = 0, r = (count - 1);
    int c;
    while (l <= r) {
        c = (r + l) / 2;
        if (arr[c].key == key) {
            fl = true;
            break;
        }
        if (arr[c].key > key) {
            r = c - 1;
        }
        if (arr[c].key < key) {
            l = c + 1;
        }
    }
    if (!fl) return nullptr;
    return &arr[c].value;
}

template<class Key, class Value>
inline bool OrderedOnArray<Key, Value>::Insert(Key key, Value value)
{
    int l = 0, r = count - 1, pos = count;
    int c;
    if (this->IsFull()) {
        return false;
    }
    while (l <= r) {
        c = (r + l) / 2;;
        if (arr[c].key == key) return false;
        if (arr[c].key > key) {
            pos = c;
            r = c - 1;
        }
        if (arr[c].key < key) {
            l = c + 1;
        }
    }
    if (pos == count) {
        arr.push_back({ key, value });
    }
    else {
        arr.insert(arr.begin() + pos, { key, value });
    }
    count++;
    return true;
}

template<class Key, class Value>
inline bool OrderedOnArray<Key, Value>::Delete(Key key)
{
    bool fl = false;
    int l = 0, r = (count - 1);
    int c;
    if (this->IsEmpty()) {
        return false;
    }
    while (l <= r) {
        c = (r + l) / 2;
        if (arr[c].key == key) {
            arr.erase(arr.begin() + c);
            count--;
            return true;
        }
        if (arr[c].key > key) {
            r = c - 1;
        }
        if (arr[c].key < key) {
            l = c + 1;
        }
    }
    return false;
}

template<class Key, class Value>
inline Key OrderedOnArray<Key, Value>::GetKey(void) const
{
    return arr[index].key;
}

template<class Key, class Value>
inline Value OrderedOnArray<Key, Value>::GetValuePtr(void)
{
    return arr[index].value;
}

template<class Key, class Value>
inline void OrderedOnArray<Key, Value>::Reset(void)
{
    index = 0;
}

template<class Key, class Value>
inline bool OrderedOnArray<Key, Value>::IsTabEnded(void)
{
    return index == count;
}

template<class Key, class Value>
inline void OrderedOnArray<Key, Value>::GoNext(void)
{
    if (index == count)
        index = 0;
    else {
        index++;
    }
}
