


#include "TFV_PopulatingFunctions.h"
#include "TFV_LabelFunctions.h"
#include "TFV_CustomClassSort.h"

using std::string;
using std::endl;
using std::cout;




// file summary: stores most of the Qt-related functions needed to display the program


QLabel* MakeLabels(QLabel* label, QString stringName, int width, int height)
{

	// summary: gets a blank label and adds all the details, outputting a fully-made label. Used for both items (150x150 square) and marker labels (300x150 rectangle)
	// theoretically only those two options should exist, so the else statement below assumes that anything that isn't a marker label is an item label

			// assign text and parameters

			QFont font = label->font();
			label->setFixedSize(width,height);
			label->setFrameStyle(QFrame::Panel | QFrame::Raised);
			label->setText(stringName);
			label->setAlignment(Qt::AlignCenter | Qt::AlignCenter );
			label->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
			label->setWordWrap(true);

			// allocate enough memory for stylesheet later using an arbitrary value
			//QString styleSheetAlloc;
			//styleSheetAlloc.reserve(100);
			//label->setStyleSheet(styleSheetAlloc);
			//cout << "Style Sheet allocation size is: " << label->styleSheet().size() << endl;


			// resize font to fit label

			// if main marker label, make font bigger and add color
			if (width > height)
			{
				font.setPointSize(font.pointSize()*2);
				label->setFont(font);
				if (stringName == "ON HOLD")
						label->setStyleSheet("QLabel { background-color : #FFFF00 }");
				else if (stringName == "DONE")
						label->setStyleSheet("QLabel { background-color : #D9D9D9 }");
				else if (stringName == "MOVED")
						label->setStyleSheet("QLabel { background-color : #00B0F0 }");
			}
			// if normal item, resize font
			else
			{
				// resize code below taken from
				// https://gist.github.com/earthday/7cb3cb9b00f033e05834
				// which itself was taken from
				// http://www.qtforum.org/article/32092/dynamic-font-size-in-qlabel-based-on-text-length.html
				// which is now unfortunately gone
				// some modifications were made

				bool fit = false;
				while (!fit)
				{
					QFontMetrics fm(font);
					QRect bound = fm.boundingRect(0,0,label->width(),label->height(), Qt::TextWordWrap | Qt::AlignLeft,stringName);
					if ((bound.width() <= label->width()) && (bound.height() <= label->height()))
					{
						label->setFont(font);
						fit = true;
					}
					else font.setPointSize(font.pointSize()-1);
				}
			}
			return label;
}



void ItemsToColumns (QVector<QLabel*> statusItems, QVBoxLayout* column1, QVBoxLayout* column2)
{
	// summary: add each item into both columns, filling with a blank if there are no items for the column

	int counter = 0;
	if (statusItems.empty())
	{
		QLabel *blankItem = new QLabel();
		blankItem->setFixedSize(150,150);
		statusItems.append(blankItem);
		statusItems.append(blankItem);
	}
	if (statusItems.length() == 1)
	{
		QLabel *blankItem = new QLabel();
		blankItem->setFixedSize(150,150);
		statusItems.append(blankItem);
	}
	for (QLabel* ql : statusItems)
	{
		if ((counter % 2) == 0)
		{
			column1->addWidget(ql);
			counter++;
		}
		else
		{
			column2->addWidget(ql);
			counter++;
		}
	}
	column1->addStretch();
	column2->addStretch();

}

