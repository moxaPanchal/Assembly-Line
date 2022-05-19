

#include<iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include"Station.h"
#include "LineManager.h"
#include "Utilities.h"

using namespace std;


namespace sdds
{


	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		try
		{

			fstream fileOpen(file);
			string str1,str2 ,str3;
			size_t pos= 0 ;
			Utilities util;
			bool check = false;
			
			m_cntCustomerOrder = pending.size();

			while (getline(fileOpen, str1))
			{
				str2 = util.extractToken(str1, pos, check);

				if (check)
				{

					str3 = util.extractToken(str1, pos, check);

				}
				else
				{

					str3 = "";

				}

				for_each(stations.begin(), stations.end(), [&](Workstation* w1)
					{
					
						if (w1->getItemName() == str2)
						{
						
							for_each(stations.begin(), stations.end(), [&](Workstation* w2)
								{
								
									if (w2->getItemName() == str3)
									{
							
										w1->setNextStation(w2);
									
									}
								
								});
					
							activeLine.push_back(w1);
						}
			
					});

				m_firstStation = activeLine.front();
			
			}

			fileOpen.clear();
			fileOpen.seekg(0,ios::beg);

			fileOpen.close();

		}
		catch (...)
		{

			cerr << "An Error Occurred!!";
		
		}
	
	}


	void LineManager::linkStations()
	{
		vector<Workstation*> v_stat;
		Workstation* v_currStation;
		v_currStation = m_firstStation;

		while (v_currStation != nullptr)
		{

			v_stat.push_back(v_currStation);
			v_currStation = v_currStation->getNextStation();

		}

		activeLine = v_stat;
	}


	bool LineManager::run(std::ostream& os)
	{
		static size_t currentIteration = 1;
		bool check = false;

		size_t orders1, orders2;
		orders1 = completed.size() + incomplete.size();

		os << "Line Manager Iteration: " << currentIteration << endl;

		if (!pending.empty())
		{

			*m_firstStation += std::move(pending.front());
			pending.pop_front();
		
		}

		for_each(activeLine.begin(), activeLine.end(), [&](Workstation* w)
			{

				w->fill(os);

			});

		for_each(activeLine.begin(), activeLine.end(), [&](Workstation* w)
			{

				w->attemptToMoveOrder();

			});

		orders2 = completed.size() + incomplete.size();

		m_cntCustomerOrder -= (orders2 - orders1);

		if (m_cntCustomerOrder <= 0)
		{

			check = true;

		}

		currentIteration++;


		return check;

	}


	void LineManager::display(std::ostream& os) const
	{
		size_t i = 0;

		for (i = 0; i < activeLine.size(); i++)
		{

			activeLine[i]->display(os);

		}
	}

}


