#include <iostream>
#include "tablichka.h"
#include <vector>
#include <list>
using namespace std;
template <class Key, class Value>
class LinearOnArray : public table<Key, Value> {
private:
    vector<Line<Key, Value>> array;  // ������ �����

    int index = 0;  // ������ ���������� ������

public:
    // ����� ������ ������ �� �����
    Value* Find(Key key) override {
        for (auto& line : array) {
            if (line.key == key) {
                return &line.value;
            }
        }
        return nullptr;
    }

    // ����� ���������� ������ � �������
    virtual bool Insert(Key key, Value value) override {
        if (IsFull()) {
            return false;
        }

        // ���������, ���������� �� ��� ������ � ����� ������
        int pos = -1;
        for (int i = 0; i < array.size(); i++) {
            if (array[i].key == key) {
                pos = i;
                break;
            }
        }

        // ���� ������ � ����� ������ ��� ����������, ���������� false
        if (pos != -1) {
            return false;
        }

        // ��������� ����� ������ � ������
        array.push_back({ key, value });
        count++;
        return true;
    }

    // ����� �������� ������ �� �������
    virtual bool Delete(Key key) override {
        if (IsEmpty()) {
            return false;
        }

        // ���� ������ � �������� ������
        int pos = -1;
        for (int i = 0; i < array.size(); i++) {
            if (array[i].key == key) {
                pos = i;
                break;
            }
        }

        // ���� ������ �� �������, ���������� false
        if (pos == -1) {
            return false;
        }

        // ������� ������ �� �������
        array[pos] = array[count - 1];
        array.pop_back();
        count--;
        return true;
    }

    // ����� ��������� ����� ���������� ������
    Key GetKey(void) const override {
        return array[index].key;
    }

    // ����� ��������� �������� ���������� ������
    Value GetValuePtr(void) override {
        return array[index].value;
    }

    // ����� ��������� ���������� ������ �� ������ �������
    void Reset(void) override {
        index = 0;
    }

    // ����� �������� ���������� ������ �� ����� �������
    bool IsTabEnded(void) override {
        return index == count;
    }

    // ����� ������������ ���������� ������ �� ��������� ������
    void GoNext(void) override {
        if (index == count) {
            index = 0;
        }
        else {
            index++;
        }
    }
};