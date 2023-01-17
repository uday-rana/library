#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H
#include <iostream>
#include "Publication.h"
namespace sdds
{
	class Book:public Publication
	{
		char* m_authorName{};
	public:
		//special
		Book() = default;
		Book(const Book&);
		Book& operator=(const Book&);
		~Book();

		//modifiers
		virtual void set(int);								// Calls Publication::set() + Publication::resetDate()

		//queries
		virtual char type()const;							// Returns 'B'
		virtual std::ostream& fileDisplay(std::ostream&)const;	// Displays in tab format

		//streamable pure virtual functions implementations
		virtual std::ostream& write(std::ostream&)const;
		virtual std::istream& read(std::istream&);
		operator bool()const;								// Returns true if the author's name exists, is not empty, and the base class's operator bool() has returned true
	};
}
#endif // !SDDS_BOOK_H