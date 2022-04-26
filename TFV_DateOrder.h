#ifndef TFV_DATEORDER_H
#define TFV_DATEORDER_H

#include "TFV_PopulatingFunctions.h"

using std::pair;
using std::map;

class DateOrder
{

	private:

		std::map<int,QString> months = {
			pair(1,"january"),
			pair(2,"february"),
			pair(3,"march"),
			pair(4,"april"),
			pair(5,"may"),
			pair(6,"june"),
			pair(7,"july"),
			pair(8,"august"),
			pair(9,"september"),
			pair(10,"october"),
			pair(11,"november"),
			pair(12,"december")
		};



	public:
		static QTabWidget* sortByDate(std::vector<pair<QString, QWidget*>> tabs, QTabWidget* tabList);


};

#endif // TFV_DATEORDER_H


