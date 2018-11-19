#pragma once
#include <iostream>
using namespace std;


template <class T>
class Node
{
public:
	T m_tData;
	char m_cPriority;
	Node<T>* m_pNext;
	Node(T val, char priority) : m_tData(val), m_cPriority(priority), m_pNext(nullptr) {}
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
	void enQueue(T val, char priority) // 'Push' method.
	{
		Node<T>* newNode = new Node<T>(val, priority);
		if (m_pHead == nullptr) // List is empty.
		{
			m_pHead = m_pTail = newNode;
		}
		else 
		{
			Node<T>* currentPosition = m_pHead;
			// Verify where to put this
			if (currentPosition->m_cPriority > newNode->m_cPriority) {
				// This has to be the new Head
				newNode->m_pNext = m_pHead;
				m_pHead = newNode;
				return;
			}
			// If it is not the new head, it must be inside....
			while (currentPosition != m_pTail  && currentPosition->m_pNext->m_cPriority <= newNode->m_cPriority) {
				currentPosition = currentPosition->m_pNext;
			}
			if (currentPosition == m_pTail) {
				m_pTail->m_pNext = newNode;
				m_pTail = newNode;
			}
			else {
				newNode->m_pNext = currentPosition->m_pNext;
				currentPosition->m_pNext = newNode;
			}
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







