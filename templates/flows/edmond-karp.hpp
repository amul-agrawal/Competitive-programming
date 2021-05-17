// If edge capacity is integral, Complexity = O(F*E)
// General Complexity for any case = O(VE^2)

// A minimum cut can be found after performing a maximum flow computation
// using the Ford-Fulkerson method. One possible minimum cut is the following:
// the set of all vertices that can be reached from s in the residual graph (using edges with positive residual capacity),
// and the set of all the other vertices. This partition can be easily found using DFS starting at s.

const long long INF = 1e17 + 13;
template<class T = int>
class Flow
{
	int n;
	vector<vector<T>> capacity;
	vector<vector<int>> adj;
public:
	Flow(int N)
	{
		n = N;
		adj.resize(n+2);
		capacity.assign(n+2, vector<int>(n+2, 0));
	}

    // Add reverse edge for each directed edge with zero capacity.
	void add_edge(int u,int v,T w) 
	{
		adj[u].pb(v);
		capacity[u][v] += w;
	}

	int bfs(int s, int t, vector<int>& parent) {
	    fill(parent.begin(), parent.end(), -1);
	    parent[s] = -2;
	    queue<pair<int, T>> q;
	    q.push({s, INF});

	    while (!q.empty()) {
	        int cur = q.front().first;
	        T flow = q.front().second;
	        q.pop();

	        for (int next : adj[cur]) {
	            if (parent[next] == -1 && capacity[cur][next]) {
	                parent[next] = cur;
	                T new_flow = min(flow, capacity[cur][next]);
	                if (next == t)
	                    return new_flow;
	                q.push({next, new_flow});
	            }
	        }
	    }

	    return 0;
	}

	T maxflow(int s,int t)
	{
		T flow = 0;
	    vector<int> parent(n+2);
	    T new_flow;

	    while (new_flow = bfs(s, t, parent)) {
	        flow += new_flow;
	        int cur = t;
	        while (cur != s) {
	            int prev = parent[cur];
	            capacity[prev][cur] -= new_flow;
	            capacity[cur][prev] += new_flow;
	            cur = prev;
	        }
	    }
	    return flow;
	}
};
