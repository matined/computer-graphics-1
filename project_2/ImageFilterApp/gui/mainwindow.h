#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QInputDialog>
#include "../filters/custom_filter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadButton_clicked();
    void on_saveButton_clicked();
    void on_applyButton_clicked();
    void on_resetButton_clicked();
    
    // Filter editor slots
    void on_filterEditorSelection_currentIndexChanged(const QString &filterName);
    void on_addPoint_clicked();
    void on_removePoint_clicked();
    void on_resetPoints_clicked();
    void on_saveCustomFilter_clicked();
    void on_applyCustomFilter_clicked();
    void onFilterChanged();
    
    // Dithering slots
    void on_applyDithering_clicked();
    
private:
    Ui::MainWindow *ui;
    QImage originalImage;
    QImage filteredImage;
    CustomFilter currentCustomFilter;
    
    // Updates the filteredImageLabel with the current filteredImage
    void updateFilteredImage();
    
    // Updates the filter editor combo box with available filters
    void updateFilterEditorComboBox();
    
    // Apply the current custom filter to the image
    void applyCustomFilterToImage();
};
#endif // MAINWINDOW_H
