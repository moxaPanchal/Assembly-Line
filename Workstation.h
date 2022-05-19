

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include<iostream>
#include<deque>
#include"CustomerOrder.h"
#include"Station.h"


extern std::deque<sdds::CustomerOrder> pending;
extern std::deque<sdds::CustomerOrder> completed;
extern std::deque<sdds::CustomerOrder> incomplete;


namespace sdds
{

	class Workstation :public Station
	{

		std::deque<sdds::CustomerOrder> m_orders{};
		Workstation* m_pNextStation{};

	public:

		Workstation(const std::string& conStr);
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station = nullptr);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
	};

};



#endif


