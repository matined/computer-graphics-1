#include "octree_quantizer.h"
#include <algorithm>
#include <cmath>
#include <QDebug>

// OctreeQuantizer implementation

OctreeQuantizer::OctreeQuantizer() : root(nullptr), leafCount(0), maxLeaves(0) {
    // Initialize the innerNodes lists
    for (int i = 0; i < 8; i++) {
        innerNodes[i].clear();
    }
}

OctreeQuantizer::~OctreeQuantizer() {
    // Clean up the root and its subtree
    delete root;
}

void OctreeQuantizer::quantize(QImage &image, int maxColors) {
    // Ensure maxColors is valid (at least 1, at most 256)
    maxLeaves = std::max(1, std::min(256, maxColors));
    
    // Reset state
    leafCount = 0;
    root = nullptr;
    for (int i = 0; i < 8; i++) {
        innerNodes[i].clear();
    }
    
    // Step 1: Build the octree from the image (as described in the guide)
    for (int y = 0; y < image.height(); y++) {
        for (int x = 0; x < image.width(); x++) {
            QRgb color = image.pixel(x, y);
            add(color);
            
            // Reduce tree if needed
            while (leafCount > maxLeaves) {
                reduce();
            }
        }
    }
    
    // Step 2: Replace each pixel with its palette color
    for (int y = 0; y < image.height(); y++) {
        for (int x = 0; x < image.width(); x++) {
            QRgb originalColor = image.pixel(x, y);
            QRgb newColor = find(originalColor);
            image.setPixel(x, y, newColor);
        }
    }
}

void OctreeQuantizer::add(const QRgb &color) {
    // Create root if it doesn't exist
    if (root == nullptr) {
        root = createNode(0);
    }
    
    // Add color recursively starting from root at depth 0
    addRecursive(root, color, 0);
}

void OctreeQuantizer::addRecursive(OctreeNode* node, const QRgb &color, int depth) {
    // If the node is a leaf, add color to it
    if (node->isLeaf) {
        node->sumR += qRed(color);
        node->sumG += qGreen(color);
        node->sumB += qBlue(color);
        node->count += 1;
        return;
    }
    
    // Otherwise, determine which child to descend to
    int index = childIndex(color, depth);
    
    // Create child if it doesn't exist
    if (node->children[index] == nullptr) {
        node->children[index] = createNode(depth + 1);
    }
    
    // Recurse to the child
    addRecursive(node->children[index], color, depth + 1);
}

OctreeNode* OctreeQuantizer::createNode(int depth) {
    OctreeNode* newNode = new OctreeNode();
    
    // Node is a leaf if at max depth
    newNode->isLeaf = (depth == MAX_DEPTH);
    
    // If not a leaf, add to innerNodes list
    if (!newNode->isLeaf) {
        innerNodes[depth].push_back(newNode);
    } else {
        // If a leaf, increment leaf count
        leafCount += 1;
    }
    
    return newNode;
}

void OctreeQuantizer::reduce() {
    // Find the lowest depth with inner nodes
    for (int i = 7; i >= 0; i--) {
        if (!innerNodes[i].empty()) {
            // Select a node to reduce (we'll take the first one)
            OctreeNode* nodeToReduce = innerNodes[i].first();
            innerNodes[i].pop_front();
            
            // Count removed leaves
            int removed = 0;
            
            // Sum the colors and counts from children
            for (int k = 0; k < 8; k++) {
                if (nodeToReduce->children[k] != nullptr) {
                    nodeToReduce->sumR += nodeToReduce->children[k]->sumR;
                    nodeToReduce->sumG += nodeToReduce->children[k]->sumG;
                    nodeToReduce->sumB += nodeToReduce->children[k]->sumB;
                    nodeToReduce->count += nodeToReduce->children[k]->count;
                    
                    // Free the child node
                    delete nodeToReduce->children[k];
                    nodeToReduce->children[k] = nullptr;
                    
                    removed++;
                }
            }
            
            // Mark as leaf and update leaf count
            nodeToReduce->isLeaf = true;
            leafCount = leafCount + 1 - removed;
            
            // Exit after reducing one node
            return;
        }
    }
}

QRgb OctreeQuantizer::find(const QRgb &color) {
    OctreeNode* node = root;
    int depth = 0;
    
    // Descend the tree until a leaf is found
    while (node != nullptr && !node->isLeaf && depth < MAX_DEPTH) {
        int index = childIndex(color, depth);
        if (node->children[index] != nullptr) {
            node = node->children[index];
            depth++;
        } else {
            // If child doesn't exist, this is unexpected
            // (should not happen if color was previously added)
            break;
        }
    }
    
    // Calculate average color from the leaf
    if (node != nullptr && node->count > 0) {
        int r = node->sumR / node->count;
        int g = node->sumG / node->count;
        int b = node->sumB / node->count;
        
        // Ensure values are in valid range
        r = std::max(0, std::min(255, r));
        g = std::max(0, std::min(255, g));
        b = std::max(0, std::min(255, b));
        
        return qRgb(r, g, b);
    }
    
    // Fallback (should not happen)
    return color;
}

int OctreeQuantizer::childIndex(const QRgb &color, int depth) {
    // Get bit position (7 for depth 0, 0 for depth 7)
    int bitPos = 7 - depth;
    
    // Calculate the index based on appropriate bits of RGB components
    int r = (qRed(color) >> bitPos) & 1;
    int g = (qGreen(color) >> bitPos) & 1;
    int b = (qBlue(color) >> bitPos) & 1;
    
    // Combine bits to get index (0-7)
    return (r << 2) | (g << 1) | b;
}

// OctreeNode implementation

OctreeNode::OctreeNode() : isLeaf(false), sumR(0), sumG(0), sumB(0), count(0) {
    // Initialize all children to nullptr
    for (int i = 0; i < 8; i++) {
        children[i] = nullptr;
    }
}

OctreeNode::~OctreeNode() {
    // Clean up children
    for (int i = 0; i < 8; i++) {
        delete children[i];
    }
} 