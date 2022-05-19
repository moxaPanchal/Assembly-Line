

#include<iostream>
#include <iomanip>
#include <algorithm>
#include "Utilities.h"
#include "CustomerOrder.h"

using namespace std;

namespace sdds
{


	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder()
	{
		m_cntItem = 0;
	}

	CustomerOrder::CustomerOrder(const std::string& str)
	{
		bool locate = true;
		size_t pos = 0;
		size_t i = 0;
		Utilities util;
		char storeDelimeter;

		try
		{

			m_name = util.extractToken(str, pos, locate);
			m_product = util.extractToken(str, pos, locate);
			storeDelimeter = util.getDelimiter();
			m_cntItem = std::count(str.begin(), str.end(), storeDelimeter) - 1;
			m_lstItem = new Item * [m_cntItem];

			for (i = 0; i < m_cntItem; i++)
			{

				m_lstItem[i] = new Item(util.extractToken(str, pos, locate));

			}


			if (util.getFieldWidth() > m_widthField)
			{

				m_widthField = util.getFieldWidth();

			}
			else
			{

				m_widthField = m_widthField;

			}

		}
		catch (std::string& message)
		{

			std::cout << message;

		}

	};

	CustomerOrder::CustomerOrder(const CustomerOrder& co)
	{
		throw string("CustomerOrder object not allowed to perform copy operations!");
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& co) noexcept
	{
		*this = std::move(co);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& co) noexcept
	{
		if (this != &co)
		{
			size_t i = 0;

			if (m_lstItem != nullptr)
			{

				for (i = 0; i < m_cntItem; i++)
				{

					delete m_lstItem[i];

				}

			}

			delete[] m_lstItem;

			m_lstItem = co.m_lstItem;
			co.m_lstItem = nullptr;
			m_name = co.m_name;
			co.m_name = "";
			m_cntItem = co.m_cntItem;
			co.m_cntItem = 0;
			m_product = co.m_product;
			co.m_product = "";

		}

		return *this;
	}


	bool CustomerOrder::isFilled() const
	{
		bool itemFill = true;
		size_t i = 0;

		for (i = 0; i < m_cntItem; i++)
		{

			if (!m_lstItem[i]->m_isFilled)
			{
				itemFill = false;
			}

		}

		return itemFill;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool itemFill = true;
		size_t i = 0;

		for (i = 0; i < m_cntItem; i++)
		{

			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled)
			{

				itemFill = false;

			}

		}

		return itemFill;

	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		size_t i = 0;

		for (i = 0; i < m_cntItem; i++)
		{

			if (m_lstItem[i]->m_itemName == station.getItemName())
			{
				if (station.getQuantity() >= 1)
				{
					station.updateQuantity();
					m_lstItem[i]->m_isFilled = true;
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();

					os.setf(ios::right);
					os.fill(' ');
					os.width(11);
					os << "Filled ";
					os << m_name << ", " << m_product;
					os << " [" << m_lstItem[i]->m_itemName << "]" << endl;
					os.unsetf(ios::right);

				}
				else
				{

					os.setf(ios::right);
					os.fill(' ');
					os.width(11);
					os << "    Unable to fill ";
					os << m_name << ", " << m_product;
					os << " [" << m_lstItem[i]->m_itemName << "]" << endl;
					os.unsetf(ios::right);

				}
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		size_t i = 0;

		os << m_name << " - ";
		os << m_product << std::endl;

		for (i = 0; i < m_cntItem; i++)
		{

			os << "[" << std::setw(6) << right << std::setfill('0') << m_lstItem[i]->m_serialNumber;
			os << "] " << std::setw(m_widthField) << left << std::setfill(' ');
			os << m_lstItem[i]->m_itemName << " - ";

			if (!m_lstItem[i]->m_isFilled)
			{

				os << "TO BE FILLED" << std::endl;

			}
			else
			{
				os << "FILLED" << std::endl;

			}

		}

	}


	CustomerOrder::~CustomerOrder()
	{
		size_t i = 0;

		for (i = 0; i < m_cntItem; i++)
		{

			delete m_lstItem[i];

		}

		delete[] m_lstItem;
		m_lstItem = nullptr;
	}

};