QTabWidget *PopulateTabs(QTabWidget *tabList, vector<tab> tabs)
{

// summary: create the qt tabs and qt labels for each tab and label, respectively. Also colors each item and sorts by priority

	for (tab& t : tabs)
		{
			// Step 0a: sort items by priority before processing into columns. After sorting here, they'll get converted to QLabels... so we can't sort them anymore after! Unless I figure out a way to link them but this program is complicated enough as it is.
			cout << "Sorting each item by priority..." << endl;
			std::sort(t.items.begin(),t.items.end(),& item_less);

			//cout << "Assigning widgets, labels, and layouts..." << endl;
			// Step 0b: declare the main canvasses
			QWidget *newTabScrollablePage = new QWidget();
			QWidget *newTabFullPage = new QWidget();
			QGridLayout *columnLayout = new QGridLayout;
			QScrollArea *innerScrollArea = new QScrollArea();
			QScrollArea *outerScrollArea = new QScrollArea();
			QGridLayout *mainGridLayout = new QGridLayout;


			// Step 0c: initialize all the status columns
			// I'm used to having two columns per status so...
			QVBoxLayout *notStarted1 = new QVBoxLayout;
			QVBoxLayout *notStarted2 = new QVBoxLayout;
			QVBoxLayout *onHold1 = new QVBoxLayout;
			QVBoxLayout *onHold2 = new QVBoxLayout;
			QVBoxLayout *ongoing1 = new QVBoxLayout;
			QVBoxLayout *ongoing2 = new QVBoxLayout;
			QVBoxLayout *done1 = new QVBoxLayout;
			QVBoxLayout *done2 = new QVBoxLayout;
			QVBoxLayout *moved1 = new QVBoxLayout;
			QVBoxLayout *moved2 = new QVBoxLayout;

			// Steb 0d: initialize the column markers...
			QHBoxLayout *markerRow = new QHBoxLayout;
			QLabel *notStartedLabel = new QLabel();
			QLabel *onHoldLabel = new QLabel();
			QLabel *ongoingLabel = new QLabel();
			QLabel *doneLabel = new QLabel();
			QLabel *movedLabel = new QLabel();


			// Step 0e: initialize all the status vectors for sorting purposes
			QVector<QLabel*> notStarted;
			QVector<QLabel*> onHold;
			QVector<QLabel*> ongoing;
			QVector<QLabel*> done;
			QVector<QLabel*> moved;

			//cout << "Step 1 and 2..." << endl;
			for (item& i : t.items)
			{
				//cout << "Step 1 for another item" << endl;
				// Step 1: create a new QLabel for each item
				QLabel *itemLabel = new QLabel();
			//	QFont font = itemLabel->font();
				QString itemLabelText = QString::fromStdString(populateItems(i));
				//cout << "Making basic uncolored label for this item..." << endl;
				itemLabel = MakeLabels(itemLabel,itemLabelText,150,150);
				// add a tooltip for a better view of the text
				itemLabel->setToolTip(itemLabelText);

				// Step2: color each label and then store in the appropriate vector
				// POTENTIAL BUG: too many possible paths. May need testing.


				// (1/3) check first if the priority is valid. If not, mark it with green.
				//cout << "Checking if priority is valid..." << endl;
				if (i.ReadPriority() == "INVALID")
				{
					itemLabel->setStyleSheet("QLabel { background-color : green }");
					notStarted.append(itemLabel);
					cout << "----------------" << endl << "Unusual entry detected. May be a misspelling. Check this entry:" << endl << i.GetDesc() << endl << "in [" << t.GetName() << "] for details." << endl;
				}
				else
				{
					// (2/3) color all lables white by default and then check if the item has been flagged for another day
					itemLabel->setStyleSheet("QLabel { background-color : #FFFFFF }");
					//cout << "Checking if status is MOVED" << endl;
					if (i.GetMTOD())
					{
						//cout << "Status is 'MOVED'" << endl;
						itemLabel->setStyleSheet("QLabel { background-color : #00b0f0 }");
						//cout << "Blue background" << endl;
						if (i.GetStatPrimary().find("ONHOLD") != string::npos)
						{
							//cout << "Yellow background" << endl;
							itemLabel->setStyleSheet("QLabel { background-color : #FFFF00 }");
						}
						if (i.ReadPriority() == "ASAP" || i.ReadPriority() == "URGENT" || i.ReadPriority() == "HIGH")
						{
							//cout << "Red background" << endl;
							itemLabel->setStyleSheet("QLabel { background-color : #FF0000 }");
						}
						//cout << "Appending..." << endl;
						moved.append(itemLabel);
					}

					// (3/3) finally, color the labels to match their status
					else
					{
						//cout << "Status is not 'MOVED'" << endl;
						if (i.GetStatPrimary().find("NOTSTARTED") != string::npos)
						{
							if (i.ReadPriority() == "ASAP" || i.ReadPriority() == "URGENT" || i.ReadPriority() == "HIGH")
							{
								itemLabel->setStyleSheet("QLabel { background-color : #FF0000 }");
							}
							notStarted.append(itemLabel);
						}
						else if (i.GetStatPrimary().find("CANCELED") != string::npos)
						{
							itemLabel->setStyleSheet("QLabel { background-color : #595959 }");
							notStarted.append(itemLabel);
						}
						else if (i.GetStatPrimary().find("ONHOLD") != string::npos)
						{
							itemLabel->setStyleSheet("QLabel { background-color : #FFFF00 }");
							if (i.ReadPriority() == "ASAP" || i.ReadPriority() == "URGENT" || i.ReadPriority() == "HIGH")
							{
								itemLabel->setStyleSheet("QLabel { background-color : #FF0000 }");
							}
							onHold.append(itemLabel);
						}
						else if (i.GetStatPrimary().find("ONGOING") != string::npos)
						{
							if (i.ReadPriority() == "ASAP" || i.ReadPriority() == "URGENT" || i.ReadPriority() == "HIGH")
							{
								itemLabel->setStyleSheet("QLabel { background-color : #FF0000 }");
							}
							ongoing.append(itemLabel);
						}
						else if (i.GetStatPrimary().find("DONE") != string::npos)
						{
							itemLabel->setStyleSheet("QLabel { background-color : #D9D9D9 }");
							done.append(itemLabel);
						}
						else
						{
							// this section isn't supposed to be here but misspellings can happen. May need to write something better in the future, but for now everything that doesn't work with the logic above just goes to the NOTSTARTED column in a weird unreal color like green
							itemLabel->setStyleSheet("QLabel { background-color : green }");
							notStarted.append(itemLabel);
							cout << "----------------" << endl << "Unusual entry detected. May be a misspelling. Check this entry:" << endl << i.GetDesc() << endl << "in [" << t.GetName() << "] for details." << endl;
						}
					}
				}

				//cout << "New item added to tab: " << i.GetDesc() << endl;
			}

			// Step3: now add all sorted items into their respective columns
			//cout << "Step3..." << endl;
			ItemsToColumns(notStarted,notStarted1,notStarted2);
			ItemsToColumns(onHold,onHold1,onHold2);
			ItemsToColumns(ongoing,ongoing1,ongoing2);
			ItemsToColumns(done,done1,done2);
			ItemsToColumns(moved,moved1,moved2);

			// Step4: add the markers first before the items...
			//cout << "Step4..." << endl;
			markerRow->addWidget(MakeLabels(notStartedLabel,"NOT STARTED",300,100));
			markerRow->addWidget(MakeLabels(onHoldLabel,"ON HOLD",300,100));
			markerRow->addWidget(MakeLabels(ongoingLabel,"ONGOING",300,100));
			markerRow->addWidget(MakeLabels(doneLabel,"DONE",300,100));
			markerRow->addWidget(MakeLabels(movedLabel,"MOVED",300,100));
			markerRow->setSpacing(0);
			markerRow->setMargin(1);
			markerRow->addStretch();

			// Step5a: put them all in the main window
			//cout << "Step5a..." << endl;
			columnLayout->addLayout(notStarted1,1,0);
			columnLayout->addLayout(notStarted2,1,1);
			columnLayout->addLayout(onHold1,1,2);
			columnLayout->addLayout(onHold2,1,3);
			columnLayout->addLayout(ongoing1,1,4);
			columnLayout->addLayout(ongoing2,1,5);
			columnLayout->addLayout(done1,1,6);
			columnLayout->addLayout(done2,1,7);
			columnLayout->addLayout(moved1,1,8);
			columnLayout->addLayout(moved2,1,9);
			columnLayout->setSpacing(0);
			columnLayout->setMargin(0);
			columnLayout->setRowStretch(0,0);

			// Step5b: Create a scrollbar parent for the page, to be used for export
			//cout << "Step5b..." << endl;
			newTabScrollablePage->setLayout(columnLayout);
			innerScrollArea->setWidget(newTabScrollablePage);
			innerScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
			outerScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
			mainGridLayout->setSpacing(0);
			mainGridLayout->setMargin(0);
			mainGridLayout->addLayout(markerRow,0,0);
			mainGridLayout->addWidget(innerScrollArea,1,0);
			mainGridLayout->setRowStretch(1,1);
			newTabFullPage->setLayout(mainGridLayout);
			//outerScrollArea->setWidget(newTabFullPage);


			// Step5c: Get the tab name
			//cout << "Step5c..." << endl;
			string newTabLabelString = t.GetName();
			QString newTabLabelQString = QString::fromStdString(newTabLabelString);

			cout << "Tab created. New tab name is: " << newTabLabelString << endl;

			// Step Final: Add this page to the tab list; it's ready to go!
			tabList->addTab(newTabFullPage, newTabLabelQString);
		}

	return tabList;
}

