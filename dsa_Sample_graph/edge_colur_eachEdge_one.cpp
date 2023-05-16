// C++ program to illustrate
// Vizing's Theorem
#include <iostream>
using namespace std;

// Function to print the color of the edge
void colorEdge(int edges[][3], int e)
{
	int color;

	// Assign a color to every edge 'i'.
	for (int i = 0; i < e; i++) {
		color = 1;
	flag:
		// Assign a color and
		// then check its validity.
		edges[i][2] = color;
		for (int j = 0; j < e; j++) {
			if (j == i)
				continue;

			// If the color of edges
			// is adjacent to edge i
			if ((edges[i][0] == edges[j][0])
				|| (edges[i][1] == edges[j][0])
				|| (edges[i][0] == edges[j][1])
				|| (edges[i][1] == edges[j][1])) {

				// If the color matches
				if (edges[i][2] == edges[j][2]) {

					// Increment the color,
					// denotes the change in color.
					color++;

					// goes back, and assigns
					// the next color.
					goto flag;
				}
			}
		}
	}
	// Check the maximum color from all the edge colors
	int maxColor = -1;
	for (int i = 0; i < e; i++) {
		maxColor = max(maxColor, edges[i][2]);
	}
	cout << maxColor
		<< " colors needs to generate a valid edge "
			"coloring:"
		<< endl;
	for (int i = 0; i < e; i++) {
		cout << "color between v(1): " << edges[i][0]
			<< " and v(2): " << edges[i][1]
			<< " is: color " << edges[i][2] << endl;
	}
}

// Driver Code
int main()
{
	// initialize the number
	// of edges of the graph
	int e = 5;

	// initialize the vertex
	// pair of every edge in a graph
	int edges[e][3] = { { 1, 2, -1 },
						{ 2, 3, -1 },
						{ 3, 4, -1 },
						{ 4, 1, -1 },
						{ 1, 3, -1 } };

	colorEdge(edges, e);
	return 0;
}
