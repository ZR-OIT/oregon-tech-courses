#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <cctype>

#ifndef OITSTRING_H
# define OITSTRING_H

class OitString
{
public:
	OitString(void);				// the default ctor
	OitString(const char *str);		// another ctor

	OitString(const OitString &os); // copy constructor

	~OitString(void);				// the dtor

	// Change the internal CString to be a copy of the cString str.
	void set(const char *str);
	// Change the internal CString to be a copy of os.m_str.
	void set(const OitString &os);

	// The assignment operator.
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

	// Return the internal m_str member variable.
	char *c_str(void) const;

	// ***************************************************************
	// NEW METHODS 
	// ***************************************************************
	// Return the character at the given position.
	// If the position is outside the length of m_str, return '\0'
	char at(size_t pos) const;

	// Return a reference to a character at a given position. This can
	// be used as an l-value.
	// For now, assume the pos is a valid position witin m_str.
	// This one will be a challenge.
	char &at(size_t pos);

	// Change the case of the given character or the entire internal
	// cString.
	void upper(size_t pos);
	void lower(size_t pos);
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
	// structure.
	char *find(const char ch) const;
	char *find(const char *str) const;

	// Exchange the internal cStrings m_str's between the 2 objects.
	// You should not need to allocate any additional space to
	// complete this method.
	void swap(OitString &os);

	// This allows you loop through the pieces of the internal cString.
	// However, you should keep a copy of the original cString that
	// remains unmodified.
	// Notice that the call to tokenize() does not itself return
	// a token.
	//
	// NOTE  NOTE  NOTE  NOTE  NOTE  NOTE  NOTE  NOTE  NOTE  NOTE
	// **********************************************************
	// You will need to use strtok_s for this to work correctly.
	// **********************************************************
	//
	// This one will be a challenge.
	void tokenize(const char *delim = " \t\n");
	// Get the next token in the string.
	// If nextToken() is called before tokenize() is called, then
	// tokenize() is called with the default delimiters.
	char *nextToken(void);

private:
	// Use this to cache the length of m_str, so you don't
	// have to call strlen() each time.
	size_t m_length;

	char *m_str;

	char *m_delim;
	char *m_tokenizedStr;
	char *m_currToken;
	char *m_nextToken;

	// This is a private function I found useful when I wanted to
	// clean up all the token stuff. Use if if you like.
	void clearTokens(void);
};

#endif // OITSTRING_H
