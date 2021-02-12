

#include "TFV_PopulatingFunctions.h"
#include <alphanum.hpp>


using std::string;
using std::vector;



// summary of file: stores most of the actual custom class functions used to run the program




tab CreateTableItems(tab currentTab, bool printLog, bool veryVerbose)
{
    // summary: read the contents of tab and output as a label item

    bool primedForDescription = false;
    item currentItem;
    string descriptionContent;
    bool currentlyMakingNewLabel = false;

    string textFile = currentTab.GetFile().toUtf8().constData();
    cout << "text file is: " << textFile << endl;

    std::ifstream tabFile(textFile.c_str());

	// parse each line "p" in the file retrieved
    for (std::string p; std::getline(tabFile, p);)
    {
        if (printLog) cout << "line content is: " << p << endl;
        if (!primedForDescription)
        {
                if (p.empty())
                {
                    if (printLog & veryVerbose) cout << "line is empty" << endl;
                    // just skip if empty
                }
                else if (p.find("----") != string::npos)
                {
                    if (printLog & veryVerbose) cout << "line contains divider" << endl;
                    // create a new label if this is the first divider in an entry
                    // if already making new label, that means it's the closing divider. push the new item into the vector and then clear everything
                    if (currentlyMakingNewLabel)
                    {
                        if (printLog) currentItem.PrintCurrentItem();
                        currentTab.items.push_back(currentItem);
                        currentItem.ClearAll();
                    }
                    else
                    {
                        // only activated at the very first divider to prime the scanner for new items
                        if (printLog) cout << "Ok, making the next label..." << endl;
                        currentlyMakingNewLabel = true;
                    }

                }
                else if (p.find("FROM:") != string::npos)
                {
                    if (printLog & veryVerbose) cout << "line contains assigner name" << endl;
                    primedForDescription = true;
                    if (printLog) cout << "Current item has been primed for description." << endl;
                    string pFind = "FROM:";
                    currentItem.SetName(p.erase(p.find(pFind),pFind.length()));
                    if (printLog & veryVerbose) cout << "FROM has been added... " << endl;
                }
                else if (p.find("STATUS:") != string::npos)
                {
                    if (printLog) cout << "line contains status but you shouldn't be seeing this particular debug line!" << endl;

                }
                else if (p.find("PRIORITY:") != string::npos)
                {
                    if (printLog & veryVerbose) cout << "line contains priority" << endl;
                    string pFind = "PRIORITY:";
                    priority newPriority;
                    string pFindErase = (p.erase(p.find(pFind),pFind.length()));
                    if (printLog) cout << "erased priority string is " << pFindErase << endl;
                    newPriority.SetPriority(pFindErase);
                    if (printLog) cout << "priority for item is " << newPriority.GetPriorityIndex() << ", or" << newPriority.GetPriority() << endl;
                    currentItem.SetPriority(newPriority);
                }
                else
                {
                    if (printLog) cout << "line contains something else that we don't recognize" << endl;
                }
        }
        // if primed to build the item description, check if the line is the status line. if not, add the line to the description
        else
        {
            if (p.find("STATUS:") != string::npos)
            {
                primedForDescription = false;
                currentItem.SetDescription(descriptionContent);
                descriptionContent.clear();
                if (printLog & veryVerbose) cout << "line contains status and is no longer primed for description" << endl;
                bool setToOtherDay(p.find("MOVED") != string::npos);
                currentItem.SetMTOD(setToOtherDay);
                string pFind = "STATUS:";
                currentItem.SetStatPrimary(p.erase(p.find(pFind),pFind.length()));

            }
            else
            {
                descriptionContent.append(p + "\n");
            }
        }
        if (printLog & veryVerbose) cout << "Line processed. Going to next line..." << endl;
    }

    if (printLog & veryVerbose)
    {
        cout << "CurrentTab contains: " << endl;
        for (item currentIt : currentTab.items) currentIt.PrintCurrentItem();
    }
    return currentTab;
}


taskFeedFile PopulateTables(QString sourcePath)
{

        // summary: reads the current directory for all subdirectories containing days and then turns each day into a tab

        // check first if sourcePath is valid. Otherwise, use the working directory
        cout << "Source Path is " << sourcePath.toUtf8().constData() << endl;
        if (sourcePath.isNull()) sourcePath = QDir::currentPath();
		else {}

		// process sourcePath and declare other stuff
		QDirIterator directoryLists(sourcePath, QDir::Files | QDir::NoDotAndDotDot , QDirIterator::Subdirectories );
		QStringList fileLocations;
		std::vector<tab> tabs;
		taskFeedFile taskFeedFile;

        // for each directory, check if it follows the format of "Assigned <Day> <Month>" and then add that into the list of directories
        while (directoryLists.hasNext())
        {
            if (directoryLists.filePath().contains("Assigned") & directoryLists.filePath().contains("Task Feed") & directoryLists.filePath().contains(".txt") & !directoryLists.filePath().contains("~"))
            {
                cout << directoryLists.filePath().toUtf8().constData() << " is a valid task feed file" << endl;
                fileLocations.append(directoryLists.fileInfo().absoluteFilePath());
                tab newTab;
                newTab.SetFile(directoryLists.filePath());
                newTab.SetTabName(directoryLists.fileName());
                tabs.push_back(newTab);
            }
            else cout << directoryLists.filePath().toUtf8().constData() << " is not an applicable file" << endl;
            directoryLists.next();
        }

// if the program can't locate any valid files, exit
        if (tabs.empty())
			return taskFeedFile;

		// sort tabs alphanumerically. Note that fileLocations does not get sorted because it'll only be used to check if the files have been modified
        std::sort(tabs.begin(),tabs.end(),doj::alphanum_less<tab>());


        // create the tabs in the UI and then populate them with items
        cout << "creating tabs..." << endl;

        for (tab& t : tabs)
        {
            // create table items
            cout << "Now creating table items of " << t.GetFile().toUtf8().constData() << " ... " << endl;
            t = CreateTableItems(t,false,false);
            cout << "number of tasks in this tab is: " << t.items.size() << endl;;
        }


#ifdef DEBUG
// debug log to output all content
        cout << "tabs created! outputting all internal content..." << endl;
        for (tab t : tabs)
        {
            cout << t.GetFile().toUtf8().constData() << endl;
            cout << "Number of tasks: " << t.items.size() << endl;
            for (item specificItem: t.items) {specificItem.PrintCurrentItem();}
            cout << "end of tab " << t.GetFile().toUtf8().constData() << endl << endl;
        }
#endif
		taskFeedFile.setTabsVector(tabs);
		taskFeedFile.setFileLocations(fileLocations);

        return taskFeedFile;
}

string populateItems(item i)
{

// summary: remake a readable version of each item within a tab using a better format than the one in the text file

	string result;
	string newline = "\n";

	result = "FROM: " + i.GetName() + newline
		+ i.GetDesc()
		+ "STATUS: " + i.GetStatPrimary();

	if (!empty(i.GetStatSec()))
	{
		result += i.GetStatSec() + newline;
	}
	else
	{
		result += newline;
	}

	result += "PRIORITY: " + i.ReadPriority();

	#ifdef DEBUG
	cout << "Priority index is" << i.GetPriority().GetPriorityIndex() << endl;
	#endif

	return result;

}


