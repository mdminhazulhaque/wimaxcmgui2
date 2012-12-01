QT       += core gui

TARGET = wimaxcmgui2

TEMPLATE = app

SOURCES +=\
        window.cpp \
    settingsdialog.cpp \
    aboutdialog.cpp \
    accountsdialog.cpp \
    scheduledialog.cpp \
    wimaxcmgui2.cpp \
    wcmtimer.cpp \
    keyboarddialog.cpp

HEADERS  += window.hpp \
    settingsdialog.hpp \
    aboutdialog.hpp \
    accountsdialog.hpp \
    scheduledialog.hpp \
    wcmtimer.hpp \
    keyboarddialog.hpp \
    wcmread.hpp \
    defines.hpp

FORMS    += window.ui \
    settingsdialog.ui \
    aboutdialog.ui \
    accountsdialog.ui \
    scheduledialog.ui \
    keyboarddialog.ui

RESOURCES += \
    icons.qrc