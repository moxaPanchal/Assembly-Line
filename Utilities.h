

#ifndef SDDS_UTILITIES_H_
#define SDDS_UTILITIES_H_

#include <iostream>

namespace sdds
{
	class Utilities
	{

		std::size_t m_widthField;
		static char m_delimiter;

	public:
		Utilities();

		void setFieldWidth(std::size_t newWidth);
		size_t getFieldWidth() const;

		std::string extractToken(const std::string& str, std::size_t& next_pos, bool& more);

		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};

}
#endif