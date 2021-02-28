#include <QApplication>
#include <QMessageBox>
#include <QThread>
#include "TFV_LabelFunctions.h"
#include "TFV_Viewer.h"
#include "TFV_PopulatingFunctions.h"

Viewer::Viewer(QObject *parent) : QObject(parent)
{
}

// Step3a. Initialize the viewer class, including the RunViewer function
Viewer::Viewer(vector<tab> tabs, QString workingDirectory, QFileSystemWatcher *watcher)
{
	thisWatcher = watcher;
	QWidget *w = new QWidget();

	// use a stacked widget for easy refreshing
	s = new QStackedWidget();

	thisWorkingDir = workingDirectory;
	RunViewer(tabs,w);
}


void Viewer::RunViewer(vector<tab> tabs, QWidget *newWidget)
{
	QTabWidget *tabFullList = new QTabWidget();
	tabFullList->setTabPosition(QTabWidget::South);
	QGridLayout *gridLayout = new QGridLayout;

	// Step3b. count the number of tabs
	std::cout << "Populating tabs... " << std::endl;
	gridLayout->addWidget(PopulateTabs(tabFullList, tabs));
	gridLayout->setSpacing(0);
	gridLayout->setMargin(0);


	// Step3c. Set the grid layout as a main layout
	newWidget->setLayout(gridLayout);

	// Step3d. Add the new widget to the main window
	s->addWidget(newWidget);


	// Step4. If the window is already open, just put a new widget on top of the old one. Otherwise, open a new window
	if (s->isVisible())
	{
		s->setCurrentWidget(newWidget);
		// loop just in case I somehow end up with multiple widgets
		for (int i = s->count(); i > 0; i--)
		{
			QWidget *toDelete = s->widget(i);
			if  (toDelete == newWidget);
			else
			{
				s->removeWidget(toDelete);
				toDelete->deleteLater();
			}
		}

	}
	else
	{
		// Window title
		s->setWindowTitle("Task Feed Visualizer");
		s->setBaseSize(1500,1000);

		// Display
		s->show();
	}
}

////////
/// \brief Viewer::RefreshViewer
/// \param currentWorkingDirectory
///
/// A function to run simultaneously with the current application. If a change is detected, the qfilemonitor thing will activate this function, creating a new widget with the updated text


// note: I currently don't plan on checking again if the directory has been emptied completely. Will add that functionality when I've got my other priority features done.

void Viewer::RefreshViewer(QString fileChanged)
{
	std::cout << "File change detected! Refreshing..." << std::endl;


	// arbitrary milliseconds to make sure file is readable on next pass, as per
	// https://stackoverflow.com/questions/18300376/qt-qfilesystemwatcher-signal-filechanged-gets-emited-only-once
	QThread::msleep(100);

	thisWatcher->addPath(fileChanged);

	QWidget *nw = new QWidget();

	RunViewer(PopulateTables(thisWorkingDir).GetTabsVector(), nw);

}

//void Viewer::TestPopup()
//{
//	QWidget *r = new QWidget();
//	QMessageBox::information(r,"File modified", "File has been modified. Current window will now close...");
//	s->close();
//}
