#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>

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

private:
    Ui::MainWindow *ui;
    QImage originalImage;
    QImage filteredImage;
    
    // Updates the filteredImageLabel with the current filteredImage
    void updateFilteredImage();
};
#endif // MAINWINDOW_H
