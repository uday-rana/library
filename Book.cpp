#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;
#include "Book.h"
#include "Utils.h"
namespace sdds
{
	Book::Book(const Book& src)
	{
		*this = src;
	}
	Book& Book::operator=(const Book& src)
	{
		Publication::operator=(src);
		if(this != &src)
		{
			delete[] m_authorName;
			m_authorName = nullptr;
			if(src.m_authorName != nullptr)
			{
				Utils::alloCopy(m_authorName, src.m_authorName);
			}
		}
		return *this;
	}

	Book::~Book()
	{
		delete[] m_authorName;
	}

	void Book::set(int member_id)
	{
		Publication::set(member_id);
		Publication::resetDate();
	}

	char Book::type() const
	{
		return 'B';
	}

	std::ostream& Book::fileDisplay(std::ostream& os) const
	{
		Publication::fileDisplay(os);
		os << '\t' << m_authorName;
		return os;
	}

	Book::operator bool() const
	{
		return (m_authorName != nullptr && m_authorName[0] != '\0' && Publication::operator bool());
	}

	std::ostream& Book::write(std::ostream& os) const
	{
		Publication::write(os);
		if(m_authorName != nullptr)
		{
			if(conIO(os))
			{
				os << " ";
				Utils::prnInWidth(SDDS_AUTHOR_WIDTH, m_authorName, ' ', os);
				os << " |";
			}
			else
			{
				fileDisplay(os);
			}
		}
		return os;
	}

	std::istream& Book::read(std::istream& is)
	{
		char temp_authorName[256]{};

		Publication::read(is);
		delete[] m_authorName;
		m_authorName = nullptr;
		if(conIO(is))
		{
			is.ignore();
			cout << "Author: ";
			is.get(temp_authorName, 256);
			is.ignore();
		}
		else
		{
			is.ignore();
			is.get(temp_authorName, 256);
		}

		if(!is.fail())
		{
			Utils::alloCopy(m_authorName, temp_authorName);
		}
		return is;
	}
}