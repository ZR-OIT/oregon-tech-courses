#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>

#ifndef OITSTRING_H
# define OITSTRING_H

class OitString
{
public:
	OitString(void);				// the default ctor
	OitString(const char *str);		// another ctor

	OitString(const OitString &os); // copy constructor

	~OitString(void);				// the dtor

	void set(const char *str);
	void set(const OitString &os);

	OitString & operator=(const char *str);
	OitString & operator=(const OitString &os);

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

	char *c_str(void) const;
private:
	// Use this to cache the length of m_str, so you don't
	// have to call strlen() each time.
	size_t m_length;

	char *m_str;
};

#endif // OITSTRING_H
