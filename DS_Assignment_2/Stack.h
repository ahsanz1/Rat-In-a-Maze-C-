#include<iostream>
using namespace std;

template <class T>
class Stack
{
private:
	T* stackPtr;
	int top;
	int maxSize;

public:
	Stack();
	Stack(int);
	bool isFull();
	bool isEmpty();
	void push(const T&);
	void pop();
	T stackTop();
	~Stack();
};

template <class T>
Stack<T>::Stack()
{
	maxSize = 100;
	stackPtr = new T[maxSize];
	top = 0;
}

template <class T>
Stack<T>::Stack(int size = 100)
{
	maxSize = size;
	stackPtr = new T[maxSize];
	top = 0;
}

template <class T>
bool Stack<T>::isFull()
{
	return (top == maxSize);
}

template <class T>
bool Stack<T>::isEmpty()
{
	return (top == 0);
}

template <class T>
void Stack<T>::push(const T& value)
{
	if (isFull())
		cout << "Stack is Full!!" << endl;
	else
	{
		stackPtr[top] = value;
		top++;
	}
}

template <class T>
void Stack<T>::pop()
{
	if (!isEmpty())
		top--;
	else
		cout << "Stack is  Empty!!" << endl;
}

template <class T>
T Stack<T>::stackTop()
{
	if (!isEmpty())
		return stackPtr[top - 1];
	else
		cout << "Stack is Empty!!" << endl;
}

template <class T>
Stack<T>::~Stack()
{
	delete[] stackPtr;
}