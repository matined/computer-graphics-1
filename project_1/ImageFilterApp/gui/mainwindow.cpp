#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../filters/functional_filters.h"
#include "../filters/convolution_filters.h"
#include <QFileDialog>
#include <QPixmap>
#include <QFileInfo>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
    // Open file dialog to select an image
    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Open Image"),
        QString(),
        tr("Image Files (*.png *.jpg *.jpeg *.bmp *.gif)")
    );

    // If user cancels the dialog, filePath will be empty
    if (filePath.isEmpty()) {
        return;
    }

    // Load the image into originalImage
    originalImage = QImage(filePath);
    
    // Check if image loaded successfully
    if (originalImage.isNull()) {
        return;
    }

    // Create a copy for the filtered image
    filteredImage = originalImage.copy();

    // Display original image in the originalImageLabel
    QPixmap originalPixmap = QPixmap::fromImage(originalImage);
    ui->originalImageLabel->setPixmap(originalPixmap.scaled(
        ui->originalImageLabel->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
    ));
    
    // Display the copy in the filteredImageLabel
    updateFilteredImage();
    
    // Make sure the labels adjust their size policy to properly display the images
    ui->originalImageLabel->setScaledContents(false);
    ui->filteredImageLabel->setScaledContents(false);
}

void MainWindow::on_saveButton_clicked()
{
    // Check if there's an image to save
    if (filteredImage.isNull()) return;

    // Open file dialog to select save location and format
    QString filePath = QFileDialog::getSaveFileName(
        this,
        tr("Save Image"),
        QString(),
        tr("PNG (*.png);;JPEG (*.jpg *.jpeg);;BMP (*.bmp);;All Files (*)")
    );

    // If user cancels the dialog, filePath will be empty
    if (filePath.isEmpty()) {
        return;
    }

    // Make sure the file has an extension
    QFileInfo fileInfo(filePath);
    if (fileInfo.suffix().isEmpty()) {
        // No extension provided, default to PNG
        filePath += ".png";
    }

    // Save the filtered image
    filteredImage.save(filePath);
}

void MainWindow::on_applyButton_clicked()
{
    // Check if an image is loaded
    if (originalImage.isNull()) {
        QMessageBox::warning(this, tr("No Image"), tr("Please load an image first."));
        return;
    }

    // Reset filteredImage to originalImage to remove any previously applied filters
    filteredImage = originalImage.copy();

    // Get the selected filter from the combo box
    QString selectedFilter = ui->filterComboBox->currentText();

    // Apply the selected filter
    if (selectedFilter == "Inversion")
        Filters::applyInversionFilter(filteredImage);
    else if (selectedFilter == "Brightness Correction")
        Filters::applyBrightnessFilter(filteredImage);
    else if (selectedFilter == "Contrast Enhancement")
        Filters::applyContrastFilter(filteredImage);
    else if (selectedFilter == "Gamma Correction")
        Filters::applyGammaFilter(filteredImage);
    else if (selectedFilter == "Blur")
        ConvolutionFilters::applyBlurFilter(filteredImage);
    else if (selectedFilter == "Gaussian Blur")
        ConvolutionFilters::applyGaussianBlurFilter(filteredImage);
    else if (selectedFilter == "Sharpen")
        ConvolutionFilters::applySharpenFilter(filteredImage);
    else if (selectedFilter == "Edge Detection")
        ConvolutionFilters::applyEdgeFilter(filteredImage);
    else if (selectedFilter == "Emboss")
        ConvolutionFilters::applyEmbossFilter(filteredImage);
    // Add more filter options here with else if statements

    // Update the display with the filtered image
    updateFilteredImage();
}

void MainWindow::updateFilteredImage()
{
    // Display the filtered image in the filteredImageLabel
    QPixmap filteredPixmap = QPixmap::fromImage(filteredImage);
    ui->filteredImageLabel->setPixmap(filteredPixmap.scaled(
        ui->filteredImageLabel->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
    ));
}

void MainWindow::on_resetButton_clicked()
{
    // Check if there's an original image to reset to
    if (originalImage.isNull()) {
        QMessageBox::warning(this, tr("No Image"), tr("Please load an image first."));
        return;
    }

    // Reset filteredImage to originalImage
    filteredImage = originalImage.copy();
    
    // Update the display with the reset image
    updateFilteredImage();
}
