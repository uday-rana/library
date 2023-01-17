#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <cstring>
using namespace std;
#include "Book.h"
#include "LibApp.h"
#include "PublicationSelector.h"
#include "Utils.h"
namespace sdds
{
	//LibApp:
	//private
	bool LibApp::confirm(const char* message)
	{
		Menu messageMenu(message);
		messageMenu << "Yes";
		return (~messageMenu == 1);
	}

	void LibApp::load()
	{
		ifstream infile(m_filename);
		char type{};

		cout << "Loading Data" << endl;
		while(infile)
		{
			infile >> type;
			infile.ignore();
			if(infile)
			{
				if(type == 'P')
				{
					m_publications[m_noOfPublications] = new Publication;
				}
				else if(type == 'B')
				{
					m_publications[m_noOfPublications] = new Book;
				}
				if(m_publications[m_noOfPublications])
				{
					infile >> *m_publications[m_noOfPublications];
					m_noOfPublications++;
				}
			}
			if(m_noOfPublications > 0)
			{
				if(m_publications[m_noOfPublications - 1] != nullptr)
				{
					m_lastref = m_publications[m_noOfPublications - 1]->getRef();
				}
			}
		}
	}

	void LibApp::save()
	{
		ofstream outfile(m_filename);

		cout << "Saving Data" << endl;
		for(int i = 0; i < m_noOfPublications; i++)
		{
			if(m_publications[i]->getRef())
			{
				outfile << *m_publications[i] << endl;
			}
		}
	}

	int LibApp::search(int searchType = 0)
	{
		int selection{};
		int foundLibRef{};
		char publicationType{};
		char searchTitle[256]{};
		bool matchFound{};
		bool quit{};
		PublicationSelector ps("Select one of the following found matches:");

		selection = ~m_typeMenu;
		if(selection == 0)
		{
			quit = true;
		}
		else if(selection == 1)
		{
			publicationType = 'B';
		}
		else if(selection == 2)
		{
			publicationType = 'P';
		}
		if(!quit)
		{
			cout << "Publication Title: ";
			cin.getline(searchTitle, 256);
			if(searchType == 0)
			{
				for(int i = 0; i < m_noOfPublications; i++)
				{
					if(m_publications[i]->getRef() && m_publications[i]->type() == publicationType && *m_publications[i] == searchTitle)
					{
						ps << m_publications[i];
						matchFound = true;
					}
				}
			}
			else if(searchType == 1)
			{
				for(int i = 0; i < m_noOfPublications; i++)
				{
					if(m_publications[i]->getRef() && m_publications[i]->type() == publicationType && *m_publications[i] == searchTitle && m_publications[i]->onLoan())
					{
						ps << m_publications[i];
						matchFound = true;
					}
				}
			}
			else if(searchType == 2)
			{
				for(int i = 0; i < m_noOfPublications; i++)
				{
					if(m_publications[i]->getRef() && m_publications[i]->type() == publicationType && *m_publications[i] == searchTitle && !(m_publications[i]->onLoan()))
					{
						ps << m_publications[i];
						matchFound = true;
					}
				}
			}
			if(matchFound)
			{
				ps.sort();
				foundLibRef = ps.run();
				if(foundLibRef == 0)
				{
					quit = true;
				}
			}
			else
			{
				cout << "No matches found!" << endl;
			}
		}
		if(quit)
		{
			cout << "Aborted!" << endl;
		}
		return foundLibRef;
	}

	void LibApp::newPublication()
	{
		bool quit{};
		int selection{};
		Publication* newPub{};

		if(m_noOfPublications == SDDS_LIBRARY_CAPACITY)
		{
			cout << "Library is at its maximum capacity!" << endl;
		}
		else
		{
			cout << "Adding new publication to the library" << endl;
			selection = ~m_typeMenu;
			if(selection == 0)
			{
				quit = true;
			}
			else if(selection == 1)
			{
				newPub = new Book();
			}
			else if(selection == 2)
			{
				newPub = new Publication();
			}
			if(!quit)
			{
				cin >> *newPub;
				if(!cin.fail())
				{
					if(confirm("Add this publication to the library?"))
					{
						if(*newPub)
						{
							newPub->setRef(++m_lastref);
							m_publications[m_noOfPublications++] = newPub;
							m_changed = true;
							cout << "Publication added" << endl;
						}
						else
						{
							cout << "Failed to add publication!";
							delete newPub;
							newPub = nullptr;
						}
					}
					else
					{
						cout << "Aborted!" << endl;
					}
				}
			}
			else
			{
				cout << "Aborted!" << endl;
			}
		}
		cout << endl;
	}

