// USE INF = 1e9!

/**********************************************************************************
* MIN COST MAX FLOW (MINIMUM COST TO ACHIEVE MAXIMUM FLOW)                        *
* Description: Given a graph which represents a flow network where every edge has *
* a capacity and a cost per unit, find the minimum cost to establish the maximum  *
* possible flow from s to t.                                                      *
* Note: When adding edge (a, b), it is a directed edge!                           *
* Usage: min_cost_max_flow()                                                      *
*        add_edge(from, to, cost, capacity)                                       *
* Notation: flw: max flow                                                         *
*           cst: min cost to achieve flw                                          *
* Testcase:                                                                       *
* add_edge(src, 1, 0, 1);   add_edge(1, snk, 0, 1);   add_edge(2, 3, 1, INF);     *
* add_edge(src, 2, 0, 1);   add_edge(2, snk, 0, 1);   add_edge(3, 4, 1, INF);     *
* add_edge(src, 2, 0, 1);   add_edge(3, snk, 0, 1);                               *
* add_edge(src, 2, 0, 1);   add_edge(4, snk, 0, 1);   => flw = 4, cst = 3         *
**********************************************************************************/

template<class T = int> struct Dinic {
    bool SCALING = false; // non-scaling = V^2E, Scaling=VElog(U) with higher constant
    int MAXV, lim = 1;
    const T INF = numeric_limits<T>::max();
    struct edge { int to, rev; T cap, flow; };
    vector<vector<edge>> adj; vector<int> level, ptr;
    //============== FUNCTION ==============================//
    Dinic(int n = 0): MAXV(n + 1), adj(n + 1) {};
    void build(int n = 0) { MAXV = n + 1; adj.assign(MAXV, vector<edge>(0)); }
    void addEdge(int a, int b, T cap, bool isDirected = true) {
        if (a == b) return;
        adj[a].push_back({b, adj[b].size(), cap, 0});
        adj[b].push_back({a, adj[a].size() - 1, isDirected ? 0 : cap, 0});
    }
    bool bfs(int s, int t) {
        level.assign(MAXV, -1);
        queue<int> q({s}); level[s] = 0;
        while (!q.empty() && level[t] == -1) {
            int u = q.front(); q.pop();
            for (auto e : adj[u])
                if (level[e.to] == -1 && e.flow < e.cap && (!SCALING || e.cap - e.flow >= lim)) // Consider change level[e.to] > level[u] + cost if MCMF
                    q.push(e.to), level[e.to] = level[u] + 1;
        } return level[t] != -1;
    }
    T dfs(int u, int t, T flow) {
        if (u == t || !flow) return flow;
        for (; ptr[u] < adj[u].size(); ptr[u]++) {
            edge &e = adj[u][ptr[u]];
            if (level[e.to] != level[u] + 1) continue; // level[e.to] != level[u] + cost if MCMF
            if (T pushed = dfs(e.to, t, min(flow, e.cap - e.flow))) {
                e.flow += pushed; adj[e.to][e.rev].flow -= pushed;
                return pushed;
            }
        } return 0;
    }
    T calc(int s, int t) {
        T flow = 0;
        for (lim = SCALING ? (1 << 30) : 1; lim > 0; lim >>= 1) {
            while (bfs(s, t)) {
                ptr.assign(MAXV, 0);
                while (T pushed = dfs(s, t, INF)) flow += pushed;
            }
        } return flow;
    }
};

