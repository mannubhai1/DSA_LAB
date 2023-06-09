// articulation point in O(v+e) ..trajan algo ..

// that is removal of vertex increase number of strongly 
// connected components in a graph 

// So, we can conclude that the only 2 conditions for U
// to be an articulation point are:
//     If all paths from A
// to V require U
// to be in the graph.
// If U
//     is the root of the DFS traversal with at least 2 children subgraphs disconnected from each other.
// Then we can break condition #1 into 2 subconditions:



// adj[u] = adjacent nodes of u
// ap = AP = articulation points
// p = parent
// disc[u] = discovery time of u
// low[u] = 'low' node of u

int dfsAP(int u, int p) {
  int children = 0;
  low[u] = disc[u] = ++Time;
  for (int& v : adj[u]) {
    if (v == p) continue; // we don't want to go back through the same path.
                          // if we go back is because we found another way back
    if (!disc[v]) { // if V has not been discovered before
      children++;
      dfsAP(v, u); // recursive DFS call
      if (disc[u] <= low[v]) // condition #1
        ap[u] = 1;
      low[u] = min(low[u], low[v]); // low[v] might be an ancestor of u
    } else // if v was already discovered means that we found an ancestor
      low[u] = min(low[u], disc[v]); // finds the ancestor with the least discovery time
  }
  return children;
}

void AP() {
  ap = low = disc = vector<int>(adj.size());
  Time = 0;
  for (int u = 0; u < adj.size(); u++)
    if (!disc[u])
      ap[u] = dfsAP(u, u) > 1; // condition #2
}