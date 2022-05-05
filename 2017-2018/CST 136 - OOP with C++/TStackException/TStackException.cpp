#include "TStackException.h"

TStackException::TStackException(const char * fileName, const char * methodName, const char * message, int lineno)
	: exception(message), m_lineno(static_cast<int>(lineno))
{
	m_fileName = new char[strlen(fileName) + 1];
	m_methodName = new char[strlen(methodName) + 1];

	strcpy(m_fileName, fileName);
	strcpy(m_methodName, methodName);
}

TStackException::~TStackException(void)
{ 
	delete[] m_fileName;
	delete[] m_methodName;

	m_fileName = nullptr;
	m_methodName = nullptr;
}

const char * TStackException::GetFileName(void) const
{
	return m_fileName;
}

const char * TStackException::GetMethodName(void) const
{
	return m_methodName;
}

const char * TStackException::GetMessage(void) const
{
	return what();
}

const int TStackException::GetLine(void) const
{
	return m_lineno;
}

ostream & operator<<(ostream & os, const TStackException & e)
{
	os << e.GetFileName() << " " << e.GetMethodName() << ":" << e.GetLine() << " " << e.what() ;
	return os;
}
