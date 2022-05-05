#pragma once

#ifndef ADDRESSLIST_H
# define ADDRESSLIST_H

# include "Node.h"

class AddressList
{
public:
	AddressList(void);
	AddressList(const AddressList &addressList);
	~AddressList(void);
	AddressList &operator=(const AddressList &addressList);

	// Insert the new person into the ordered list
	void Insert(const char *fname, const char *lname, const char *email,
		const char *street, const char *city, const char *state, const char *zip);

	void Display(bool forward = true);
	// Return true is address was found and deleted, else false.
	bool Delete(const char *fname, const char *lname);
	Person *Find(const char *fname, const char *lname) const;

	void Clear(void);
	size_t Length(void);

private:
	void prepend(const char *fname, const char *lname, const char *email,
		const char *street, const char *city, const char *state, const char *zip);

	Node *m_head;
	Node *m_tail;

	size_t m_length;
};

#endif // ADDRESSLIST_H