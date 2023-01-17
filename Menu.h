#ifndef SDDS_MENU_H
#define SDDS_MENU_H
#include <iostream>
namespace sdds
{
	const unsigned int MAX_MENU_ITEMS = 20;

	class Menu;

	class MenuItem
	{
		char* m_content{};												// dynamically allocated char array: holds title

		//special
		MenuItem();														// default constructor
		MenuItem(const char*);											// one argument constructor: sets title
		MenuItem(const MenuItem&) = delete;								// copy constructor deleted
		MenuItem& operator=(const MenuItem&) = delete;					// copy assignment operator deleted
		~MenuItem();													// destructor

		//queries
		void display()const;											// displays content
		operator bool()const;											// returns true if content is not empty
		operator const char* ()const;									// returns content

		//modifiers
		void set(const char*);											// sets content, called by one argument MenuItem constructor and one argument Menu constructor

		friend class Menu;
	};



	class Menu
	{
		MenuItem m_title{};
		MenuItem* m_menuItems[MAX_MENU_ITEMS]{};
		int m_numOfItems{};

	public:
		//special
		Menu();															// default constructor
		Menu(const char*);												// one argument constructor: sets title
		Menu(const Menu&) = delete;										// copy constructor deleted
		Menu& operator=(const Menu&) = delete;							// copy assignment operator deleted
		~Menu();

		//queries
		void displayTitle()const;										// displays title
		void display()const;											// displays menu
		operator int()const;											// returns m_numOfItems
		operator unsigned int()const;									// returns m_numOfItems
		operator bool()const;											// returns true if m_numOfItems != 0
		const char* operator[](int)const;								// return content of MenuItem at specified index in m_menuItems

		//modifiers
		void setTitle(const char*);										// sets title
		unsigned int run();												// display menu and ask for user selection
		unsigned int operator~();										// display menu and ask for user selection
		Menu& operator<<(const char*);									// add MenuItem to end of m_menuItems array, if space exists
	};
	//Free Helpers:
	std::ostream& operator<<(std::ostream& os, const Menu& toDisplay);	// displays title

	unsigned int selectMenuItem(const unsigned int min, const unsigned int max);
}

#endif // !SDDS_MENU_H
