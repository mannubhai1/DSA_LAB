#include <iostream>
#include <vector>
#include "kMeansClustering.h"

using namespace std;

int main()
{
    my_graph g(4);
    vector<pair<double, double>> points = {{2, 2}, {5, 8}, {-2, -2}, {2, -2}, {5, -4}, {3, 1}, {-1, 0}, {-5, -2}};
    for (auto &p : points)
    {
        g.addPoint(GraphPoint(p.first, p.second));
    }
    g.doKMeans();
}