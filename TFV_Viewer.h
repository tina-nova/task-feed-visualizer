#ifndef VIEWER_H
#define VIEWER_H

#include <QObject>
#include <QWidget>
#include <QStackedWidget>
#include <QFileSystemWatcher>
#include "TFV_Classes.h"


using std::vector;



class Viewer : public QObject
{
    Q_OBJECT


public:
	explicit Viewer(QObject *parent = nullptr);

	Viewer(vector<tab> tabsAdd, QString workingDirectory, QFileSystemWatcher *watcher);


public slots:

	void RefreshViewer(QString fileChanged);

//	void TestPopup();


signals:



private:

	QString thisWorkingDir;

	QStackedWidget *s;

	void RunViewer(vector<tab> tabs, QWidget *newWidget);

	QFileSystemWatcher *thisWatcher;

};

#endif // VIEWER_H
