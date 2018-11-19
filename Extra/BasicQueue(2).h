#pragma once
#include <iostream>
using namespace std;

class Unit
{
private:
	string m_sName;
public:
	Unit(const string s) : m_sName(s) {}
	friend ostream& operator<<(ostream& s, const Unit& u);
};

template <class T>
class Node
{
public:
	T m_tData;
	Node<T>* m_pNext;
	Node(T val) : m_tData(val), m_pNext(nullptr) {}
};

template <class T>
class BasicQueue
{
private:
	Node<T>* m_pHead;
	Node<T>* m_pTail;
public:
	BasicQueue() : m_pHead(nullptr), m_pTail(nullptr) {}
	~BasicQueue()
	{
		//Node<T>* current = m_pHead; // Consider this an iterator.
		Node<T>* next;
		while (m_pHead != nullptr)
		{
			next = m_pHead->m_pNext;
			delete m_pHead;
			m_pHead = next;
		}
	}
	void enQueue(T val) // 'Push' method.
	{
		Node<T>* newNode = new Node<T>(val);
		if (m_pHead == nullptr) // List is empty.
		{
			m_pHead = m_pTail = newNode;
		}
		else // New node becomes the new tail.
		{
			m_pTail->m_pNext = newNode;
			m_pTail = m_pTail->m_pNext;
		}
	}
	T deQueue() // 'Pop' method. 
	{
		if (m_pHead != nullptr)
		{
			T val = m_pHead->m_tData; // Storing the data to be returned.
			Node<T>* next;
			next = m_pHead->m_pNext;
			delete m_pHead; // Deallocating head.
			m_pHead = next;
			return val; // Throwing copy of old head's data.
		}
	}
	bool isEmpty()
	{
		return m_pHead == nullptr;
	}
	void print()
	{
		if (isEmpty())
			return;
		cout << "Queue contents: ";
		Node<T>* current = m_pHead;
		while (current != nullptr)
		{
			cout << current->m_tData << ' ';
			current = current->m_pNext;
		}
		cout << endl;
	}
};

ostream& operator<<(ostream& s, const Unit& u)
{
	s << u.m_sName;
	return s;
}






