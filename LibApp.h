#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include "Lib.h"
#include "Menu.h"
#include "Publication.h"
namespace sdds
{
	class LibApp
	{
		bool m_changed{};
		char m_filename[256]{};
		int m_noOfPublications{};									// no of loaded publications
		int m_lastref{};											// last library reference number
		Publication* m_publications[SDDS_LIBRARY_CAPACITY]{};		// publication pointer array
		Menu m_typeMenu{};
		Menu m_mainMenu{};
		Menu m_exitMenu{};
		bool confirm(const char*);
		void load();									// open the data file for reading and read all the publications in dynamic instances pointed by the PPA Array.
		void save();									// open the data file for overwriting and insert all elements into the ofstream object
		int search(int);								// 0 = search all, 1 = search checked out items, 2 = search available items
		void newPublication();
		void removePublication();
		void checkOutPub();
		void returnPub();
	public:
		//special
		LibApp(const char*); //constructor
		~LibApp();

		//query
		Publication* getPub(int)const;					//return the address of a Publication object in the PPA that has the library reference number matching the argument.

		void run();
	};
}
#endif // !SDDS_LIBAPP_H
