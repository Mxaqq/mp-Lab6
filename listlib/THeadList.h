#pragma once
#include "TList.h"
using namespace std;


template<class T>
class THeadList : public TList<T>
{
protected:
	TNode<T>* pHead;  // заголовок, pFirst - звено за pHead
public:
	THeadList();
	~THeadList();
	void InsertFirst(T item); // вставка звеньев после заголовка
	void DeleteFirst(); // удалить первое звено
};

template<class T>
THeadList<T>::THeadList()
{
	pHead = new TNode<T>;
	pHead->pNext = nullptr;
}

template<class T>
THeadList<T>::~THeadList()
{
	while (pHead->pNext != nullptr)
	{
		DeleteFirst();
	}
	delete pHead;
}

template <class T>
void THeadList<T>::InsertFirst(T item)
{
	TNode<T>* pNode = new TNode<T>;
	pNode->pNext = pHead->pNext;
	pHead->pNext = pNode;
	pNode->data = item;
}

template <class T>
void THeadList<T>::DeleteFirst()
{
	if (pHead->pNext != nullptr)
	{
		TNode<T>* pNode = pHead->pNext;
		pHead->pNext = pNode->pNext;
		delete pNode;
	}
}