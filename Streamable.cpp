using namespace std;
#include "Streamable.h"
namespace sdds
{
	std::ostream& operator<<(std::ostream& os, const Streamable& strObj)
	{
		strObj.write(os);
		return os;
	}

	std::istream& operator>>(std::istream& is, Streamable& strObj)
	{
		strObj.read(is);
		return is;
	}
}