#include "TFV_DateOrder.h"
#include "logger.h"

#include <QTabWidget>

using std::pair;
QTabWidget* DateOrder::sortByDate(vector<pair<QString,QWidget*>> tabs, QTabWidget* tabList)
{
	std::cout << "Sorting tabs by date..." << std::endl;
	DateOrder dateOrder;
	vector<pair<int,pair<QString,QWidget*>>> tabsWithMonthIndex;
	vector<int> listOfMonths;
	std::cout << "Assigning month indexes to each tab..." << std::endl;
	for (auto& tab : tabs) {
		logger::log(tab.first.toLower().toStdString());
		for (auto& month : dateOrder.months){
			//logger::log("month " + month.second.toStdString() + " cross referenced with " + tab.first.toStdString());
			if (tab.first.contains(month.second,Qt::CaseInsensitive)){
				tabsWithMonthIndex.push_back(std::make_pair(month.first,tab));
				logger::log("Adding a " + month.second.toStdString() + " tab to the list...");
				if (std::find(listOfMonths.begin(),listOfMonths.end(),month.first) == listOfMonths.end()) {
					listOfMonths.push_back(month.first);
				}
				break;
			}
		}
	}
	vector<pair<int,pair<QString,QWidget*>>> sortedMonthedTabs;
	logger::log("Positioning each tab by its month index...");
	for (auto& tab : tabsWithMonthIndex){
		if (sortedMonthedTabs.empty()){
			logger::log("sorted months is empty");
			sortedMonthedTabs.push_back(tab);
		}
		else {
			logger::log("sorted months is NOT empty");
			int frontFirst = sortedMonthedTabs.front().first;
			if (tab.first >= frontFirst){
				int position = -1;
				bool properPosition = false;
				while (properPosition == false){
					int currentPositionValue = sortedMonthedTabs[position].first;
					logger::log("comparing currentpositionValue " + std::to_string(currentPositionValue) + " to tab value " + std::to_string(tab.first));
					if (!(tab.first >= currentPositionValue))
						properPosition = true;
					else {
						position++;
						logger::log(std::to_string(position));
					}
				}
				logger::log("emplacing " + std::to_string(tab.first) + " to position " + std::to_string(position));
				sortedMonthedTabs.emplace(sortedMonthedTabs.begin()+position,std::make_pair(tab.first,tab.second));
			} else {
				logger::log("else");
				sortedMonthedTabs.emplace(sortedMonthedTabs.begin(),tab);
			}
		}
	}
	logger::log("Converting QWidget to tabs...");
	for (auto& tab : sortedMonthedTabs){
		logger::log("converting " + tab.second.first.toStdString() + "...");
		tabList->addTab(tab.second.second,tab.second.first);
	}
	logger::log("All done with DateOrder!");
	return tabList;
}
