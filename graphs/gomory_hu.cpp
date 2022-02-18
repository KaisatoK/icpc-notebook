FORW(i, 0, n, 1) par[i] = 1, ans[i][i] = 0;
FORW(s, 2, n, 1) {
	G.build(n + 1);
	FORW(u, 1, n, 1) FORW(v, 1, n, 1) if(u != v) G.addEdge(u, v, a[u][v]);

	int t = par[s];
	int tmp = G.calc(s, t);

	VI visited, unvisited;
	FORW(u, 1, n, 1) {
		if(G.level[u] == -1) unvisited.pb(u);
		else visited.pb(u);
	}

	for(int& u1 : visited) for(int& u2 : unvisited) {
		ans[u1][u2] = min(ans[u1][u2], tmp);
		ans[u2][u1] = min(ans[u2][u1], tmp);
	}

	FORW(u, s, n, 1) if(t == par[u] && G.level[u] != -1) par[u] = s;
}