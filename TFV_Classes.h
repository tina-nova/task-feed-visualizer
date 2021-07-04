#ifndef TFV_CLASSES_H
#define TFV_CLASSES_H



#include <iostream>
#include <QString>
#include <vector>
#include <string>
#include <QStringList>
#include <QWidget>
#include <QGridLayout>
#include <QTabWidget>

using std::string;
using std::vector;

class priority
{
	public:

		priority() : priorities {"ASAP","URGENT","HIGH","NORMAL/HIGH","NORMAL/MEDIUM","NORMAL/LOW","LOW"}{}

		void clear();
		string GetPriority();
		int GetPriorityIndex();
		void SetPriority(string priorityInput);
		void SetPriority(int inputIndex);

	private:

		int index;
		string priorities[7];

};

class item
{
	public:

		void SetName(string name);
		string GetName();
		void SetDescription(string newDescription);
		string GetDesc();
		void SetStatPrimary(string newStatPrim);
		string GetStatPrimary();
		void SetStatSec(string newStatSec);
		string GetStatSec();
		void SetPriority(priority newPriority);
		string ReadPriority();
		priority GetPriority();
		void ClearAll();
		void SetMTOD(bool newState);
		bool GetMTOD();
		string GetMTODAnswer();
		void PrintCurrentItem();
		bool operator<(item& i);
		void SetProject(string newProject);
		string GetProject();

	private:

		string fromName;
		string descr;
		string statusPrimary;
		string statusSecondary;
		priority currentPriority;
		bool movedToOtherDay;
		string project;

};

class tab
{
	public:

		QString GetFile();
		void SetFile(QString newFile);
		string GetName();
		void SetTabName(QString newFile);
		vector<item> items;
		bool operator<(const tab& t) const;

	private:

		QString matchingFile;
		string tabName;
};

class taskFeedFile
{
	public:

		vector<tab> GetTabsVector();
		void setTabsVector(vector<tab> inputtedTabsVector);
		QStringList GetFileLocations();
		void setFileLocations(QStringList inputtedFileLocations);
		bool emptyTabs();

	private:

		vector<tab> tabsVector;
		QStringList fileLocations;
};

#endif // TFV_CLASSES_H
