#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filtereditorwidget.h"
#include "../filters/functional_filters.h"
#include "../filters/convolution_filters.h"
#include "../filters/custom_filter.h"
#include <QFileDialog>
#include <QPixmap>
#include <QFileInfo>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    qDebug() << "MainWindow constructor started";
    
    // Connect the filter editor's filterChanged signal to our slot
    connect(ui->filterEditorWidget, &FilterEditorWidget::filterChanged, this, &MainWindow::onFilterChanged);
    
    qDebug() << "Connected filter editor signals";
    
    // Make sure the filter editor widget is ready
    ui->filterEditorWidget->resetToIdentity();
    
    // Initialize filter editor combo box
    updateFilterEditorComboBox();
    
    // Set initial custom filter as Identity
    currentCustomFilter = CustomFilterManager::instance().getFilter("Identity");
    ui->filterEditorWidget->setPoints(currentCustomFilter.getPoints());
    
    qDebug() << "Initial filter set to Identity";
    
    // Update display
    ui->filterEditorWidget->update();
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
    ui->originalImageLabel->setPixmap(originalPixmap);
    
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
    else {
        // Check if it's a custom filter
        if (CustomFilterManager::instance().hasFilter(selectedFilter)) {
            CustomFilter filter = CustomFilterManager::instance().getFilter(selectedFilter);
            filter.apply(filteredImage);
        }
    }

    // Update the display with the filtered image
    updateFilteredImage();
}

