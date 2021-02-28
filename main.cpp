#include <QFileDialog>
#include "MainClass.h"
#include "TFV_PopulatingFunctions.h"
#include "TFV_LabelFunctions.h"
#include "TFV_Viewer.h"

using std::vector;
using std::endl;
using std::cout;


// summary: The program follows a pretty simple process to initialize the folder and text files all the way to drawing the actual window, going from Steps 0 to 4.




int main(int argc, char *argv[])
{
	// Step0. Define everything

	QApplication a(argc, argv);

	QFileSystemWatcher *watchUpdates = new QFileSystemWatcher();
	QStringList watchUpdatesQS;


	// Step0a. this tab vector array will contain all the data in memory. It's probably an incredibly terrible and non-secure way to store it, but whatever it's not like I'm gonna make this thing connect to the internet or anything. Also as of 1Feb2021 I don't know any other way to implement it.
	vector<tab> tabs;
	// Step0b. This will be used to get the directory from which to retrieve the subdirectories full of task feeds
	QString workingDirectory;
	// Step0c. This will be used to process the working directory and retrieve both the tab array and a list of files to continuously check for modifications
	taskFeedFile taskFeedFileToProcess;
	QStringList taskFeedFiles;



	// Step0d. Set the working directory to a custom address if an extra argument was added
	if (argc == 2)
	{
		workingDirectory = argv[1];
		cout << "Custom directory provided. New working directory is " << argv[1] << endl;
	}


	// Step1a. scan all the subdirectories to populate the tabs and the items within each tab
	taskFeedFileToProcess = PopulateTables(workingDirectory);

	// Step1b. Check if the directory is empty. If so, close the program.

		if (taskFeedFileToProcess.GetTabsVector().empty())
		{
			QWidget *d = new QWidget();
			workingDirectory = QFileDialog::getExistingDirectory(d,"Open Directory", QDir::currentPath(), QFileDialog::ShowDirsOnly  | QFileDialog::DontResolveSymlinks);
			d->deleteLater();
			taskFeedFileToProcess = PopulateTables(workingDirectory);
			if (taskFeedFileToProcess.GetTabsVector().empty())
			{
				QWidget *p = new QWidget();
				QMessageBox::information(p,"No Task Feed Files Found","We could not find any task feed files. Check the directory and try again.");
				p->deleteLater();
				a.exit();
			}
			else
			{
					cout << "Task Feed File(s) found. Setting up viewer..." << endl;
					tabs = taskFeedFileToProcess.GetTabsVector();



					// Step2. Scan all the text files to see if there are any changes, so that the viewer can update its contents
					cout << "Getting File locations..." << endl;
					taskFeedFiles = taskFeedFileToProcess.GetFileLocations();
					cout << "Adding paths to watch updates..." << endl;
					watchUpdates->addPaths(taskFeedFiles);

					#ifdef DEBUG
					watchUpdatesQS = watchUpdates->files();
					cout << "Currently watching files: " << endl;
					for (QString q : watchUpdatesQS)
					{
						cout << q.toUtf8().constData() << endl;
					}
					#endif

					// Steps 3 and 4 continue in the TFV_Viewer class
					Viewer viewer(tabs, workingDirectory, watchUpdates);

					// signal-slot system to detect if any of the files have been modified
					QObject::connect(watchUpdates, SIGNAL(fileChanged(QString)), &viewer, SLOT(RefreshViewer(QString)));

					// Event loop
					return a.exec();
			}

		}

		// Step1c. If not, get the identified files that will be turned into tabs.
		else
		{
			cout << "Task Feed File(s) found. Setting up viewer..." << endl;
			tabs = taskFeedFileToProcess.GetTabsVector();



			// Step2. Scan all the text files to see if there are any changes, so that the viewer can update its contents
			cout << "Getting File locations..." << endl;
			taskFeedFiles = taskFeedFileToProcess.GetFileLocations();
			cout << "Adding paths to watch updates..." << endl;
			watchUpdates->addPaths(taskFeedFiles);

			#ifdef DEBUG
			watchUpdatesQS = watchUpdates->files();
			cout << "Currently watching files: " << endl;
			for (QString q : watchUpdatesQS)
			{
				cout << q.toUtf8().constData() << endl;
			}
			#endif

			// Steps 3 and 4 continue in the TFV_Viewer class
			Viewer viewer(tabs, workingDirectory, watchUpdates);

			// signal-slot system to detect if any of the files have been modified
			QObject::connect(watchUpdates, SIGNAL(fileChanged(QString)), &viewer, SLOT(RefreshViewer(QString)));

			// Event loop
			return a.exec();
		}

}
