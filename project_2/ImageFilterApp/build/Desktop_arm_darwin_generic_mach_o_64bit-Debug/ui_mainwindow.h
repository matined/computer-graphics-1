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
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "gui/filtereditorwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_2;
    QComboBox *filterEditorSelection;
    QPushButton *addPoint;
    QPushButton *removePoint;
    QPushButton *resetPoints;
    QPushButton *saveCustomFilter;
    QPushButton *applyCustomFilter;
    QLabel *label;
    FilterEditorWidget *filterEditorWidget;
    QGridLayout *imagesGrid;
    QLabel *label_3;
    QPushButton *applyButton;
    QLabel *label_2;
    QLabel *filteredImageLabel;
    QComboBox *filterComboBox;
    QLabel *originalImageLabel;
    QPushButton *loadButton;
    QPushButton *resetButton;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_3;
    QSpinBox *ditheringRedColorsSpinBox;
    QSpinBox *ditheringGreenColorsSpinBox;
    QSpinBox *ditheringBlueColorsSpinBox;
    QLabel *label_4;
    QPushButton *applyDithering;
    QPushButton *applyQuantization;
    QSpinBox *quantizationMaximumColors;
    QLabel *label_5;
    QPushButton *convertToGreyscale;
    QPushButton *saveButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(842, 870);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMaximumSize(QSize(842, 870));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName("gridLayout_4");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        filterEditorSelection = new QComboBox(centralwidget);
        filterEditorSelection->addItem(QString());
        filterEditorSelection->addItem(QString());
        filterEditorSelection->addItem(QString());
        filterEditorSelection->setObjectName("filterEditorSelection");

        verticalLayout_2->addWidget(filterEditorSelection);

        addPoint = new QPushButton(centralwidget);
        addPoint->setObjectName("addPoint");

        verticalLayout_2->addWidget(addPoint);

        removePoint = new QPushButton(centralwidget);
        removePoint->setObjectName("removePoint");

        verticalLayout_2->addWidget(removePoint);

        resetPoints = new QPushButton(centralwidget);
        resetPoints->setObjectName("resetPoints");

        verticalLayout_2->addWidget(resetPoints);

        saveCustomFilter = new QPushButton(centralwidget);
        saveCustomFilter->setObjectName("saveCustomFilter");

        verticalLayout_2->addWidget(saveCustomFilter);

        applyCustomFilter = new QPushButton(centralwidget);
        applyCustomFilter->setObjectName("applyCustomFilter");

        verticalLayout_2->addWidget(applyCustomFilter);

        label = new QLabel(centralwidget);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);


        gridLayout_4->addLayout(verticalLayout_2, 1, 1, 1, 1);

        filterEditorWidget = new FilterEditorWidget(centralwidget);
        filterEditorWidget->setObjectName("filterEditorWidget");
        filterEditorWidget->setMinimumSize(QSize(256, 256));
        filterEditorWidget->setMaximumSize(QSize(256, 256));

        gridLayout_4->addWidget(filterEditorWidget, 1, 0, 1, 1);


        gridLayout->addLayout(gridLayout_4, 4, 0, 1, 3);

        imagesGrid = new QGridLayout();
        imagesGrid->setObjectName("imagesGrid");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        imagesGrid->addWidget(label_3, 1, 1, 1, 1);

        applyButton = new QPushButton(centralwidget);
        applyButton->setObjectName("applyButton");

        imagesGrid->addWidget(applyButton, 0, 1, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        imagesGrid->addWidget(label_2, 1, 0, 1, 1);

        filteredImageLabel = new QLabel(centralwidget);
        filteredImageLabel->setObjectName("filteredImageLabel");

        imagesGrid->addWidget(filteredImageLabel, 2, 1, 1, 1);

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

        imagesGrid->addWidget(filterComboBox, 0, 0, 1, 1);

        originalImageLabel = new QLabel(centralwidget);
        originalImageLabel->setObjectName("originalImageLabel");

        imagesGrid->addWidget(originalImageLabel, 2, 0, 1, 1);


        gridLayout->addLayout(imagesGrid, 3, 0, 1, 3);

        loadButton = new QPushButton(centralwidget);
        loadButton->setObjectName("loadButton");

        gridLayout->addWidget(loadButton, 0, 0, 1, 1);

        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName("resetButton");

        gridLayout->addWidget(resetButton, 0, 2, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        ditheringRedColorsSpinBox = new QSpinBox(centralwidget);
        ditheringRedColorsSpinBox->setObjectName("ditheringRedColorsSpinBox");
        ditheringRedColorsSpinBox->setMinimum(2);

        gridLayout_3->addWidget(ditheringRedColorsSpinBox, 0, 1, 1, 1);

        ditheringGreenColorsSpinBox = new QSpinBox(centralwidget);
        ditheringGreenColorsSpinBox->setObjectName("ditheringGreenColorsSpinBox");
        ditheringGreenColorsSpinBox->setMinimum(2);

        gridLayout_3->addWidget(ditheringGreenColorsSpinBox, 0, 2, 1, 1);

        ditheringBlueColorsSpinBox = new QSpinBox(centralwidget);
        ditheringBlueColorsSpinBox->setObjectName("ditheringBlueColorsSpinBox");
        ditheringBlueColorsSpinBox->setMinimum(2);

        gridLayout_3->addWidget(ditheringBlueColorsSpinBox, 0, 3, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        gridLayout_3->addWidget(label_4, 0, 0, 1, 1);

        applyDithering = new QPushButton(centralwidget);
        applyDithering->setObjectName("applyDithering");

        gridLayout_3->addWidget(applyDithering, 0, 4, 1, 1);

        applyQuantization = new QPushButton(centralwidget);
        applyQuantization->setObjectName("applyQuantization");

        gridLayout_3->addWidget(applyQuantization, 1, 4, 1, 1);

        quantizationMaximumColors = new QSpinBox(centralwidget);
        quantizationMaximumColors->setObjectName("quantizationMaximumColors");
        quantizationMaximumColors->setMinimum(2);
        quantizationMaximumColors->setMaximum(10000);

        gridLayout_3->addWidget(quantizationMaximumColors, 1, 3, 1, 1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");

        gridLayout_3->addWidget(label_5, 1, 2, 1, 1);

        convertToGreyscale = new QPushButton(centralwidget);
        convertToGreyscale->setObjectName("convertToGreyscale");

        gridLayout_3->addWidget(convertToGreyscale, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout_3, 3, 1, 1, 1);


        gridLayout->addLayout(gridLayout_2, 5, 0, 1, 3);

        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName("saveButton");

        gridLayout->addWidget(saveButton, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 842, 38));
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
        filterEditorSelection->setItemText(0, QCoreApplication::translate("MainWindow", "Inversion", nullptr));
        filterEditorSelection->setItemText(1, QCoreApplication::translate("MainWindow", "Brightness Correction", nullptr));
        filterEditorSelection->setItemText(2, QCoreApplication::translate("MainWindow", "Contrast Enhancement", nullptr));

        addPoint->setText(QCoreApplication::translate("MainWindow", "Add Point", nullptr));
        removePoint->setText(QCoreApplication::translate("MainWindow", "Remove Point", nullptr));
        resetPoints->setText(QCoreApplication::translate("MainWindow", "Reset Points", nullptr));
        saveCustomFilter->setText(QCoreApplication::translate("MainWindow", "Save Filter", nullptr));
        applyCustomFilter->setText(QCoreApplication::translate("MainWindow", "Apply to Image", nullptr));
        label->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "Filtered Image", nullptr));
        applyButton->setText(QCoreApplication::translate("MainWindow", "Apply Filter", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Original Image", nullptr));
        filteredImageLabel->setText(QString());
        filterComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Inversion", nullptr));
        filterComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Brightness Correction", nullptr));
        filterComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Contrast Enhancement", nullptr));
        filterComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Gamma Correction", nullptr));
        filterComboBox->setItemText(4, QCoreApplication::translate("MainWindow", "Blur", nullptr));
        filterComboBox->setItemText(5, QCoreApplication::translate("MainWindow", "Gaussian Blur", nullptr));
        filterComboBox->setItemText(6, QCoreApplication::translate("MainWindow", "Sharpen", nullptr));
        filterComboBox->setItemText(7, QCoreApplication::translate("MainWindow", "Edge Detection", nullptr));
        filterComboBox->setItemText(8, QCoreApplication::translate("MainWindow", "Emboss", nullptr));

        originalImageLabel->setText(QString());
        loadButton->setText(QCoreApplication::translate("MainWindow", "Load Image", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "Reset Image", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Colors per RGB channel:", nullptr));
        applyDithering->setText(QCoreApplication::translate("MainWindow", "Apply Dithering", nullptr));
        applyQuantization->setText(QCoreApplication::translate("MainWindow", "Apply Quantization", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Maximum number of colors:", nullptr));
        convertToGreyscale->setText(QCoreApplication::translate("MainWindow", "Convert to Greyscale", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Save Image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
