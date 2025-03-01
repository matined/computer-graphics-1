#ifndef CUSTOM_FILTER_H
#define CUSTOM_FILTER_H

#include <QImage>
#include <QVector>
#include <QPointF>
#include <QString>
#include <QMap>
#include <QStringList>

class CustomFilter 
{
public:
    CustomFilter();
    CustomFilter(const QString& name, const QVector<QPointF>& filterPoints);
    
    // Apply this filter to an image
    void apply(QImage &image) const;
    
    // Set the filter points
    void setPoints(const QVector<QPointF>& points);
    
    // Get the filter points
    QVector<QPointF> getPoints() const;
    
    // Get/set the filter name
    QString getName() const;
    void setName(const QString& name);
    
    // Generate a lookup table from the filter points
    QVector<int> getLookupTable() const;
    
private:
    QString name;
    QVector<QPointF> points;
};

// Custom filter manager to store and retrieve custom filters
class CustomFilterManager 
{
public:
    static CustomFilterManager& instance();
    
    // Add or update a custom filter
    void addFilter(const CustomFilter& filter);
    
    // Get a filter by name
    CustomFilter getFilter(const QString& name) const;
    
    // Get all filter names
    QStringList getFilterNames() const;
    
    // Check if a filter exists
    bool hasFilter(const QString& name) const;
    
private:
    CustomFilterManager();
    QMap<QString, CustomFilter> filters;
};

#endif // CUSTOM_FILTER_H 