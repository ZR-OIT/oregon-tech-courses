#pragma once

#ifndef NODE_H
# define NODE_H

# include "Person.h"

class Node
{
public:
	Node(const char *fname, const char *lname, const char *email,
		const char *street, const char *city, const char *state, const char *zip);
	~Node(void);
	// Copy constructor.
	//   Both m_next and m_prev should be set to nullptr
	Node(const Node &node);
	// Assignment operator.
	//   Both m_next and m_prev should be set to nullptr
	Node &operator=(const Node &node);

	void Display(void) const;

	void SetNext(Node *next);
	void SetPrev(Node *prev);
	Node * GetNext(void) const;
	Node * GetPrev(void) const;
	Person *GetPerson(void);

	int Compare(const char *fname, const char *lname) const;

private:
	Node(void);
	void clear(void);

	Person * m_person;

	Node *m_next;
	Node *m_prev;
};


#endif // NODE_H