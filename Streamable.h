#ifndef SDDS_STREAMABLE_H
#define SDDS_STREAMABLE_H
#include <iostream>
namespace sdds
{
	class Streamable
	{
	public:
		virtual std::ostream& write(std::ostream&)const = 0;
		virtual std::istream& read(std::istream&) = 0;
		virtual bool conIO(std::ios&)const = 0;
		virtual operator bool()const = 0;
		virtual ~Streamable()
		{
		};
	};
	std::ostream& operator<<(std::ostream&, const Streamable&);
	std::istream& operator>>(std::istream&, Streamable&);
}
#endif // !SDDS_STREAMABLE_H
