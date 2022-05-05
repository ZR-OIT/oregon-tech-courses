#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <iostream>

using std::cout;
using std::endl;

// A forward declaration for the List class.
class List;

class Node
{
public:
	Node(int data);
	~Node(void);

	friend class List;
private:

	int m_data;
	Node *m_next;
};

class List
{
public:
	List(void);
	~List(void);

	// Append places the new Node at the end of the List.
	void Append(int data);
	void Display(void);

private:
	Node *m_head;
	Node *m_tail;
};
////////////////////NODE////////////////////////////
Node::Node(int data) : m_data(data), m_next(nullptr)
{
	//empty
}
Node::~Node(void)
{
	m_data = 0;
	m_next = nullptr;
}
////////////////////LIST///////////////////////////
List::List(void) : m_head(nullptr), m_tail(nullptr)
{
	//empty
}
List::~List(void)
{
	Node *travel = m_head;
	Node *trail = m_head;

	while (trail != nullptr)
	{
		travel = trail->m_next;
		delete trail;
		trail = travel;
	}
	m_head = nullptr;
	m_tail = nullptr;
	travel = nullptr;
	trail = nullptr;
}
void List::Append(int data)
{
	Node *new_node = new Node(data);
	if (m_tail == nullptr)
	{
		m_head = new_node;
		m_tail = new_node;
		m_head->m_next = m_tail;
		m_tail->m_next = nullptr;
	}
	else
	{
		m_tail->m_next = new_node;
		m_tail = new_node;
		m_tail->m_next = nullptr;
	}
}
void List::Display(void)
{
	Node *travel = m_head;
	while (travel != nullptr)
	{
		cout << travel->m_data << endl;
		travel = travel->m_next;
	}
}
//////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{
		List list;
		list.Append(1);
		list.Append(2);
		list.Append(3);

		list.Display();
	}
}
