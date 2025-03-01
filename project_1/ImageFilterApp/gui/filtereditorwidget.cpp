#include "filtereditorwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <algorithm>
#include <cmath>

// Maximum distance to select a point
const double MAX_SELECT_DISTANCE = 10.0;

FilterEditorWidget::FilterEditorWidget(QWidget *parent) 
    : QWidget(parent), selectedPoint(-1), isDragging(false)
{
    // Set default size
    setMinimumSize(256, 256);
    setMaximumSize(256, 256);
    
    // Set focus policy to enable key events
    setFocusPolicy(Qt::StrongFocus);
    
    // Initialize with identity filter
    resetToIdentity();
}

void FilterEditorWidget::resetToIdentity() 
{
    // Identity filter is a straight line from (0,0) to (255,255)
    points.clear();
    points.append(QPointF(0, 0));     // Bottom-left
    points.append(QPointF(255, 255)); // Top-right
    
    selectedPoint = -1;
    update();
    emit filterChanged();
}

void FilterEditorWidget::loadInversion() 
{
    // Inversion filter is a straight line from (0,255) to (255,0)
    points.clear();
    points.append(QPointF(0, 255));   // Top-left
    points.append(QPointF(255, 0));   // Bottom-right
    
    selectedPoint = -1;
    update();
    emit filterChanged();
}

void FilterEditorWidget::loadBrightness(int brightness) 
{
    // Brightness filter is a line parallel to identity but shifted up/down
    points.clear();
    
    // Clamp brightness value between -255 and 255
    brightness = std::max(-255, std::min(brightness, 255));
    
    points.append(QPointF(0, std::max(0, std::min(255, brightness))));
    points.append(QPointF(255, std::max(0, std::min(255, 255 + brightness))));
    
    selectedPoint = -1;
    update();
    emit filterChanged();
}

void FilterEditorWidget::loadContrast(double contrast) 
{
    // Contrast filter is a line with increased/decreased slope through the midpoint
    points.clear();
    
    // Clamp contrast value
    contrast = std::max(0.0, std::min(contrast, 3.0));
    
    // The midpoint is (128, 128)
    int midpoint = 128;
    
    // Calculate contrast adjusted endpoints
    int y0 = std::max(0, std::min(255, static_cast<int>(midpoint - contrast * midpoint)));
    int y1 = std::max(0, std::min(255, static_cast<int>(midpoint + contrast * (255 - midpoint))));
    
    points.append(QPointF(0, y0));
    points.append(QPointF(255, y1));
    
    selectedPoint = -1;
    update();
    emit filterChanged();
}

QVector<int> FilterEditorWidget::getFilterLUT() const 
{
    // Create a lookup table for the filter
    QVector<int> lut(256);
    
    if (points.size() < 2) {
        // If not enough points, return identity LUT
        for (int i = 0; i < 256; i++) {
            lut[i] = i;
        }
        return lut;
    }
    
    // Sort points by x-coordinate
    QVector<QPointF> sortedPoints = points;
    std::sort(sortedPoints.begin(), sortedPoints.end(), 
        [](const QPointF& a, const QPointF& b) { return a.x() < b.x(); });
    
    // For each input value, calculate the output value by linear interpolation
    for (int x = 0; x < 256; x++) {
        // Find the points to interpolate between
        int i = 0;
        while (i < sortedPoints.size() - 1 && sortedPoints[i + 1].x() < x) {
            i++;
        }
        
        if (i >= sortedPoints.size() - 1) {
            // Use the last point if x is beyond the range
            lut[x] = std::max(0, std::min(255, static_cast<int>(sortedPoints.last().y())));
        } else if (sortedPoints[i].x() > x) {
            // Use the first point if x is before the range
            lut[x] = std::max(0, std::min(255, static_cast<int>(sortedPoints.first().y())));
        } else {
            // Linear interpolation between points i and i+1
            double x0 = sortedPoints[i].x();
            double y0 = sortedPoints[i].y();
            double x1 = sortedPoints[i + 1].x();
            double y1 = sortedPoints[i + 1].y();
            
            // Interpolation formula: y = y0 + (x - x0) * (y1 - y0) / (x1 - x0)
            double t = (x - x0) / (x1 - x0);
            double y = y0 + t * (y1 - y0);
            
            lut[x] = std::max(0, std::min(255, static_cast<int>(std::round(y))));
        }
    }
    
    return lut;
}

