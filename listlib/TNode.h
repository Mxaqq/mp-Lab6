#pragma once

template<class T>
struct Node
{
    T value;
    Node<T>* pPrev;
    Node<T>* pNext;
    Node(T value, Node<T>* pPrev = nullptr, Node<T>* pNext = nullptr) {
        this->pNext = pNext;
        this->pPrev = pPrev;
        this->value = value;
    }

};