
#include "TFV_Classes.h"


using std::cout;
using std::string;
using std::vector;
using std::endl;


// summary of the file: stores most of the classes used to run the program



///////////////
/// \brief The priority class
///
/// Priority class for items, to work out sorting and to store the priority status for further data manipulation

	// took me a full workday to write this class, which I guess I can use as a reference point for other workloads and my skills development

	void priority::clear()
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
	string priority::GetPriority()
	{
		//cout << "index is " << index << endl;
		//cout << "so string should be: " << priorities[index] << endl;
		string error = "INVALID";
		if ((index <= 7) & (index >= 0)) return priorities[index];
		else return error;
	}


	int priority::GetPriorityIndex()
	{
		return index;
	}
	void priority::SetPriority(string priorityInput)
	{

		//cout << "Priority in SetPriority() is " << priorityInput << endl;

	// potential bug: HIGH gets confirmed twice
	// also I got array comparison to work an hour after typing that warning above. Yay.
		for (int i = 0; i < 7; i++)
		{
			string iPrio = priorities[i].c_str();
			if ((priorityInput.find(priorities[i].c_str()) != string::npos) & (priorities[i].length() == priorityInput.length()))
			{
				// UPDATE6MAY2021: bug for double high and double low confirmations fixed by comparing the length of both strings
					index = i;
                    //cout << "priority confirmed to be " << index << endl;
			}
		}

        //cout << "resulting priority is " << index << endl;

	}

	void priority::SetPriority(int inputIndex)
	{
		if ((inputIndex < 8) & (inputIndex > -1)) index = inputIndex;
		else cout << "The inputted priority number " << inputIndex << " is an INVALID PRIORITY!" << endl;
	}

/////////////////////
/// \brief The item class
///	Proto task item object, containing all the stuff in one item


	// getters and setters
	void item::SetName (string name)
	{
	   fromName = name;
	}

	string item::GetName ()
	{
	    return fromName;
	}

	void item::SetDescription(string newDescription)
	{
	   descr = newDescription;
	}

	string item::GetDesc()
	{
	    return descr;
	}

	void item::SetStatPrimary (string newStatPrim)
	{
	   statusPrimary = newStatPrim;
	}

	string item::GetStatPrimary()
	{
	    return statusPrimary;
	}

	void item::SetStatSec(string newStatSec)
	{
	   statusSecondary = newStatSec;
	}

	string item::GetStatSec()
	{
	    return statusSecondary;
	}

	void item::SetPriority (priority newPriority)
	{
	   currentPriority = newPriority;
	}

	string item::ReadPriority()
	{
	    return currentPriority.GetPriority();
	}

	priority item::GetPriority()
	{
		return currentPriority;
	}

	void item::ClearAll()
	{

	    fromName.clear();
	    project.clear();
	    descr.clear();
	    statusPrimary.clear();
	    statusSecondary.clear();
	    currentPriority.clear();

	}

	void item::SetMTOD (bool newState)
	{
	    movedToOtherDay = newState;
	}

	bool item::GetMTOD ()
	{
	    return movedToOtherDay;
	}

	string item::GetMTODAnswer()
	{
	    if (movedToOtherDay) return "Yes";
	    else return "No";
	}

	void item::PrintCurrentItem()
	{
	    // summary: for debugging only. Prints the current contents of the item
	    cout << "----" << std::endl;
	    cout << "FROM: " << fromName << std::endl
	    << "PROJECT: " << project << std::endl
	    << descr << std::endl
	    << "STATUS: " << statusPrimary << ";" << statusSecondary << std::endl
	    << "Moved To Tomorrow? " << GetMTODAnswer() << std::endl
	    << "PRIORITY: " << currentPriority.GetPriority() << std::endl;
	}

	bool item::operator<(item& i)
	{
		return currentPriority.GetPriorityIndex() < i.currentPriority.GetPriorityIndex();
	}

	void item::SetProject(string newProject)
	{
		project = newProject;
	}

	string item::GetProject()
	{
		return project;
	}


///////////////
/// \brief The tab class
/// Tab Object meant to contain the items of each tab as well as its name and associated file


        QString tab::GetFile()
        {
            return matchingFile;
        }

        void tab::SetFile(QString newFile)
        {
            matchingFile = newFile;
        }

        string tab::GetName()
        {
        	return tabName;
        }

		void tab::SetTabName(QString newFile)
		{
			string newTabName = newFile.toUtf8().constData();
            string omitString = "Task Feed ";
            string omitEnd = ".txt";
            string dash = "- ";
            tabName = newTabName.erase(newTabName.find(omitString),omitString.length());
            if (tabName.find(dash) != string::npos) tabName = tabName.erase(tabName.find(dash),dash.length());
            tabName = tabName.erase(tabName.find(omitEnd),omitEnd.length());
		}

        bool tab::operator<(const tab& t) const
        {
        	return tabName < t.tabName;
        }



////////////
/// \brief The taskFeedFile class
///	Simple wrapper to contain both the task feed file location vector and the tabs vector
///


		vector<tab> taskFeedFile::GetTabsVector()
		{
			return tabsVector;
		}

		void taskFeedFile::setTabsVector(vector<tab> inputtedTabsVector)
		{
			tabsVector = inputtedTabsVector;
		}

		QStringList taskFeedFile::GetFileLocations()
		{
			return fileLocations;
		}

		void taskFeedFile::setFileLocations(QStringList inputtedFileLocations)
		{
			fileLocations = inputtedFileLocations;
		}

		bool taskFeedFile::emptyTabs()
		{
			if (tabsVector.empty()) return true;
			else return false;
		}



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
