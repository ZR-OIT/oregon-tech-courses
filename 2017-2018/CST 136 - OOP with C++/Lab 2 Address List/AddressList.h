#pragma once

#ifndef ADDRESSLIST_H
# define ADDRESSLIST_H

# define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

# include "Node.h"

static const char ADDRESS_FILE[] = "AddressBook.csv";

class AddressList
{
public:
	// create an empty list.
	// use base member initialization (aka colon int) whenever possible.
	AddressList(void);

	// the copy ctor.
	AddressList(const AddressList &addressList);

	// the ante-ctor.
	~AddressList(void);

	// the assignment operator.
	AddressList &operator=(const AddressList &addressList);

	// Insert the new person into the __ordered__ list.
	void Insert(const char *fname, const char *lname, const char *email,
		const char *street, const char *city, const char *state, const char *zip);

	// insert all the data from addressList into the existing list
	void Insert(const AddressList &addressList);

	// Return person pointer if lname/fname was found and deleted, else nullptr.
	// since this returns a pointer, it is up to you to de-allocate the memory.
	Person * Delete(const char *fname, const char *lname);
	// remove all the items from addressList from the list. if address list
	// if the same as this, skip the removal.
	bool Delete(const AddressList &addressList);

	// locate and return the Person * from the list. if the names cannot
	// be found in the list, return nullptr.
	Person *Find(const char *fname, const char *lname) const;

	// removes all items from the list.
	// the ctor should call this method and not duplicate code.
	void Clear(void);

	// Step through the entire list and display each item from the list.
	// By default, the list is displayed in alpha order. If the forward parameter
	// is set to false, the list is printed in reverse order.
	void Display(bool forward = true) const;

	// Returns the length of the list.
	// You should have this cached in the m_length data member.
	size_t Length(void) const;

	// Allow iteration through the list of addresses. If this has never been
	// called, return the first item.
	// A call to Next()/NextR() does not allocate a new Person, it only returns the
	// exising pointer.
	Person *Next(void);
	Person *NextR(void);

	void LoadFile(const char * fileName = ADDRESS_FILE);
	void AddFile(const char * fileName);
	void SaveFile(const char * fileName = ADDRESS_FILE) const;

private:
	// A private function that places the new item at the beginning of the list.
	// this is a private method that can only be called from within the class,
	// such as from the Insert() method.
	void prepend(const char *fname, const char *lname, const char *email,
		const char *street, const char *city, const char *state, const char *zip);

	Node *m_head;
	Node *m_tail;

	// This holds the current length of the list.
	size_t m_length;

	// this is what you can use to keep track of what is the next item from
	// the AddressList to return from a call to Next/NextR. If it is set to nullptr,
	// such as during a ctor, it should return the first/last item in the list.
	//
	// Thereafter, it should move its way through the list.
	//
	// Any changes to the list, additions or deletions, should reset these back
	// to nullptr.
	Node *m_next;
	Node *m_nextR;
};

#endif // ADDRESSLIST_H
