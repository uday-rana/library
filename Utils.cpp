#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#include "Utils.h"
namespace sdds
{
	void Utils::read(int& val, int min, int max, const char* ErrorMess)
	{
		bool ok{};
		char newline{};
		do
		{
			cin >> val;
			newline = cin.get();
			if(cin.fail() || newline != '\n')
			{
				ok = false;
				cin.clear();
				cin.ignore(1000, '\n');
			}
			else
			{
				ok = val <= max && val >= min;
			}
		}
		while(!ok && cout << ErrorMess);
	}

	void Utils::read(char* str, int len, const char* errorMessage, char delim, std::istream& is)
	{
		bool ok{};
		do
		{
			ok = true;
			is.getline(str, len + 1, '\n');
			if(is.fail())
			{
				is.clear();
				is.ignore(1000, '\n');
				ok = false;
			}
		}
		while(!ok && (!errorMessage || cout << errorMessage));
	}
	char* Utils::read(char delimiter, istream& is)
	{
		char* data = new char[ReadBufferSize];
		char* toRet{};
		char* str = data;
		int noOfBuffers = 1;
		bool done{};
		do
		{
			done = true;
			is.getline(str, ReadBufferSize, delimiter);
			if(is.fail())
			{
				noOfBuffers++;
				char* temp = new char[(ReadBufferSize - 1) * noOfBuffers + 1];
				strcpy(temp, data);
				delete[] data;
				data = temp;
				str = data + (ReadBufferSize - 1) * (noOfBuffers - 1);
				is.clear();
				done = false;
			}
		}
		while(!done);
		toRet = new char[strlen(data) + 1];
		strcpy(toRet, data);
		delete[] data;
		return toRet;
	}
	void Utils::prnInWidth(int width, const char* value, char fillChar, ostream& os)
	{
		if(strlen(value) > (size_t)width)
		{
			for(int i = 0; i < width; os << value[i++]);
		}
		else
		{
			os.width(width);
			os.fill(fillChar);
			os.setf(ios::left);
			os << value;
			os.unsetf(ios::left);
		}
	}
	void Utils::convertToVisibleASSCI(const char* filename)
	{
		ifstream fin(filename);
		ofstream temp("sdds_temp.txt");
		char ch;
		int tab{}, newline{}, ret{}, non{}, ascii{};
		while(fin)
		{
			ch = fin.get();
			if(ch == '\t' || ch == '\n' || ch == '\r' || (ch >= 32 && ch <= 126))
			{
				tab += (ch == '\t');
				newline += (ch == '\n');
				ret += (ch == '\r');
				ascii += ((ch >= 32 && ch <= 126));
				temp << ch;
			}
			else
			{
				non++;
			}
			cout << "tab: " << tab << ", newline: " << newline << ", return: " << ret << ", ascii: " << ascii << " non: " << non << "                           \r";
		}
		fin.close();
		temp.close();
	}
	void Utils::alloCopy(char*& des, const char* value)
	{
		delete[] des;
		des = nullptr;
		if(value)
		{
			des = new char[strlen(value) + 1]{};
			strcpy(des, value);
		}
	}
}