/*
    Time Complexity: O(V + E)
    Space Complexity: O(V)

    Where 'V' denotes the number of nodes and
    'E' denotes the number of edges in the given Graph.
*/

#include <iostream>
using namespace std;

#define MOD 1000000007

#include <vector>

int dfs(int src, vector<int> &dp, vector<vector<int>> &graph) {
    if (dp[src] != -1) {
        return dp[src];
    }

    int count = 1;
    for (int i = 0; i < graph[src].size(); i++) {
        count = (count + dfs(graph[src][i], dp, graph)) % MOD;
    }

    return dp[src] = count;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int v, e, s;
    cin >> v >> e >> s;

    vector<vector<int>> graph(v + 1);

    for (int i = 0; i < e; i++) {
        int src, des;
        cin >> src >> des;

        graph[src].push_back(des);
    }

    vector<int> dp(v + 1, -1);

    int totalWays = dfs(s, dp, graph);
    cout << totalWays;

    return 0;
}