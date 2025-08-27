/*
 EULERIAN PATH & CIRCUIT RULES
==========================================================
 UNDIRECTED GRAPH:
 Eulerian **Circuit** exists if:
   - All vertices with non-zero degree have even degree.
   - The graph is connected (excluding isolated vertices).
 Eulerian **Path** exists if:
   - Exactly 0 or 2 vertices have odd degree.
   - The graph is connected (excluding isolated vertices).
 If exactly 2 vertices have odd degree → Eulerian Path (not a circuit).
 If all vertices have even degree → Eulerian Circuit (also a path).
----------------------------------------------------------
 DIRECTED GRAPH:
 Eulerian **Circuit** exists if:
   - For every vertex: in-degree == out-degree.
   - The graph is strongly connected (when reduced to non-zero degree nodes).
 Eulerian **Path** exists if:
   - Exactly one vertex has (out-degree = in-degree + 1) → Start vertex.
   - Exactly one vertex has (in-degree = out-degree + 1) → End vertex.
   - All other vertices: in-degree == out-degree.
   - The graph is connected in a way that allows traversal of all edges.
 If these hold, Eulerian Path exists (not necessarily a circuit).
 If all vertices have equal in/out degree → Eulerian Circuit.
*/
//Undirected
int n;
vector<vector<pair<int, int>>> g;
vector<int> path,degree;
vector<bool> seen;
void dfs(int node) {
    while (!g[node].empty()) {
        auto [son, idx] = g[node].back();
        g[node].pop_back();
        if (seen[idx]) { continue; }
        seen[idx] = true;
        dfs(son);
    }
    path.push_back(node);
}
bool is_Eulerian(){
    for (int i = 1; i <= n; i++) 
        if (degree[i] % 2) 
            return 0;
    dfs(1);//or from root
    return 1;
}
//Directed
int n;
vector<vector<int>> g;
vector<int> in, out, path;
void dfs(int node) {
    while (!g[node].empty()) {
        int son = g[node].back();
        g[node].pop_back();
        dfs(son);
    }
    path.push_back(node);
}
bool is_Eulerian(){
  int ok = 1, cnt1 = 0, cnt2 = 0, root = 0;
  for (int i = 1; i <= n; i++) {
    if (in[i] - out[i] == 1) cnt1++;
    if (out[i] - in[i] == 1) cnt2++, root = i;
    if (abs(in[i] - out[i]) > 1) ok = 0;
  }
  if (cnt1 > 1 || cnt2 > 1) ok = 0;
  if (!ok) return 0;
  if (root == 0) {
    for (int i = 1; i <= n; i++) if (out[i]) root = i;
  }
  if (root == 0) return 1; //empty graph
  dfs(root);
  if (ans.size() != edges + 1) return 0; //connectivity
  reverse(ans.begin(), ans.end());
  return 1;
}