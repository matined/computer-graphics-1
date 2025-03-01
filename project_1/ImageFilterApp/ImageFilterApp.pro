QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    gui/mainwindow.cpp \
    gui/filtereditorwidget.cpp \
    filters/functional_filters.cpp \
    filters/convolution_filters.cpp \
    filters/custom_filter.cpp

HEADERS += \
    gui/mainwindow.h \
    gui/filtereditorwidget.h \
    filters/functional_filters.h \
    filters/convolution_filters.h \
    filters/custom_filter.h

FORMS += \
    gui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
