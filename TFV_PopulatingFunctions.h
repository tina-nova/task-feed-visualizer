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

class tab;
class taskFeedFile;
class item;

using std::string;

tab CreateTableItems(tab currentTab, bool printLog, bool veryVerbose);
taskFeedFile PopulateTables(QString sourcePath);
string populateItems(item i);

#endif // TFV_POPULATINGFUNCTIONS_H