void FilterEditorWidget::setPoints(const QVector<QPointF>& newPoints) 
{
    if (newPoints.size() >= 2) {
        points = newPoints;
        sortPoints();
        selectedPoint = -1;
        update();
        emit filterChanged();
    }
}

QVector<QPointF> FilterEditorWidget::getPoints() const 
{
    return points;
}

void FilterEditorWidget::addPoint() 
{
    if (points.size() < 2) {
        // If there are fewer than 2 points, reset to identity
        resetToIdentity();
        return;
    }
    
    // Add a point in the middle of the curve
    double midX = (points.first().x() + points.last().x()) / 2;
    
    // Find points to interpolate between
    QVector<QPointF> sortedPoints = points;
    std::sort(sortedPoints.begin(), sortedPoints.end(), 
        [](const QPointF& a, const QPointF& b) { return a.x() < b.x(); });
    
    // Find the position to insert
    int pos = 0;
    while (pos < sortedPoints.size() && sortedPoints[pos].x() < midX) {
        pos++;
    }
    
    // Interpolate y value
    double y;
    if (pos == 0) {
        y = sortedPoints[0].y();
    } else if (pos >= sortedPoints.size()) {
        y = sortedPoints.last().y();
    } else {
        double x0 = sortedPoints[pos - 1].x();
        double y0 = sortedPoints[pos - 1].y();
        double x1 = sortedPoints[pos].x();
        double y1 = sortedPoints[pos].y();
        
        double t = (midX - x0) / (x1 - x0);
        y = y0 + t * (y1 - y0);
    }
    
    // Add the new point
    points.append(QPointF(midX, y));
    sortPoints();
    
    // Select the new point
    selectedPoint = points.indexOf(QPointF(midX, y));
    update();
    emit filterChanged();
}

void FilterEditorWidget::removeSelectedPoint() 
{
    if (selectedPoint >= 0 && selectedPoint < points.size()) {
        // Cannot remove the first or last point
        if (selectedPoint == 0 || selectedPoint == points.size() - 1) {
            return;
        }
        
        points.remove(selectedPoint);
        selectedPoint = -1;
        update();
        emit filterChanged();
    }
}

void FilterEditorWidget::paintEvent(QPaintEvent* event) 
{
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Fill background
    painter.fillRect(rect(), Qt::white);
    
    // Draw axes and grid
    drawAxes(painter);
    
    // Draw curve
    drawCurve(painter);
}

void FilterEditorWidget::mousePressEvent(QMouseEvent* event) 
{
    if (event->button() == Qt::LeftButton) {
        QPointF pos = event->pos();
        double distance;
        int index = findClosestPoint(pos, distance);
        
        if (distance < MAX_SELECT_DISTANCE) {
            selectedPoint = index;
            isDragging = true;
            
            // Emit signal with selected point info
            QPointF filterPos = widgetToFilter(pos);
            emit pointSelected(index, static_cast<int>(filterPos.x()), static_cast<int>(filterPos.y()));
            
            update();
        } else {
            selectedPoint = -1;
            update();
        }
    }
}

void FilterEditorWidget::mouseMoveEvent(QMouseEvent* event) 
{
    if (isDragging && selectedPoint >= 0 && selectedPoint < points.size()) {
        QPointF pos = event->pos();
        QPointF filterPos = widgetToFilter(pos);
        
        // Constrain y to 0-255 range
        filterPos.setY(std::max(0.0, std::min(255.0, filterPos.y())));
        
        // If it's first or last point, only allow vertical movement
        if (selectedPoint == 0 || selectedPoint == points.size() - 1) {
            filterPos.setX(points[selectedPoint].x());
        } else {
            // Constrain x to be between adjacent points to maintain a valid function
            double minX = (selectedPoint > 0) ? points[selectedPoint - 1].x() + 1 : 0;
            double maxX = (selectedPoint < points.size() - 1) ? points[selectedPoint + 1].x() - 1 : 255;
            
            filterPos.setX(std::max(minX, std::min(maxX, filterPos.x())));
        }
        
        points[selectedPoint] = filterPos;
        
        // Emit signal with updated point info
        emit pointSelected(selectedPoint, static_cast<int>(filterPos.x()), static_cast<int>(filterPos.y()));
        
        update();
        emit filterChanged();
    }
}