void MainWindow::updateFilteredImage()
{
    // Display the filtered image in the filteredImageLabel
    QPixmap filteredPixmap = QPixmap::fromImage(filteredImage);
    ui->filteredImageLabel->setPixmap(filteredPixmap);
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

// Filter Editor functions

void MainWindow::updateFilterEditorComboBox()
{
    qDebug() << "Updating filter editor combo box";
    
    // Block signals during update
    ui->filterEditorSelection->blockSignals(true);
    
    // Save current selection if any
    QString currentSelection = ui->filterEditorSelection->currentText();
    qDebug() << "Current selection before update:" << currentSelection;
    
    // Clear and repopulate the combo box
    ui->filterEditorSelection->clear();
    
    // Add predefined filters
    ui->filterEditorSelection->addItem("Identity");
    ui->filterEditorSelection->addItem("Inversion");
    ui->filterEditorSelection->addItem("Brightness Correction");
    ui->filterEditorSelection->addItem("Contrast Enhancement");
    
    // Add custom filters from the filter manager
    QStringList customFilters = CustomFilterManager::instance().getFilterNames();
    for (const QString& filterName : customFilters) {
        // Skip predefined filters that are already added
        if (filterName != "Identity" && filterName != "Inversion" && 
            filterName != "Brightness Correction" && filterName != "Contrast Enhancement") {
            ui->filterEditorSelection->addItem(filterName);
        }
    }
    
    // Restore previous selection if it exists
    int index = -1;
    if (!currentSelection.isEmpty()) {
        index = ui->filterEditorSelection->findText(currentSelection);
        if (index >= 0) {
            ui->filterEditorSelection->setCurrentIndex(index);
        }
    }
    
    // Unblock signals
    ui->filterEditorSelection->blockSignals(false);
    
    // If no previous selection was restored, manually trigger the first item
    if (index < 0 && ui->filterEditorSelection->count() > 0) {
        QString firstItem = ui->filterEditorSelection->itemText(0);
        qDebug() << "No previous selection, triggering first item:" << firstItem;
        on_filterEditorSelection_currentIndexChanged(firstItem);
    } else {
        qDebug() << "Previous selection restored:" << currentSelection;
        // Also manually trigger the selection change to ensure the filter is updated
        on_filterEditorSelection_currentIndexChanged(currentSelection);
    }
    
    // Also update the main filter combo box to include custom filters
    ui->filterComboBox->blockSignals(true);
    
    // Save current selection
    currentSelection = ui->filterComboBox->currentText();
    
    // Clear and repopulate with standard filters
    ui->filterComboBox->clear();
    ui->filterComboBox->addItem("Inversion");
    ui->filterComboBox->addItem("Brightness Correction");
    ui->filterComboBox->addItem("Contrast Enhancement");
    ui->filterComboBox->addItem("Gamma Correction");
    ui->filterComboBox->addItem("Blur");
    ui->filterComboBox->addItem("Gaussian Blur");
    ui->filterComboBox->addItem("Sharpen");
    ui->filterComboBox->addItem("Edge Detection");
    ui->filterComboBox->addItem("Emboss");
    
    // Add custom filters at the end
    for (const QString& filterName : customFilters) {
        // Skip predefined filters that are already in the standard list
        if (filterName != "Identity" && filterName != "Inversion" && 
            filterName != "Brightness Correction" && filterName != "Contrast Enhancement") {
            ui->filterComboBox->addItem(filterName);
        }
    }
    
    // Restore previous selection if it exists
    if (!currentSelection.isEmpty()) {
        int index = ui->filterComboBox->findText(currentSelection);
        if (index >= 0) {
            ui->filterComboBox->setCurrentIndex(index);
        }
    }
    
    ui->filterComboBox->blockSignals(false);
}

void MainWindow::on_filterEditorSelection_currentIndexChanged(const QString &filterName)
{
    qDebug() << "Filter selected:" << filterName;
    
    if (filterName == "Identity") {
        // Load identity filter
        qDebug() << "Loading Identity filter";
        ui->filterEditorWidget->resetToIdentity();
        currentCustomFilter = CustomFilter("Identity", ui->filterEditorWidget->getPoints());
    } else if (filterName == "Inversion") {
        // Load inversion filter
        qDebug() << "Loading Inversion filter";
        ui->filterEditorWidget->loadInversion();
        currentCustomFilter = CustomFilter("Inversion", ui->filterEditorWidget->getPoints());
    } else if (filterName == "Brightness Correction") {
        // Load brightness filter
        qDebug() << "Loading Brightness filter";
        ui->filterEditorWidget->loadBrightness();
        currentCustomFilter = CustomFilter("Brightness Correction", ui->filterEditorWidget->getPoints());
    } else if (filterName == "Contrast Enhancement") {
        // Load contrast filter
        qDebug() << "Loading Contrast filter";
        ui->filterEditorWidget->loadContrast();
        currentCustomFilter = CustomFilter("Contrast Enhancement", ui->filterEditorWidget->getPoints());
    } else if (CustomFilterManager::instance().hasFilter(filterName)) {
        // Load custom filter
        qDebug() << "Loading custom filter:" << filterName;
        currentCustomFilter = CustomFilterManager::instance().getFilter(filterName);
        ui->filterEditorWidget->setPoints(currentCustomFilter.getPoints());
    }
    
    // Make sure the widget is updated
    ui->filterEditorWidget->update();
}

void MainWindow::on_addPoint_clicked()
{
    // Add a new point to the filter editor
    ui->filterEditorWidget->addPoint();
}

void MainWindow::on_removePoint_clicked()
{
    // Remove the selected point from the filter editor
    ui->filterEditorWidget->removeSelectedPoint();
}

void MainWindow::on_resetPoints_clicked()
{
    // Reset the current filter to identity
    ui->filterEditorWidget->resetToIdentity();
}

void MainWindow::on_saveCustomFilter_clicked()
{
    // Get current filter name from selection
    QString currentName = ui->filterEditorSelection->currentText();
    
    // Don't allow modifying predefined filters
    if (currentName == "Identity" || currentName == "Brightness Correction" || 
        currentName == "Contrast Enhancement") {
        
        // Prompt for a new name
        bool ok;
        QString newName = QInputDialog::getText(this, "Save Custom Filter", 
                                                "Enter a name for the custom filter:", 
                                                QLineEdit::Normal, "Custom Filter", &ok);
        
        if (ok && !newName.isEmpty()) {
            // Create new filter with the current points
            currentCustomFilter = CustomFilter(newName, ui->filterEditorWidget->getPoints());
            CustomFilterManager::instance().addFilter(currentCustomFilter);
            
            // Update the comboboxes
            updateFilterEditorComboBox();
            
            // Select the new filter in the combobox
            int index = ui->filterEditorSelection->findText(newName);
            if (index >= 0) {
                ui->filterEditorSelection->setCurrentIndex(index);
            }
        }
    } else {
        // Update the existing filter
        currentCustomFilter.setPoints(ui->filterEditorWidget->getPoints());
        CustomFilterManager::instance().addFilter(currentCustomFilter);
        
        QMessageBox::information(this, "Filter Saved", 
                                "The filter '" + currentName + "' has been updated.");
    }
}

void MainWindow::on_applyCustomFilter_clicked()
{
    // Apply the current custom filter to the image
    applyCustomFilterToImage();
}

void MainWindow::onFilterChanged()
{
    // Update the current custom filter when the filter editor points change
    currentCustomFilter.setPoints(ui->filterEditorWidget->getPoints());
}

void MainWindow::applyCustomFilterToImage()
{
    // Check if an image is loaded
    if (originalImage.isNull()) {
        QMessageBox::warning(this, tr("No Image"), tr("Please load an image first."));
        return;
    }
    
    // Apply the current custom filter to the image
    filteredImage = originalImage.copy();
    currentCustomFilter.apply(filteredImage);
    
    // Update the display
    updateFilteredImage();
}

void MainWindow::on_applyDithering_clicked()
{
    // Check if an image is loaded
    if (originalImage.isNull()) {
        QMessageBox::warning(this, tr("No Image"), tr("Please load an image first."));
        return;
    }
    
    // Reset filteredImage to originalImage to remove any previously applied filters
    filteredImage = originalImage.copy();
    
    // Get the number of colors for each channel from spin boxes
    int redColors = ui->ditheringRedColorsSpinBox->value();
    int greenColors = ui->ditheringGreenColorsSpinBox->value();
    int blueColors = ui->ditheringBlueColorsSpinBox->value();
    
    // Apply the random dithering filter
    Filters::applyRandomDitheringFilter(filteredImage, redColors, greenColors, blueColors);
    
    // Update the display with the filtered image
    updateFilteredImage();
}
