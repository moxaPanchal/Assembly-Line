

#include <string>
#include <algorithm>
#include "Utilities.h"
#include "Station.h"

using namespace std;

namespace sdds
{
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 1;


	Station::Station()
	{

		id_station = 0;
		m_serialNumber = 0;
		quantityStock = 0;

	}


	const std::string& Station::getItemName() const
	{

		return stat_name;

	}

	unsigned int Station::getNextSerialNumber()
	{

		m_serialNumber++;

		return m_serialNumber - 1;

	}

	unsigned int Station::getQuantity() const
	{

		return quantityStock;

	}

	void Station::updateQuantity()
	{

		quantityStock = quantityStock - 1;

		if (quantityStock < 0)
		{

			quantityStock = 0;

		}
	}

	Station::Station(const std::string& s1)
	{

		Utilities util;
		size_t pos = 0;
		bool check = true;
		id_station = id_generator++;


			stat_name = util.extractToken(s1, pos, check);

			m_serialNumber = stoi(util.extractToken(s1, pos, check));

			quantityStock = stoi(util.extractToken(s1, pos, check));

			if (util.getFieldWidth() > m_widthField)
			{

				m_widthField = util.getFieldWidth();

			}
			else
			{

				m_widthField = m_widthField;

			}

			stat_desc = util.extractToken(s1, pos, check);
	}


	void Station::display(std::ostream& os, bool full) const
	{
		if (full == true)
		{
			os.setf(ios::right);
			os << "[";
			os.fill('0');
			os.width(3);
			os << id_station;
			os << "]";
			os << " Item: ";
			os.width(m_widthField);
			os.unsetf(ios::right);

			os.setf(ios::left);
			os.fill(' ');
			os << stat_name;
			os << " [";
			os.width(6);
			os.unsetf(ios::left);

			os.setf(ios::right);
			os.fill('0');
			os << m_serialNumber;
			os << "]";
			os << " Quantity: ";
			os.width(m_widthField);
			os.unsetf(ios::right);

			os.setf(ios::left);
			os.fill(' ');
			os << quantityStock;
			os << " Description: ";
			os << stat_desc;
			os << endl;
			os.unsetf(ios::left
			);
		}
		else
		{
			os.setf(ios::right);
			os << "[";
			os.fill('0');
			os.width(3);
			os << id_station;
			os << "]";
			os << " Item: ";
			os.width(m_widthField);
			os.unsetf(ios::right);

			os.setf(ios::left);
			os.fill(' ');
			os << stat_name;
			os << " [";
			os.width(6);
			os.unsetf(ios::left);
			os.setf(ios::right);
			os.fill('0');
			os << m_serialNumber;
			os << "]";
			os << endl;
			os.unsetf(ios::right);
		}

	}
}

