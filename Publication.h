#ifndef SDDS_PUBLICATION_H
#define SDDS_PUBLICATION_H
#include <iostream>
#include "Lib.h"
#include "Streamable.h"
#include "Date.h"
namespace sdds
{
	class Publication:public Streamable
	{
		char* m_title{};
		char m_shelfId[SDDS_SHELF_ID_LEN + 1]{};
		int m_membership{};
		int m_libRef{};
		Date m_date{};
	public:
		//special
		Publication();
		Publication(const Publication&);
		Publication& operator=(const Publication&);
		~Publication();

		//modifiers
		virtual void set(int);								// Sets the membership attribute to either zero or a five-digit integer
		void setRef(int);									// Sets the libRef attribute value
		void resetDate();									// Sets the date to the current date of the system
		void reset();										// Sets attributes to default

		//queries
		operator const char* ()const;						// Returns the title attribute
		virtual char type()const;							// Returns the character 'P' to identify this object as a "Publication object"
		bool onLoan()const;									// Returns true if the publication is checkout (membership is non-zero)
		bool operator==(const char*)const;					// Returns true if the argument appears anywhere in the title of the publication
		int getRef()const;									// Returns the libRef attribute
		Date checkoutDate()const;							// Returns the date attribute
		virtual std::ostream& fileDisplay(std::ostream& = std::cout)const;	// Displays in tab format

		//streamable pure virtual functions implementations
		virtual std::ostream& write(std::ostream&)const;
		virtual std::istream& read(std::istream&);
		bool conIO(std::ios&)const;
		operator bool()const;								// Returns true if neither of the title or shelfId attributes is null or empty
	};
}
#endif // !SDDS_PUBLICATION_H
