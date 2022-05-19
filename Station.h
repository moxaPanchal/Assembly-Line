

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>

namespace sdds
{
	class Station
	{
		int id_station{};
		std::string stat_name{};
		std::string stat_desc{};
		unsigned int m_serialNumber{};
		unsigned int quantityStock{};
		static std::size_t m_widthField;
		static size_t id_generator;
	public:
		Station();
		Station(const std::string&);
		const std::string& getItemName() const;
		unsigned int getNextSerialNumber();
		unsigned int getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}
#endif