	void LibApp::removePublication()
	{
		int foundLibRef{};

		cout << "Removing publication from the library" << endl;
		foundLibRef = search();
		if(foundLibRef)
		{
			cout << *getPub(foundLibRef) << endl;
			if(confirm("Remove this publication from the library?"))
			{
				getPub(foundLibRef)->setRef(0);
				m_changed = true;
				cout << "Publication removed" << endl;
			}
		}
		cout << endl;
	}

	void LibApp::checkOutPub()
	{
		int foundLibRef{};
		int temp_membership{};

		cout << "Checkout publication from the library" << endl;
		foundLibRef = search(2);
		if(foundLibRef)
		{
			cout << *getPub(foundLibRef) << endl;
			if(confirm("Check out publication?"))
			{
				cout << "Enter Membership number: ";
				Utils::read(temp_membership, 10000, 99999, "Invalid membership number, try again: ");
				getPub(foundLibRef)->set(temp_membership);
				m_changed = true;
				cout << "Publication checked out" << endl;
			}
		}
		cout << endl;
	}

	void LibApp::returnPub()
	{
		int foundLibRef{};
		int dateDiff{};
		double lateFees{};
		Date today{};

		cout << "Return publication to the library" << endl;
		foundLibRef = search(1);
		if(foundLibRef)
		{
			cout << *getPub(foundLibRef) << endl;
			if(confirm("Return Publication?"))
			{
				dateDiff = today - getPub(foundLibRef)->checkoutDate();
				if(dateDiff > 15)
				{
					lateFees = 0.50 * (dateDiff - 15);
					cout << "Please pay $";
					cout.setf(ios::fixed);
					cout.precision(2);
					cout << lateFees;
					cout.precision(6);
					cout.unsetf(ios::fixed);
					cout << " penalty for being " << (dateDiff - 15) << " days late!" << endl;
				}
				getPub(foundLibRef)->set(0);
				m_changed = true;
				cout << "Publication returned" << endl;
			}
		}
		cout << endl;
	}

	//public
	LibApp::LibApp(const char* filename = "")
	{
		strcpy(m_filename, filename);
		m_typeMenu.setTitle("Choose the type of publication:");
		m_typeMenu << "Book" << "Publication";
		m_mainMenu.setTitle("Seneca Library Application");
		m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
		m_exitMenu.setTitle("Changes have been made to the data, what would you like to do?");
		m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
		load();
	}

	LibApp::~LibApp()
	{
		for(int i = 0; i < m_noOfPublications; i++)
		{
			delete m_publications[i];
		}
	}

	Publication* LibApp::getPub(int libRef) const
	{
		int matchIndex{};

		for(int i = 0; i < m_noOfPublications; i++)
		{
			if(m_publications[i]->getRef() == libRef)
			{
				matchIndex = i;
			}
		}
		return m_publications[matchIndex];
	}

	void LibApp::run()
	{
		bool quit{};
		do
		{
			switch(~m_mainMenu)
			{
				case 1:
					newPublication();
					break;
				case 2:
					removePublication();
					break;
				case 3:
					checkOutPub();
					break;
				case 4:
					returnPub();
					break;
				default:
					if(m_changed)
					{
						switch(~m_exitMenu)
						{
							case 1:
								save();
								quit = true;
								break;
							case 2:
								cout << endl;
								break;
							default:
								if(confirm("This will discard all the changes are you sure?") == 1)
								{
									quit = true;
								}
								break;
						}
					}
					else
					{
						quit = true;
					}
					break;
			}
		}
		while(quit == false);
		cout << endl << "-------------------------------------------" << endl;
		cout << "Thanks for using Seneca Library Application" << endl;
		ifstream infile(m_filename);
		cout << infile.rdbuf();
	}
}