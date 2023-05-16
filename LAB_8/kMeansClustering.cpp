#include "kMeansClustering.h"
#include <iostream>
#include <unordered_set>
using namespace std;

cluster::cluster()
{
    isCentroid = false;
}

cluster::cluster(Point p)
{
    isCentroid = true;
    centroid = p;
}

void cluster::updateCentroid()
{
    if (root == nullptr)
    {
        isCentroid = false;
        return;
    }
    else
    {
        centroid = Point(sumX / numNodes, sumY / numNodes);
        return;
    }
}

GraphPoint::GraphPoint(Point p, int cluster)
{
    this->x = p.x;
    this->y = p.y;
    this->cluster = cluster;
}

GraphPoint::GraphPoint(double x, double y, int cluster)
{
    this->x = x;
    this->y = y;
    this->cluster = cluster;
}

GraphPoint::GraphPoint(double x, double y)
{
    this->x = x;
    this->y = y;
    this->cluster = -1;
}

GraphPoint::GraphPoint(Point p)
{
    this->x = p.x;
    this->y = p.y;
    this->cluster = -1;
}

my_graph::my_graph(int numClusters)
{
    this->numClusters = numClusters;
    numPoints = 0;
    clusters = std::vector<cluster>(numClusters);
    graphPoints = std::vector<GraphPoint>();
}

void my_graph::setPoints(std::vector<GraphPoint> points)
{
    graphPoints = points;
    numPoints = points.size();
    assignRandomCentroids();
}

void my_graph::assignRandomCentroids()
{
    unordered_set<int> used;
    for (int i = 0; i < numClusters; i++)
    {
        while (true)
        {
            int randNum = rand() % numPoints;
            if (used.find(randNum) == used.end())
            {
                used.insert(randNum);
                clusters[i] = cluster(graphPoints[randNum]);
                clusters[i].isCentroid = true;
                graphPoints[randNum].cluster = i;
                clusters[i].insert(graphPoints[randNum]);
                break;
            }
        }
    }
}

void my_graph::addPoint(GraphPoint p)
{
    graphPoints.push_back(p);
    numPoints++;
}

void my_graph::removePoint(GraphPoint p)
{
    for (int i = 0; i < numPoints; i++)
    {
        if (graphPoints[i] == p)
        {
            graphPoints.erase(graphPoints.begin() + i);
            numPoints--;
            return;
        }
    }
}

void my_graph::doKMeans()
{
    for (int i = 0; i < numClusters; i++)
    {
        clusters[i].clearTree();
        clusters[i].isCentroid = false;
    }
    for (auto &p : graphPoints)
    {
        p.cluster = -1;
    }
    assignRandomCentroids();
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (int i = 0; i < numPoints; i++)
        {
            int minCluster = 0;
            double minDist = graphPoints[i].calcDist(clusters[0].centroid);
            for (int j = 1; j < numClusters; j++)
            {
                double dist = graphPoints[i].calcDist(clusters[j].centroid);
                if (dist < minDist)
                {
                    minDist = dist;
                    minCluster = j;
                }
            }
            if (graphPoints[i].cluster != minCluster)
            {
                changed = true;
                if (graphPoints[i].cluster != -1)
                {
                    clusters[graphPoints[i].cluster].remove(graphPoints[i]);
                }
                graphPoints[i].cluster = minCluster;
                clusters[minCluster].insert(graphPoints[i]);
            }
        }
        for (int i = 0; i < numClusters; i++)
        {
            clusters[i].updateCentroid();
        }
    }
    for (int i = 0; i < numClusters; i++)
    {
        cout << "Cluster " << i << " Centroid: " << clusters[i].centroid.x << ", " << clusters[i].centroid.y << endl;
        clusters[i].print();
        cout << "\n\n";
    }
}
