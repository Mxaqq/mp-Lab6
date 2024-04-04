#include <iostream>
#include "tablichka.h"
#include <vector>
#include <list>
using namespace std;
template <class Key, class Value>
class LinearOnArray : public table<Key, Value> {
private:
    vector<Line<Key, Value>> array;  // Массив строк

    int index = 0;  // Индекс актуальной строки

public:
    // Метод поиска строки по ключу
    Value* Find(Key key) override {
        for (auto& line : array) {
            if (line.key == key) {
                return &line.value;
            }
        }
        return nullptr;
    }

    // Метод добавления записи в таблицу
    virtual bool Insert(Key key, Value value) override {
        if (IsFull()) {
            return false;
        }

        // Проверяем, существует ли уже строка с таким ключом
        int pos = -1;
        for (int i = 0; i < array.size(); i++) {
            if (array[i].key == key) {
                pos = i;
                break;
            }
        }

        // Если строка с таким ключом уже существует, возвращаем false
        if (pos != -1) {
            return false;
        }

        // Добавляем новую строку в массив
        array.push_back({ key, value });
        count++;
        return true;
    }

    // Метод удаления записи из таблицы
    virtual bool Delete(Key key) override {
        if (IsEmpty()) {
            return false;
        }

        // Ищем строку с заданным ключом
        int pos = -1;
        for (int i = 0; i < array.size(); i++) {
            if (array[i].key == key) {
                pos = i;
                break;
            }
        }

        // Если строка не найдена, возвращаем false
        if (pos == -1) {
            return false;
        }

        // Удаляем строку из массива
        array[pos] = array[count - 1];
        array.pop_back();
        count--;
        return true;
    }

    // Метод получения ключа актуальной записи
    Key GetKey(void) const override {
        return array[index].key;
    }

    // Метод получения значения актуальной записи
    Value GetValuePtr(void) override {
        return array[index].value;
    }

    // Метод установки актуальной записи на начало таблицы
    void Reset(void) override {
        index = 0;
    }

    // Метод проверки актуальной записи на конец таблицы
    bool IsTabEnded(void) override {
        return index == count;
    }

    // Метод перестановки актуальной записи на следующую строку
    void GoNext(void) override {
        if (index == count) {
            index = 0;
        }
        else {
            index++;
        }
    }
};