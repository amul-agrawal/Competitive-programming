// spoj: GOODA
#include <bits/stdc++.h>
using namespace std;

// Takes adjaceny list, empty adj_scc: new DAG, 
// empty comp: nodes which are being represented by this node, n
void condense(vector<vector<int>> adj,vector<vector<int>> &adj_scc,vector<vector<int>> &comp,vector<int> &root_of,int n) {
	vector<vector<int>> rev_adj(n+1);
	for(int u=1;u<=n;u++) {
		for(auto v : adj[u]) {
			rev_adj[v].push_back(u);
		}
	}
	vector<bool> vis(n+1, false);
	vector<int> order, component;
	function<void(int)> dfs1 = [&](int x) {
		vis[x] = true;
		for(auto nx : adj[x]) {
			if(!vis[nx]) {
				dfs1(nx);
			}
		}
		order.push_back(x);
	};
	for(int i=1;i<=n;i++) {
		if(!vis[i]) {
			dfs1(i);
		}
	}
	vis.clear(); vis.assign(n+1, false);
	// order is now kind of topologically sorted
	reverse(order.begin(), order.end());
	function<void(int)> dfs2 = [&](int x) {
		vis[x] = true;
		component.push_back(x);
		for(auto u : rev_adj[x]) {
			if(!vis[u]) {
				dfs2(u);
			}
		}
	};
	vector<int> root_nodes;
	comp.clear(); comp.resize(n+1);
	root_of.clear(); root_of.resize(n+1);
	for(auto v : order) {
		if(!vis[v]) {
			dfs2(v);
			int root = component.front();
			for(auto u : component) root_of[u] = root;
			root_nodes.push_back(root);
			comp[root] = component;
			component.clear();
		}
	}
	adj_scc.clear(); adj_scc.resize(n+1);
	for(int u = 1; u <= n; u++) {
		for(auto v : adj[u]) {
			if(root_of[u] != root_of[v]) {
				// cerr<<"edge: "<<root_of[u]<<" "<<root_of[v]<<endl;
				adj_scc[root_of[u]].push_back(root_of[v]);
			}
		}
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	int n, m, s, e;
	cin>>n>>m>>s>>e;
	vector<int> f(n+1);
	for(int i=1;i<=n;i++)
		cin>>f[i];
	vector<vector<int>> adj(n+2), comp, adj_scc;
	for(int i=0;i<m;i++)
	{
		int u, v;
		cin>>u>>v;
		adj[u].push_back(v);
		// adj[v].push_back(u);
	}
	vector<int> root_of;
	condense(adj,adj_scc,comp,root_of,n);
	// -------------------------------
	vector<bool> take(n+1, false);
	function<void(int)> dfs = [&](int x)
	{
		take[x] = true;
		for(auto nx : adj_scc[x])
			if(!take[nx]) 
				dfs(nx);
	};
	dfs(root_of[s]);
	vector<int> in(n+1);
	for(int i=1;i<=n;i++)
	{
		if(take[i])
		for(auto nx : adj_scc[i])
		{
			if(take[nx])
			in[nx]++;
		}
	}
	vector<long long> dp(n+1, -1), val(n+1);
	auto get_dp = [&](int x)
	{
		if(dp[x] != -1) return dp[x];
		dp[x] = 0;
		for(auto c : comp[x])
			dp[x] += f[c];
		return dp[x]; 
	};
	queue<int> q;
	q.push(root_of[s]);
	val[root_of[s]] = get_dp(root_of[s]);
	while(!q.empty())
	{
		auto curr = q.front();
		q.pop();
		for(auto nx : adj_scc[curr]) {
			in[nx]--;
			val[nx] = max(val[nx],val[curr] + get_dp(nx));
			if(in[nx] == 0) {
				q.push(nx);
			}
		}
	}
	cout<<val[root_of[e]]<<endl;
	return 0;
}	
