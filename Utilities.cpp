


#include <string>
#include "Utilities.h"

using namespace std;

namespace sdds
{

	char Utilities::m_delimiter = ' ';

	Utilities::Utilities()
	{

		m_widthField = 1;

	}

	void Utilities::setFieldWidth(size_t newWidth)
	{

		m_widthField = newWidth;
	
	}

	size_t Utilities::getFieldWidth() const
	{

		return m_widthField;

	}



	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		string tmp{};
		
		size_t curr_pos{};
		
		curr_pos= next_pos;
		next_pos = str.find(m_delimiter, curr_pos);

		if (next_pos == string::npos)
		{

			tmp = str.substr(curr_pos);
			if (tmp.length() > m_widthField)
			{

				m_widthField = tmp.length();

			}
			else
			{

				m_widthField = m_widthField;

			}

			more = false;
		
		}
		else if (curr_pos == next_pos)
		{

			more = false;

			throw "Error occurred";
			
		}
		else
		{

			tmp = str.substr(curr_pos, next_pos - curr_pos);
			if (tmp.length() > m_widthField)
			{

				m_widthField = tmp.length();

			}
			else
			{

				m_widthField = m_widthField;

			}

			more = true;
		
		}

		next_pos++;

		return tmp;
	}

	void Utilities::setDelimiter(char newDelimiter)
	{

		m_delimiter = newDelimiter;
	
	}

	char Utilities::getDelimiter()
	{

		return m_delimiter;
	
	}

};