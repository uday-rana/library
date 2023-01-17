#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;
#include "Publication.h"
#include "Utils.h"
namespace sdds
{
	//special
	Publication::Publication()
	{
		reset();
	}

	Publication::Publication(const Publication& src)
	{
		*this = src;
	}

	Publication& Publication::operator=(const Publication& src)
	{
		if(this != &src)
		{
			for(int i = 0; i < SDDS_SHELF_ID_LEN + 1; i++)
			{
				m_shelfId[i] = src.m_shelfId[i];
			}
			m_membership = src.m_membership;
			m_libRef = src.m_libRef;
			m_date = src.m_date;
			delete[] m_title;
			m_title = nullptr;
			if(src.m_title != nullptr)
			{
			Utils::alloCopy(m_title, src.m_title);
			}
		}
		return *this;
	}

	Publication::~Publication()
	{
		delete[] m_title;
	}

	//modifiers
	void Publication::set(int member_id)
	{
		if(member_id >= 10000 && member_id <= 99999)
		{
			m_membership = member_id;
		}
		else
		{
			m_membership = 0;
		}
	}

	void Publication::setRef(int value)
	{
		m_libRef = value;
	}

	void Publication::resetDate()
	{
		m_date.reset();
	}

	void Publication::reset()
	{
		delete[] m_title;
		m_title = nullptr;
		for(int i = 0; i < SDDS_SHELF_ID_LEN; i++)
		{
			m_shelfId[i] = '\0';
		}
		m_membership = 0;
		m_libRef = -1;
		resetDate();
	}

	//queries
	char Publication::type() const
	{
		return 'P';
	}

	bool Publication::onLoan() const
	{
		return (m_membership != 0);
	}

	Date Publication::checkoutDate() const
	{
		return m_date;
	}

	ostream& Publication::fileDisplay(ostream& os) const
	{
		os << type() << "\t" << getRef() << "\t" << m_shelfId << "\t" << m_title << "\t" << m_membership << "\t" << checkoutDate();
		return os;
	}

	bool Publication::operator==(const char* title) const
	{
		bool matchFound{};

		if(title)
		{
			if(strstr(m_title, title))
			{
				matchFound = true;
			}
		}
		return matchFound;
	}

	Publication::operator const char* () const
	{
		return m_title;
	}

	int Publication::getRef() const
	{
		return m_libRef;
	}

	//Streamable pure virtual functions implementations

	ostream& Publication::write(ostream& os = cout) const
	{
		if(m_title != nullptr)
		{
			if(conIO(os))
			{
				os << "| " << m_shelfId << " | ";
				if(m_title)
				{
					Utils::prnInWidth(SDDS_TITLE_WIDTH, m_title, '.', os);
				}
				os << " | ";
				if(onLoan())
				{
					os << m_membership;
				}
				else
				{
					os << " N/A ";
				}
				os << " | " << checkoutDate() << " |";
			}
			else
			{
				fileDisplay(os);
			}
		}
		return os;
	}

	istream& Publication::read(istream& istr)
	{
		char temp_title[255 + 1]{};
		char temp_shelfId[SDDS_SHELF_ID_LEN + 2]{};
		int temp_libRef = -1;
		int temp_membership{};
		Date temp_date{};

		reset();
		if(conIO(istr))
		{
			cout << "Shelf No: ";
			istr.get(temp_shelfId, SDDS_SHELF_ID_LEN + 2, '\n');
			if(strlen(temp_shelfId) != 4)
			{
				istr.setstate(ios::failbit);
				istr.ignore(2000, '\n');
			}
			cout << "Title: ";
			if(!istr.fail())
			{
				istr.ignore(2000, '\n');
				istr.getline(temp_title, 255, '\n');
			}
			cout << "Date: ";
			if(!istr.fail())
			{
				temp_date.read(istr);
			}
		}
		else
		{
			istr >> temp_libRef; //read libref
			istr.ignore(2000, '\t'); //skip tab
			istr.getline(temp_shelfId, SDDS_SHELF_ID_LEN + 2, '\t'); //read shelfid & skip tab
			istr.getline(temp_title, 255, '\t'); //read title & skip tab
			istr >> temp_membership; //read membership
			istr.ignore(2000, '\t'); //skip tab
			temp_date.read(istr); //read date
		}
		if(temp_date.errCode() != 0)
		{
			istr.setstate(ios::failbit);
		}
		if(!istr.fail())
		{
			Utils::alloCopy(m_title, temp_title);
			strcpy(m_shelfId, temp_shelfId);
			m_libRef = temp_libRef;
			m_membership = temp_membership;
			m_date = temp_date;
		}
		return istr;
	}

	bool Publication::conIO(ios& io) const
	{
		return (&io == &cin || &io == &cout);
	}

	Publication::operator bool() const
	{
		return (m_title != nullptr && m_title[0] != '\0' && m_shelfId[SDDS_SHELF_ID_LEN - 1] != '\0');
	}
}