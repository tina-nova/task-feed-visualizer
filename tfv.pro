QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
	TFV_Classes.cpp \
	TFV_CustomClassSort.cpp \
	TFV_Viewer.cpp \
    main.cpp \
    	TFV_LabelFunctions.cpp \
	TFV_PopulatingFunctions.cpp

HEADERS +=\
	TFV_Classes.h \
	TFV_Classes.h \
	TFV_CustomClassSort.h \
	TFV_LabelFunctions.h \
	TFV_PopulatingFunctions.h \
	TFV_Viewer.h \
    alphanum.hpp \
    MainClass.h \


FORMS += \

LIBS += -lstdc++fs

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    PseudoFeb \
    pseudo_code