void FilterEditorWidget::mouseReleaseEvent(QMouseEvent* event) 
{
    if (event->button() == Qt::LeftButton && isDragging) {
        isDragging = false;
        
        // Sort points after dragging to maintain order
        if (selectedPoint > 0 && selectedPoint < points.size() - 1) {
            sortPoints();
            
            // Update selected point index after sorting
            if (selectedPoint >= 0 && selectedPoint < points.size()) {
                QPointF currentPoint = points[selectedPoint];
                
                // Find the new index of the selected point
                for (int i = 0; i < points.size(); i++) {
                    if (points[i] == currentPoint) {
                        selectedPoint = i;
                        break;
                    }
                }
            }
        }
        
        update();
    }
}

QPointF FilterEditorWidget::widgetToFilter(const QPointF& point) const 
{
    // Convert from widget coordinates to filter coordinates (0-255)
    double x = (point.x() / width()) * 255.0;
    double y = 255.0 - (point.y() / height()) * 255.0; // Invert Y since widget Y increases downward
    
    return QPointF(x, y);
}

QPointF FilterEditorWidget::filterToWidget(const QPointF& point) const 
{
    // Convert from filter coordinates to widget coordinates
    double x = (point.x() / 255.0) * width();
    double y = height() - (point.y() / 255.0) * height(); // Invert Y since widget Y increases downward
    
    return QPointF(x, y);
}

void FilterEditorWidget::sortPoints() 
{
    // Sort points by x-coordinate to ensure a valid function
    std::sort(points.begin(), points.end(), 
        [](const QPointF& a, const QPointF& b) { return a.x() < b.x(); });
}

int FilterEditorWidget::findClosestPoint(const QPointF& pos, double& distance) 
{
    int closest = -1;
    distance = std::numeric_limits<double>::max();
    
    for (int i = 0; i < points.size(); i++) {
        QPointF widgetPos = filterToWidget(points[i]);
        double d = QPointF(pos - widgetPos).manhattanLength();
        
        if (d < distance) {
            closest = i;
            distance = d;
        }
    }
    
    return closest;
}

void FilterEditorWidget::drawAxes(QPainter& painter) 
{
    painter.save();
    
    // Draw a frame around the widget
    painter.setPen(QPen(Qt::black, 1));
    painter.drawRect(0, 0, width() - 1, height() - 1);
    
    // Draw grid lines
    painter.setPen(QPen(QColor(220, 220, 220), 1));
    
    // Horizontal grid lines (every 32 pixels)
    for (int y = 32; y < height(); y += 32) {
        painter.drawLine(0, y, width(), y);
    }
    
    // Vertical grid lines (every 32 pixels)
    for (int x = 32; x < width(); x += 32) {
        painter.drawLine(x, 0, x, height());
    }
    
    painter.restore();
}

void FilterEditorWidget::drawCurve(QPainter& painter) 
{
    painter.save();
    
    // Sort points by x-coordinate
    QVector<QPointF> sortedPoints = points;
    std::sort(sortedPoints.begin(), sortedPoints.end(), 
        [](const QPointF& a, const QPointF& b) { return a.x() < b.x(); });
    
    // Draw line segments connecting points
    painter.setPen(QPen(Qt::blue, 2));
    
    QPainterPath path;
    bool firstPoint = true;
    
    for (const QPointF& point : sortedPoints) {
        QPointF widgetPos = filterToWidget(point);
        
        if (firstPoint) {
            path.moveTo(widgetPos);
            firstPoint = false;
        } else {
            path.lineTo(widgetPos);
        }
    }
    
    painter.drawPath(path);
    
    // Draw points
    for (int i = 0; i < points.size(); i++) {
        QPointF widgetPos = filterToWidget(points[i]);
        
        if (i == selectedPoint) {
            // Selected point
            painter.setPen(QPen(Qt::red, 2));
            painter.setBrush(Qt::red);
            painter.drawEllipse(widgetPos, 5, 5);
        } else {
            // Normal point
            painter.setPen(QPen(Qt::blue, 2));
            painter.setBrush(Qt::white);
            painter.drawEllipse(widgetPos, 4, 4);
        }
    }
    
    painter.restore();
} 