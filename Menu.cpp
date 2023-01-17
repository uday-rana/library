#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;
#include "Menu.h"
#include "Utils.h"
namespace sdds
{
	// MenuItem:
	// Member functions:
	// special
	MenuItem::MenuItem()
	{
	}

	MenuItem::MenuItem(const char* content)
	{
		set(content);
	}

	MenuItem::~MenuItem()
	{
		delete[] m_content;
		m_content = nullptr;
	}


	// queries
	void MenuItem::display() const
	{
		if(*this)
		{
			cout << m_content;
		}
	}

	MenuItem::operator bool() const
	{
		return (m_content != nullptr);
	}

	MenuItem::operator const char* () const
	{
		return m_content;
	}

	// modifiers
	void MenuItem::set(const char* title)
	{
		unsigned length = strlen(title) + 1;
		m_content = new char[length]
		{};
		strcpy(m_content, title);
	}



	// Menu:
	// Member functions:
	// special
	Menu::Menu()
	{
		m_title.m_content = nullptr;
	}

	Menu::Menu(const char* title)
	{
		m_title.set(title);
	}

	Menu::~Menu()
	{
		for(int i = 0; i < m_numOfItems; i++)
		{
			delete m_menuItems[i];
			m_menuItems[i] = nullptr;
		}
	}

	// queries
	void Menu::displayTitle()const
	{
		m_title.display();
	}

	void Menu::display() const
	{
		displayTitle();
		if(m_title)
		{
			cout << endl;
		}
		for(int i = 0; i < m_numOfItems; i++)
		{
			cout.width(2);
			cout.setf(ios::right);
			cout << i + 1;
			cout.unsetf(ios::right);
			cout << "- ";
			m_menuItems[i]->display();
			cout << endl;
		}
		cout.width(2);
		cout.setf(ios::right);
		cout << "0";
		cout.unsetf(ios::right);
		cout << "- Exit" << endl << "> ";
	}

	Menu::operator int() const
	{
		return m_numOfItems;
	}

	Menu::operator unsigned int() const
	{
		return m_numOfItems;
	}

	Menu::operator bool() const
	{
		return m_numOfItems;
	}

	const char* Menu::operator[](int index)const
	{
		const char* toReturn{};
		if(index > -1 && index < m_numOfItems)
		{
			toReturn = (const char*)(*m_menuItems[index]);
		}
		else if(index > m_numOfItems)
		{
			if(index % m_numOfItems == 0)
			{
				toReturn = (const char*)m_menuItems[m_numOfItems - 1];
			}
			else
			{
				toReturn = (const char*)m_menuItems[(index % m_numOfItems) - 1];
			}
		}
		return toReturn;
	}

	void Menu::setTitle(const char* content)
	{
		m_title.set(content);
	}

	unsigned int Menu::run()
	{
		unsigned int selection{};

		display();
		selection = selectMenuItem(0, m_numOfItems);
		return selection;
	}

	unsigned int Menu::operator~()
	{
		return run();
	}

	Menu& Menu::operator<<(const char* menuitemContent)
	{
		if((unsigned int)m_numOfItems < MAX_MENU_ITEMS)
		{
			m_menuItems[m_numOfItems] = new MenuItem(menuitemContent);
			m_numOfItems++;
		}
		return *this;
	}

	std::ostream& operator<<(std::ostream& os, const Menu& toDisplay)
	{
		toDisplay.displayTitle();
		return os;
	}


	unsigned int selectMenuItem(const unsigned int min, const unsigned int max)
	{
		unsigned int selection{};
		bool fail{};
		do
		{
			fail = false;
			cin >> selection;
			if(selection < min || selection > max || cin.fail())
			{
				cin.clear();
				cin.ignore(10000, '\n');
				fail = true;
				cout << "Invalid Selection, try again: ";
			}
		}
		while(fail == true);
		cin.ignore(1000, '\n');
		return selection;
	}
}