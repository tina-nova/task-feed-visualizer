#ifndef TFV_LABELFUNCTIONS_H
#define TFV_LABELFUNCTIONS_H

#include <QTabWidget>
#include <QGridLayout>
#include <QLabel>
#include <QScrollArea>
#include <iostream>
#include "TFV_Classes.h"


using std::vector;



QLabel* MakeLabels(QLabel* label, QString stringName, int width, int height);
void ItemsToColumns (QVector<QLabel*> statusItems, QVBoxLayout* column1, QVBoxLayout* column2);
QTabWidget *PopulateTabs(QTabWidget *tabList, vector<tab> tabs);

#endif // TFV_LABELFUNCTIONS_H


