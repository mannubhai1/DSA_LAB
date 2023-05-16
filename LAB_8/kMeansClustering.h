#ifndef KMEANSCLUSTERING_H
#define KMEANSCLUSTERING_H

#include "points.h"
#include "myRBTree.h"
#include <vector>
#include <unordered_map>
#include <cmath>

class cluster : public myRBTree
{
public:
    bool isCentroid;
    Point centroid;

    cluster();
    cluster(Point p);
    void updateCentroid();
};

class GraphPoint : public Point
{
public:
    int cluster;

    GraphPoint(Point p, int cluster);
    GraphPoint(double x, double y, int cluster);
    GraphPoint(double x, double y);
    GraphPoint(Point p);

    double calcDist(GraphPoint p)
    {
        return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
    }

    bool operator==(const GraphPoint &p) const
    {
        return (x == p.x && y == p.y);
    }

    bool operator!=(const GraphPoint &p) const
    {
        return (x != p.x || y != p.y);
    }
};

class my_graph
{
public:
    int numClusters;
    int numPoints;
    std::vector<cluster> clusters;
    std::vector<GraphPoint> graphPoints;

    my_graph(int numClusters);
    void setPoints(std::vector<GraphPoint> points);
    void assignRandomCentroids();
    void addPoint(GraphPoint p);
    void removePoint(GraphPoint p);
    void doKMeans();
};

#endif