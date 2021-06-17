// Complexity:
// 1. O(V^2*E): General
// 2. O(Flow * E): General
// 3. O(E*root(V)): when sum of edge capacities is O(n), 
// 					we can treat edge with weight x as x edges with weight 1.
// 4. O(E*V*log(Flow)): Dinics with scaling

#define sz(x) (int)(x).size()	
const int INF = 1e9 + 13;
template<class T = long long>
class Dinic
{
	// {to: to, rev: reverse_edge_id, c: cap, oc: original cap}
	struct Edge {
		int to, rev;
		T c, oc;
		T flow() { return max(oc - c, (T)0); } // if you need flows
	};
	vector<int> lvl, ptr, q;
	vector<vector<Edge>> adj;
public:
	Dinic(int n)
	{
		lvl.resize(n); adj.resize(n); ptr.resize(n); q.resize(n);
	}

	// automatically adds a reversed edge
	void addEdge(int a, int b, T c, T rcap = 0) {
		adj[a].push_back({b, sz(adj[b]), c, c});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
	}

	T dfs(int v, int t, T f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (T p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}

	T calc(int s, int t) {
		
		T flow = 0; q[0] = s;

		// bfs part, setting the lvl here
		for(int L = 0; L < 31; L++) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vector<int>(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}

			// dfs part, setting ptr and checking for a path.
			while (T p = dfs(s, t, INF)) flow += p;
		} while (lvl[t]);
		return flow;
	}

	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};