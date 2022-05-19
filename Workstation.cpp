

#include<iostream>
#include"Workstation.h"

using namespace std;


std::deque<sdds::CustomerOrder> pending{};
std::deque<sdds::CustomerOrder> completed{};
std::deque<sdds::CustomerOrder> incomplete{};

namespace sdds
{

	Workstation::Workstation(const std::string& conStr) :Station(conStr)
	{
		m_pNextStation = nullptr;
	}

	void Workstation::fill(std::ostream& os)
	{

		if (!m_orders.empty())
		{

			m_orders.front().fillItem(*this, os);

		}

	}

	bool Workstation::attemptToMoveOrder()
	{
		bool check = false;

		if (!m_orders.empty() && (m_orders.front().isItemFilled(getItemName()) || getQuantity() <= 0))
		{

			if (m_pNextStation != nullptr)
			{

				*m_pNextStation += std::move(m_orders.front());
				m_orders.pop_front();
				check = true;
			
			}
			else if (m_orders.front().isFilled())
			{

				completed.push_back(std::move(m_orders.front()));
				m_orders.pop_front();
				check = true;
			
			}
			else
			{

				incomplete.push_back(std::move(m_orders.front()));
				m_orders.pop_front();
				check = true;

			}

		}

		return check;

	}


	void Workstation::setNextStation(Workstation* station)
	{

		m_pNextStation = station;

	}

	Workstation* Workstation::getNextStation() const
	{

		return m_pNextStation;

	}

	void Workstation::display(std::ostream& os) const
	{
		os << getItemName() << " --> ";

		if (m_pNextStation == nullptr)
		{

			os << "End of Line";

		}
		else
		{

			os << m_pNextStation->getItemName();

		}

		os << endl;
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{

		m_orders.push_back(std::move(newOrder));
		return *this;

	}


}

