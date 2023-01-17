#ifndef SDDS_UTILS_H__
#define SDDS_UTILS_H__
#include <iostream>
namespace sdds
{
	const unsigned int ReadBufferSize = 10;
	class Utils
	{
	public:
		static void read(int& val, int min, int max, const char* errorMessage = "");
		static void read(char* str, int len, const char* errorMessage = nullptr, char delimeter = '\n', std::istream& is = std::cin);
		static char* read(char delimiter = '\n', std::istream& is = std::cin);
		static void prnInWidth(int width, const char* value, char fillChar = ' ', std::ostream& os = std::cout);
		static void convertToVisibleASSCI(const char* filename);
		static void alloCopy(char*& des, const char* value);
	};
}
#endif // !
