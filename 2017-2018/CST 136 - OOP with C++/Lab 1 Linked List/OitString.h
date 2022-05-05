#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <cctype>

#ifndef OITSTRING_H
# define OITSTRING_H

class OitString
{
public:
	// whereever possible, make use of an existing method.
	OitString(void);				// the default ctor
	OitString(const char ch);		// ctor with a single char
	OitString(const char *str);		// ctor with a cString

	OitString(const OitString &os); // copy constructor

	~OitString(void);				// the dtor

	// Change the internal CString to be a copy of the cString str.
	void set(const char *str);
	// Change the internal CString to be a copy of os.m_str.
	void set(const OitString &os);
	// Change the internal m_str to be a cString containing only ch.
	void set(const char ch);

	// The assignment operator.
	OitString & operator=(const OitString &os);
	OitString & operator=(const char ch);
	OitString & operator=(const char *str);

	// Return the length of m_str.
	// This does not include the null terminator.
	size_t length(void) const;

	// Append to the end of the OitString.
	void append(const char *str);
	void append(char ch);
	void append(const OitString &os);

	// Prepend to the (beginning of) OitString
	void prepend(const char *str);
	void prepend(char ch);
	void prepend(const OitString &os);

	// Return the internal m_str member variable.
	char *c_str(void) const;

	// Return the character at the given position.
	// If the position is outside the length of m_str, return '\0'
	char at(size_t pos) const;

	// Return a reference to a character at a given position. This can
	// be used as an l-value.
	// For now, assume the pos is a valid position witin m_str.
	char &at(size_t pos);

	// Change the case of the given character or the entire internal
	// cString.
	// these change the case of an individual character.
	void upper(size_t pos);
	void lower(size_t pos);
	// these change the case of the entire string.
	void upper(void);
	void lower(void);

	// Reverse the internal cString.
	void reverse(void);

	// These should behave like the strcmp() fucntions.
	int compare(const char *str) const;
	int compare(const OitString &os) const;

	// Return true if the length of the internal cString == 0
	bool isEmpty(void) const;

	// Locate the cString/character within the cString internal
	// structure. You can make use of existing cString functions.
	char *find(const char ch) const;
	char *find(const char *str) const;
	// Find a character, from the end of the string.
	char *findR(const char ch) const;

	// Exchange the internal cStrings m_str's between the 2 objects.
	// You should not need to allocate any additional space to
	// complete this method.
	void swap(OitString &os);

private:
	// Use this to cache the length of m_str, so you don't
	// have to call strlen() each time.
	size_t m_length;

	char *m_str;
};

#endif // OITSTRING_H
