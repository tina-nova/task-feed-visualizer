#include "MainClass.h"
#include "TFV_PopulatingFunctions.h"
#include "TFV_LabelFunctions.h"

using std::vector;




int main(int argc, char *argv[])
{
	// Step0. Define everything

	QApplication a(argc, argv);

	QTabWidget *tabFullList = new QTabWidget();
	tabFullList->setTabPosition(QTabWidget::South);
	QFileSystemWatcher watchUpdates;
	QStringList watchUpdatesQS;


	// Step0a. this tab vector array will contain all the data in memory. It's probably an incredibly terrible and non-secure way to store it, but whatever it's not like I'm gonna make this thing connect to the internet or anything. Also as of 1Feb2021 I don't know any other way to implement it.
	vector<tab> tabs;
	// Step0b. This will be used to get the directory from which to retrieve the subdirectories full of task feeds
	QString workingDirectory;
	// Step0c. This will be used to process the working directory and retrieve both the tab array and a list of files to continuously check for modifications
	taskFeedFile taskFeedFileToProcess;
	QStringList taskFeedFiles;

	if (argc == 2)
	{
		workingDirectory = argv[1];
		cout << "Custom directory provided. New working directory is " << argv[1] << endl;
	}

	// Step1. scan all the subdirectories to populate the tabs and the items within each tab
	taskFeedFileToProcess = PopulateTables(workingDirectory);

	if (taskFeedFileToProcess.GetTabsVector().empty())
	{
		QWidget *p = new QWidget();
		QMessageBox::information(p,"No Task Feed Files Found","We could not find any task feed files. Check the directory and try again.");
		a.exit();
	}

	else
	{
		tabs = taskFeedFileToProcess.GetTabsVector();



		// Step2. Scan all the text files to see if there are any changes, so that the viewer can update its contents
		taskFeedFiles = taskFeedFileToProcess.GetFileLocations();
		watchUpdates.addPaths(taskFeedFiles);
		watchUpdatesQS = watchUpdates.files();
		#ifdef DEBUG
		cout << "Currently watching files: " << endl;
		for (QString q : watchUpdatesQS)
		{
			cout << q.toUtf8().constData() << endl;
		}
		#endif

		//MainClass *mc = new MainClass;
		//QObject::connect(&watchUpdates, SIGNAL(fileChanged(QString)), [] {;});
		{
			QWidget *w = new QWidget();
			QGridLayout *gridLayout = new QGridLayout;
			// Step3 and Step4. Count the number of tabs and then create them in the window
			gridLayout->addWidget(PopulateTabs(tabFullList, tabs));
			gridLayout->setSpacing(0);
			gridLayout->setMargin(0);

			// Set the grid layout as a main layout
			w->setLayout(gridLayout);

			// Window title
			w->setWindowTitle("Task Feed Visualizer");
			w->setBaseSize(1500,1000);

			// Display
			w->show();
		}

	// Event loop
	return a.exec();
	}

}
