#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "TStackException.h"

using std::cout;
using std::ostream;
using std::endl;

namespace {
	const size_t TSTACK_MAX_SIZE_DEFAULT = 5;
	const size_t TSTACK_MAX_UPPERBOUND_DEFAULT = 50;
}

template <class T>
class TStack
{
public:
	TStack(int max_size = TSTACK_MAX_SIZE_DEFAULT);
	TStack(const TStack<T> &tstack);
	TStack<T>& operator = (const TStack<T> & orig);

	~TStack(void);

	void Push(const T& item);
	T Pop(void);
	T &Peek(void);

	bool IsFull(void) const;
	bool IsEmpty(void) const;
	int GetStackSize(void) const;
	int GetMaxSize(void) const;

	friend ostream &operator << (ostream& os, const TStack<T> &tstack)
	{
		tstack.display(os);
		return os;
	};

private:
	T *m_stack;

	int m_maxSize;
	int m_size;

	void display(ostream& os) const;
};

template<typename T>
inline TStack<T>::TStack(int max_size) 
	: m_maxSize(max_size), m_size(0)  //, m_stack(new T[max_size])
{
	if (m_maxSize > TSTACK_MAX_UPPERBOUND_DEFAULT)
	{
		// this is really in here to show you that you can throw an exception
		// in a constructor.
		throw TStackException(__FILE__, __FUNCTION__, " Stack maxSize cannot exceed 50 elements ", __LINE__);
	}
	m_stack = new T[max_size];
}

template<class T>
inline TStack<T>::TStack(const TStack<T>& tstack)
	: m_maxSize(tstack.m_maxSize), m_size(0), m_stack(new T[tstack.m_maxSize])
{
	for (int i = 0; i < m_size; i++)
	{
		Push(tstack.m_stack[i]);
	}
}

template<class T>
inline TStack<T>& TStack<T>::operator=(const TStack<T>& orig)
{
	if (this != &orig) {
		delete[] m_stack;

		m_size = 0;
		m_maxSize = orig.m_maxSize;
		m_stack = new T[m_maxSize];

		for (int i = 0; i < orig.m_size; i++)
		{
			Push(orig.m_stack[i]);
		}
	}

	return *this;
}

template<typename T>
inline void TStack<T>::Push(const T & item)
{
	if (IsFull())
	{
		throw TStackException(__FILE__, __FUNCTION__, " Can't push onto an already full stack ", __LINE__);
	}
	m_stack[m_size++] = item;
}

template<typename T>
inline T TStack<T>::Pop(void)
{
	if (IsEmpty())
	{
		throw exception("Can't pop off an empty stack");
	}
	return m_stack[--m_size];
}

template<typename T>
inline T &TStack<T>::Peek(void)
{
	if (IsEmpty())
	{
		throw -17;
	}
	return m_stack[m_size - 1];
}

template<typename T>
inline bool TStack<T>::IsFull(void) const
{
	return m_size >= m_maxSize;
}

template<typename T>
inline bool TStack<T>::IsEmpty(void) const
{
	return m_size <= 0;
}

template<typename T>
inline int TStack<T>::GetStackSize(void) const
{
	return m_size;
}

template<typename T>
inline int TStack<T>::GetMaxSize(void) const
{
	return m_maxSize;
}

template<typename T>
inline TStack<T>::~TStack(void)
{
	delete[] m_stack;
}

template<class T>
inline void TStack<T>::display(ostream & os) const
{
	for (int i = 0; i < m_size; i++)
	{
		os << m_stack[i] << endl;
	}
}
