/*
    Time Complexity: O(N * M * log(N * M))
    Space Complexity: O(N * M)

    where 'N' is the number of rows and 'M' is number of columns in the grid respectively.
*/


// minimum direction question we need to find a path from (0,0) to (n-1,m-1) with minimum direction changes

#include<queue>

// Defining the structure of node
struct node {
    int row, column;
    int distance = 1e6;
};

// Defining the structure of edge
struct edge {

    int destinationRow, destinationColumn;
    int weight;

    edge(int x, int y, int w) {
        destinationRow = x;
        destinationColumn = y;
        weight = w;
    }
};

// Custom operator to compare nodes
bool operator < (node a, node b) {
    return a.distance > b.distance;
}

int minDirectionChanges(vector< vector< char > > grid, int n, int m) {
    
    // Defining and initializing the Node arrays
    node arr[n][m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr[i][j].row = i;
            arr[i][j].column = j;
        }
    }

    // Defining the adjacency list
    vector < edge > adj[n][m];

    // Traversing the grid
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
    
            // Checking if we are in bottom row
            if (i + 1 < n) {
    
                // Checking if specified direction is Down
                if (grid[i][j] == 'D') {
                    adj[i][j].push_back(edge(i + 1, j, 0));
                }
                else {
                    adj[i][j].push_back(edge(i + 1, j, 1));
                }
            }

            // Checking if we are in rightmost column
            if ((j + 1) < m) {
                
                // Checking if specified direction is Right
                if (grid[i][j] == 'R') {
                    adj[i][j].push_back(edge(i, j + 1, 0));
                }
                else {
                    adj[i][j].push_back(edge(i, j + 1, 1));
                }
            }

            // Checking if we are in top row
            if (i) {
                
                // Checking if specified direction is Up
                if (grid[i][j] == 'U') {
                    adj[i][j].push_back(edge(i - 1, j, 0));
                } 
                else {
                    adj[i][j].push_back(edge(i - 1, j, 1));
                }
            }

            // Checking if we are in leftmost column
            if (j) {
                
                // Checking if specified direction is Left
                if (grid[i][j] == 'L') {
                    adj[i][j].push_back(edge(i, j - 1, 0));
                } 
                else {
                    adj[i][j].push_back(edge(i, j - 1, 1));
                }
            }
        }
    }

    // Initialising the priority-queue and pushing start node
    priority_queue < node > pq;
    arr[0][0].distance = 0;
    pq.push(arr[0][0]);

    // Traversing the priority-queue
    while (pq.size()) {
        
        // Extracting node with min-distance
        node current = pq.top();
        pq.pop();

        // Traversing  the edges of extracted node
        for (edge currentEdge : adj[current.row][current.column]) {
        
            // Checking if the weight gets reduced
            if ((currentEdge.weight + (arr[current.row][current.column]).distance) < (arr[currentEdge.destinationRow][currentEdge.destinationColumn]).distance) {
        
                // Updating the weight value
                (arr[currentEdge.destinationRow][currentEdge.destinationColumn]).distance = currentEdge.weight + (arr[current.row][current.column]).distance;
        
                // Pushing it into priority-queue
                pq.push(arr[currentEdge.destinationRow][currentEdge.destinationColumn]);
            }
        }
    }
    
    // Returning minimum-distance
    return (arr[n - 1][m - 1]).distance;
}