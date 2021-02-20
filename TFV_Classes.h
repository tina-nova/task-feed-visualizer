#include <iostream>
#include <QString>
#include <vector>
#include <string>
#include <QStringList>
#include <QWidget>
#include <QGridLayout>
#include <QTabWidget>

//#include "alphanum.hpp"


using namespace std;


// summare of the file: stores most of the classes used to run the program





class priority
{
	// summary: priority class for items, to work out sorting and to store the priority status for further data manipulation
	// took me a full workday to write this class, which I guess I can use as a reference point for other workloads and my skills development
	public:

		priority() : priorities {"ASAP","URGENT","HIGH","NORMAL/HIGH","NORMAL/MEDIUM","NORMAL/LOW","LOW"}{}

		~priority(){};


		void clear()
		{
			// reset to an arbitrarily high value as a placeholder null
			index = 100;
		}


		// !!!!!!!!!!!!!!!!!!!!!!!!!
		// NOTICE NOTICE NOTICE
		// WARNING WARNING WARNING WARNING WARNING
		// !!!!!!!!!!!!!!!!!!!!!!!!!
		// HEADS UP. We might cause a HUGE bug by returning the string from the array instead of directly copying the original string!!!
		// But also I spent a whole day trying to compare strings to array strings THAT ARE EXACTLY THE SAME BUT THEY DON'T WORK FOR SOME REASON so I gave up; the time spent wasn't worth the effort. If the bug pops up in the future, ASK FOR HELP. But right now (2Feb2021) it's just not worth the time.
		string GetPriority()
		{
			//cout << "index is " << index << endl;
			//cout << "so string should be: " << priorities[index] << endl;
			string error = "INVALID";
			if ((index <= 7) & (index >= 0)) return priorities[index];
			else return error;
		}


		int GetPriorityIndex()
		{
			return index;
		}
		void SetPriority(string priorityInput)
		{

			//cout << "Priority in SetPriority() is " << priorityInput << endl;

		// potential bug: HIGH gets confirmed twice
		// also I got array comparison to work an hour after typing that warning above. Yay.
		// but yeah it has a bug because I don't know how to compare string length to c_str length
			for (int i = 0; i < 7; i++)
			{
				string iPrio = priorities[i].c_str();
				if ((priorityInput.find(priorities[i].c_str()) != string::npos))
				{
					// todo: fix that bug with HIGH being confirmed twice
						index = i;
						cout << "priority confirmed to be " << index << endl;
				}
			}

			//cout << "resulting priority is " << index << endl;

		}
		void SetPriority(int inputIndex)
		{
			if ((inputIndex < 8) & (inputIndex > -1)) index = inputIndex;
			else cout << "The inputted priority number " << inputIndex << " is an INVALID PRIORITY!" << endl;
		}

	private:
		int index;

		// I wonder if I can store these elsewhere to save memory...
		string priorities[7];

};


class item
{
    // summary: proto task item object, containing all the stuff in one item

	public:

		// default initialization
		item(){}

		// full initialization
		item(string name, string description, string statprimary, string statsec, priority prio, bool mtt) : fromName(name), descr(description), statusPrimary(statprimary), statusSecondary(statsec), currentPriority(prio), movedToOtherDay(mtt) {}

		// custom initializers (if any)

		~item(){}


        // getters and setters
        void SetName (string name)
        {
           fromName = name;
        }

        string GetName ()
        {
            return fromName;
        }

        void SetDescription (string newDescription)
        {
           descr = newDescription;
        }

        string GetDesc()
        {
            return descr;
        }

        void SetStatPrimary (string newStatPrim)
        {
           statusPrimary = newStatPrim;
        }

        string GetStatPrimary()
        {
            return statusPrimary;
        }

        void SetStatSec(string newStatSec)
        {
           statusSecondary = newStatSec;
        }

        string GetStatSec()
        {
            return statusSecondary;
        }

