/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *applyButton;
    QLabel *filterLabel;
    QComboBox *filterComboBox;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *resetButton;
    QGridLayout *imagesGrid;
    QLabel *originalImageLabel;
    QLabel *filteredImageLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        applyButton = new QPushButton(centralwidget);
        applyButton->setObjectName("applyButton");

        gridLayout->addWidget(applyButton, 1, 2, 1, 1);

        filterLabel = new QLabel(centralwidget);
        filterLabel->setObjectName("filterLabel");

        gridLayout->addWidget(filterLabel, 1, 0, 1, 1);

        filterComboBox = new QComboBox(centralwidget);
        filterComboBox->addItem(QString());
        filterComboBox->addItem(QString());
        filterComboBox->addItem(QString());
        filterComboBox->addItem(QString());
        filterComboBox->addItem(QString());
        filterComboBox->addItem(QString());
        filterComboBox->addItem(QString());
        filterComboBox->addItem(QString());
        filterComboBox->addItem(QString());
        filterComboBox->setObjectName("filterComboBox");
        filterComboBox->setEditable(false);

        gridLayout->addWidget(filterComboBox, 1, 1, 1, 1);

        loadButton = new QPushButton(centralwidget);
        loadButton->setObjectName("loadButton");

        gridLayout->addWidget(loadButton, 0, 0, 1, 1);

        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName("saveButton");

        gridLayout->addWidget(saveButton, 0, 1, 1, 1);

        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName("resetButton");

        gridLayout->addWidget(resetButton, 0, 2, 1, 1);

        imagesGrid = new QGridLayout();
        imagesGrid->setObjectName("imagesGrid");
        originalImageLabel = new QLabel(centralwidget);
        originalImageLabel->setObjectName("originalImageLabel");

        imagesGrid->addWidget(originalImageLabel, 0, 0, 1, 1);

        filteredImageLabel = new QLabel(centralwidget);
        filteredImageLabel->setObjectName("filteredImageLabel");

        imagesGrid->addWidget(filteredImageLabel, 0, 1, 1, 1);


        gridLayout->addLayout(imagesGrid, 3, 0, 1, 3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Image Filter App", nullptr));
        applyButton->setText(QCoreApplication::translate("MainWindow", "Apply Filter", nullptr));
        filterLabel->setText(QCoreApplication::translate("MainWindow", "Select Filter:", nullptr));
        filterComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Inversion", nullptr));
        filterComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Brightness Correction", nullptr));
        filterComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Contrast Enhancement", nullptr));
        filterComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Gamma Correction", nullptr));
        filterComboBox->setItemText(4, QCoreApplication::translate("MainWindow", "Blur", nullptr));
        filterComboBox->setItemText(5, QCoreApplication::translate("MainWindow", "Gaussian Blur", nullptr));
        filterComboBox->setItemText(6, QCoreApplication::translate("MainWindow", "Sharpen", nullptr));
        filterComboBox->setItemText(7, QCoreApplication::translate("MainWindow", "Edge Detection", nullptr));
        filterComboBox->setItemText(8, QCoreApplication::translate("MainWindow", "Emboss", nullptr));

        loadButton->setText(QCoreApplication::translate("MainWindow", "Load Image", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Save Image", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "Reset Image", nullptr));
        originalImageLabel->setText(QString());
        filteredImageLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
