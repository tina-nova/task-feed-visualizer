#ifndef TFV_POPULATINGFUNCTIONS_H
#define TFV_POPULATINGFUNCTIONS_H

#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <QDir>
#include <QDirIterator>
#include <QString>
#include <QBoxLayout>
#include "TFV_Classes.h"

using std::string;

tab CreateTableItems(tab currentTab, bool printLog, bool veryVerbose);
taskFeedFile PopulateTables(QString sourcePath);
string populateItems(item i);

#endif // TFV_POPULATINGFUNCTIONS_H
