#pragma once

template<class T>
class MaxStack {

public:

	MaxStack() noexcept;

	bool empty() noexcept;

	void push(T value);

	void pop();

	void clear();

	size_t size() noexcept { return sz; }

	T& top();

	~MaxStack();

private:

	template<class T>
	class Note {
	public:
		T value; 
		Note* next;
		
		Note(T value = T(), Note* next = nullptr) {
			this->value = value;
			this->next = next;
		}
	};

	Note<T>* head; 
	size_t sz; 
};


template<class T>
inline MaxStack<T>::MaxStack() noexcept
{
	head = nullptr;
	sz = 0;
}

template<class T>
bool MaxStack<T>::empty() noexcept
{
	if (sz == 0)
		return true;
	return false;
}

template<class T>
void MaxStack<T>::push(T value)
{
	if (head == nullptr)
		head = new Note<T>(value);
	else {
		Note<T>* temp = new Note<T>(value, head);
		this->head = temp;
	}
	sz++;
}

template<class T>
void MaxStack<T>::pop()
{
	if (this->empty())
		throw std::exception("Ionoonoao?o yeaiaiou a noaea");
	Note<T>* temp = head;
	head = head->next;
	delete temp;
	sz--;
}

template<class T>
inline void MaxStack<T>::clear()
{
	while (!this->empty())
		this->pop();
}

template<class T>
T& MaxStack<T>::top()
{
	if (this->empty())
		throw std::exception("Ionoonoao?o yeaiaiou a noaea");
	return head->value;
}

template<class T>
inline MaxStack<T>::~MaxStack()
{
	this->clear();
}