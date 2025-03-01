#ifndef FILTEREDITORWIDGET_H
#define FILTEREDITORWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QPainterPath>

class FilterEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FilterEditorWidget(QWidget *parent = nullptr);
    
    // Reset to identity filter (straight line from bottom-left to top-right)
    void resetToIdentity();
    
    // Load points from predefined filters
    void loadInversion();
    void loadBrightness(int brightness = 100);
    void loadContrast(double contrast = 1.5);
    
    // Get current filter lookup table
    QVector<int> getFilterLUT() const;
    
    // Set the current points from an existing filter
    void setPoints(const QVector<QPointF>& newPoints);
    
    // Get the current points
    QVector<QPointF> getPoints() const;

signals:
    void pointSelected(int index, int x, int y);
    void filterChanged();

public slots:
    void addPoint();
    void removeSelectedPoint();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QVector<QPointF> points; // Points defining the filter curve
    int selectedPoint;       // Index of selected point (-1 if none)
    bool isDragging;         // Whether a point is being dragged
    
    // Convert from widget coordinates to filter coordinates (0-255)
    QPointF widgetToFilter(const QPointF& point) const;
    
    // Convert from filter coordinates to widget coordinates
    QPointF filterToWidget(const QPointF& point) const;
    
    // Sort points by x-coordinate to ensure a valid function
    void sortPoints();
    
    // Find the closest point to a given position
    int findClosestPoint(const QPointF& pos, double& distance);
    
    // Draw axes and grid
    void drawAxes(QPainter& painter);
    
    // Draw the filter curve
    void drawCurve(QPainter& painter);
};

#endif // FILTEREDITORWIDGET_H 