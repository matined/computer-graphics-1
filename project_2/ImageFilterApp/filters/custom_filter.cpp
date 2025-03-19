#include "custom_filter.h"
#include <algorithm>
#include <cmath>
#include <QMap>

// CustomFilter implementation

CustomFilter::CustomFilter()
    : name("Untitled")
{
    // Initialize with identity filter points
    points.append(QPointF(0, 0));
    points.append(QPointF(255, 255));
}

CustomFilter::CustomFilter(const QString& name, const QVector<QPointF>& filterPoints)
    : name(name), points(filterPoints)
{
    // Ensure points are in order by x-coordinate
    std::sort(points.begin(), points.end(), 
        [](const QPointF& a, const QPointF& b) { return a.x() < b.x(); });
}

void CustomFilter::apply(QImage &image) const
{
    // Generate lookup table
    QVector<int> lut = getLookupTable();
    
    // Apply the lookup table to each pixel
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QRgb pixel = image.pixel(x, y);
            
            // Apply lookup table to each color component
            int red = lut[qRed(pixel)];
            int green = lut[qGreen(pixel)];
            int blue = lut[qBlue(pixel)];
            int alpha = qAlpha(pixel); // Keep original alpha
            
            // Set the transformed pixel
            image.setPixel(x, y, qRgba(red, green, blue, alpha));
        }
    }
}

void CustomFilter::setPoints(const QVector<QPointF>& newPoints)
{
    points = newPoints;
    
    // Ensure points are in order
    std::sort(points.begin(), points.end(), 
        [](const QPointF& a, const QPointF& b) { return a.x() < b.x(); });
}

QVector<QPointF> CustomFilter::getPoints() const
{
    return points;
}

QString CustomFilter::getName() const
{
    return name;
}

void CustomFilter::setName(const QString& newName)
{
    name = newName;
}

QVector<int> CustomFilter::getLookupTable() const
{
    // Create a lookup table for the filter
    QVector<int> lut(256);
    
    if (points.isEmpty()) {
        // If no points, return identity LUT
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

// CustomFilterManager implementation

CustomFilterManager& CustomFilterManager::instance()
{
    // Singleton pattern
    static CustomFilterManager instance;
    return instance;
}

CustomFilterManager::CustomFilterManager()
{
    // Initialize a predefined identity filter
    CustomFilter identityFilter("Identity", {QPointF(0, 0), QPointF(255, 255)});
    
    // Add all predefined filters
    filters["Identity"] = identityFilter;
}

void CustomFilterManager::addFilter(const CustomFilter& filter)
{
    filters[filter.getName()] = filter;
}

CustomFilter CustomFilterManager::getFilter(const QString& name) const
{
    if (filters.contains(name)) {
        return filters[name];
    }
    
    // Return an identity filter if name is not found
    return CustomFilter();
}

QStringList CustomFilterManager::getFilterNames() const
{
    return filters.keys();
}

bool CustomFilterManager::hasFilter(const QString& name) const
{
    return filters.contains(name);
} 