        void SetPriority (priority newPriority)
        {
           currentPriority = newPriority;
        }

        string ReadPriority()
        {
            return currentPriority.GetPriority();
        }

        priority GetPriority()
        {
        	return currentPriority;
        }

        void ClearAll()
        {

            fromName.clear();
            descr.clear();
            statusPrimary.clear();
            statusSecondary.clear();
            currentPriority.clear();

        }

        void SetMTOD (bool newState)
        {
            movedToOtherDay = newState;
        }

        bool GetMTOD ()
        {
            return movedToOtherDay;
        }

        string GetMTODAnswer()
        {
            if (movedToOtherDay) return "Yes";
            else return "No";
        }


        void PrintCurrentItem()
        {
            // summary: for debugging only. Prints the current contents of the item
            cout << "----" << std::endl;
            cout << "FROM: " << fromName << std::endl
            << descr << std::endl
            << "STATUS: " << statusPrimary << ";" << statusSecondary << std::endl
            << "Moved To Tomorrow? " << GetMTODAnswer() << std::endl
            << "PRIORITY: " << currentPriority.GetPriority() << std::endl;
        }

        //friend ostream& operator<<(ostream& os, const item& dt);






        bool operator<(item& i)
        {
        	return currentPriority.GetPriorityIndex() < i.currentPriority.GetPriorityIndex();
        }


    private:

    // item properties

        string fromName;

        string descr;

        string statusPrimary;

        string statusSecondary;

        priority currentPriority;

        bool movedToOtherDay;


};

class tab
{
    // summary: proto tab object

    public:

        QString GetFile()
        {
            return matchingFile;
        }

        void SetFile(QString newFile)
        {
            matchingFile = newFile;
        }

        string GetName()
        {
        	return tabName;
        }

		void SetTabName(QString newFile)
		{
			string newTabName = newFile.toUtf8().constData();
            string omitString = "Task Feed ";
            string omitEnd = ".txt";
            string dash = "- ";
            tabName = newTabName.erase(newTabName.find(omitString),omitString.length());
            if (tabName.find(dash) != string::npos) tabName = tabName.erase(tabName.find(dash),dash.length());
            tabName = tabName.erase(tabName.find(omitEnd),omitEnd.length());
		}

        // vector containing all items
        vector<item> items;

        bool operator<(const tab& t) const
        {
        	return tabName < t.tabName;
        }

        //friend ostream& operator<<(ostream& os, const tab& dt);

    private:

        QString matchingFile;

		string tabName;



};

class taskFeedFile
{
	// summary: simple wrapper to contain both the task feed file location and the tabs
	public:

		vector<tab> GetTabsVector()
		{
			return tabsVector;
		}

		void setTabsVector(vector<tab> inputtedTabsVector)
		{
			tabsVector = inputtedTabsVector;
		}

		QStringList GetFileLocations()
		{
			return fileLocations;
		}

		void setFileLocations(QStringList inputtedFileLocations)
		{
			fileLocations = inputtedFileLocations;
		}

		bool emptyTabs()
		{
			if (tabsVector.empty()) return true;
			else return false;
		}

	private:

		vector<tab> tabsVector;

		QStringList fileLocations;

};



// don't mind this - just making sure I still have the code I used to make alphanum work before. Still trying to figure it out btw.
//namespace doj
//{
//  template<class Ty>
//  struct alphanum_less : public std::binary_function<Ty, Ty, bool>
//  {
//    bool operator()(const Ty& left, const Ty& right) const
//    {
//      return alphanum_comp(left, right) < 0;
//    }
//
//    bool operator()(tab& left, tab& right) const
//    {
//    	return alphanum_comp(left.GetName(), right.GetName()) < 0;
//    }
//    bool operator()(item& left, item& right) const
//    {
//    	return alphanum_comp(left.GetPriority().GetPriorityIndex(),right.GetPriority().GetPriorityIndex()) <0;
//    }
//  };
//}
