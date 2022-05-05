#pragma once

#ifndef NODE_H
# define NODE_H

# include "Person.h"

class Node
{
public:
	// basic ctor for a Node with a Person.
	Node(const char *fname, const char *lname, const char *email,
		const char *street, const char *city, const char *state, const char *zip);

	// the Node ante-ctor.
	~Node(void);

	// Copy constructor.
	//   Both m_next and m_prev should be set to nullptr
	Node(const Node &node);

	// Assignment operator.
	//   Both m_next and m_prev should be set to nullptr
	Node &operator=(const Node &node);

	// Don't duplicate the code from the Person::Display() method.
	void Display(void) const;

	void SetNext(Node *next);
	void SetPrev(Node *prev);
	Node * GetNext(void) const;
	Node * GetPrev(void) const;

	// return a pointer to the provate Person pointer.
	Person *GetPerson(void);

	// don't duplicate the Compare() method from Person.
	int Compare(const char *fname, const char *lname) const;

private:
	// we don't want to have a Node without a person.
	Node(void);

	// delallocate all the stuff for a Node. The dtor should call
	// this method and not duplicate code.
	void clear(void);

	Person * m_person;

	Node *m_next;
	Node *m_prev;
};

#endif // NODE_H
