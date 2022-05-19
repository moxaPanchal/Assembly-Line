

#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H

#include<iostream>
#include<string>
#include"Station.h"

namespace sdds
{

	class CustomerOrder
	{

		struct Item
		{
			std::string m_itemName;
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };

			Item(const std::string& src) : m_itemName(src)
			{
			};

		};

		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{0};
		Item** m_lstItem{};

		static size_t m_widthField;

	public:

		CustomerOrder();
		CustomerOrder(const std::string& str);

		CustomerOrder(const CustomerOrder& co);
		CustomerOrder& operator=(const CustomerOrder& co) = delete;

		CustomerOrder(CustomerOrder&& co) noexcept;
		CustomerOrder& operator=(CustomerOrder&& co)noexcept;

		bool isFilled() const;
		bool isItemFilled(const std::string& itemName) const;

		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;

		~CustomerOrder();
	
	};


}



#endif