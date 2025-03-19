#ifndef OCTREE_QUANTIZER_H
#define OCTREE_QUANTIZER_H

#include <QImage>
#include <QColor>
#include <QVector>
#include <QList>

// Forward declarations
class OctreeNode;

// Octree Color Quantizer
class OctreeQuantizer 
{
public:
    // Constructor
    OctreeQuantizer();
    
    // Destructor
    ~OctreeQuantizer();
    
    // Apply octree color quantization to an image
    void quantize(QImage &image, int maxColors);
    
private:
    // Maximum tree depth (8 levels, one for each bit of color)
    static const int MAX_DEPTH = 8;
    
    // Root node of the octree
    OctreeNode* root;
    
    // Leaf count and maximum leaves
    int leafCount;
    int maxLeaves;
    
    // Lists of inner nodes at each depth [0-7]
    QList<OctreeNode*> innerNodes[8];
    
    // Add a color to the octree
    void add(const QRgb &color);
    
    // Add a color to the octree recursively
    void addRecursive(OctreeNode* node, const QRgb &color, int depth);
    
    // Create a new node
    OctreeNode* createNode(int depth);
    
    // Reduce the octree by one node
    void reduce();
    
    // Find color in octree
    QRgb find(const QRgb &color);
    
    // Calculate child index for a color at a given depth
    static int childIndex(const QRgb &color, int depth);
};

// Octree Node class
class OctreeNode 
{
public:
    // Constructor
    OctreeNode();
    
    // Destructor
    ~OctreeNode();
    
    // Is this a leaf node
    bool isLeaf;
    
    // Color sums
    int sumR;
    int sumG;
    int sumB;
    
    // Pixel count
    int count;
    
    // Children (8 possible children)
    OctreeNode* children[8];
};

#endif // OCTREE_QUANTIZER_H 