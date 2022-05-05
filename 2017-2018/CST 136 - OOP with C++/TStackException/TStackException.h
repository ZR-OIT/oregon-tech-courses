#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <exception>

using std::exception;
using std::cout;
using std::endl;
using std::ostream;

#ifndef TSTACKEXCEPTION_H
# define TSTACKEXCEPTION_H

class TStackException : public exception
{
public:
	TStackException(const char *fileName, const char *methodName, const char *message, int lineno = 0);
	~TStackException(void);
	const char * GetFileName(void) const;
	const char * GetMethodName(void) const;
	const char * GetMessage(void) const;
	const int GetLine(void) const;

	friend ostream& operator << (ostream& os, const TStackException &e);

private:
	char *m_fileName;
	char *m_methodName;

	int m_lineno;
};

#endif // TSTACKEXCEPTION_H
