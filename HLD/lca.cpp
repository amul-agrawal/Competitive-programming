#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod = 1e9 + 7;
#define all(c) (c).begin(), (c).end()
typedef vector<int> vi;
typedef vector<vi> vvi;

class hld
{
	vector<vector<int>> adj;
	vector<int> sz, par, head, sc, st, ed, A;
	int t;
public:
	hld(vector<vector<int>> &adj1,int n) {
		sz.resize(n+2);
		par.resize(n+2);
		head.resize(n+2);
		sc.resize(n+2);
		st.resize(n+2);
		ed.resize(n+2);
		A.resize(n+2);
		adj = adj1;
		t = 0;
	}
	void dfs_sz(int x,int p = 0) {
		sz[x] = 1;
		par[x] = p;
		head[x] = x;
		for(auto nx : adj[x]) {
			if(nx == p) continue;
			dfs_sz(nx, x);
			sz[x] += sz[nx];
			if(sz[nx] > sz[sc[x]]) sc[x] = nx;
		}
	}
	void dfs_hld(int x,int p = 0) {
		st[x] = t++;
		// A[t] = val[x];
		// dfs on heavy edge
		if(sc[x]) {
			head[sc[x]] = head[x];
			dfs_hld(sc[x], x);
		}
		// dfs on light edge
		for(auto nx : adj[x]) {
			if(nx == p or nx == sc[x]) continue;
			dfs_hld(nx, x);
		}
		ed[x] = t - 1;
	}
	bool anc(int x,int y) {
		if(x == 0) return true;
		if(y == 0) return false;
		return (st[x] <= st[y] and ed[x] >= ed[y]);
	}
	int lca(int x,int y) {
		if(anc(x, y)) return x;
		if(anc(y, x)) return y;
		while(!anc(par[head[x]], y)) x = par[head[x]];
		while(!anc(par[head[y]], x)) y = par[head[y]];
		x = par[head[x]];
		y = par[head[y]];
		// one will overshoot the lca and the other will reach lca.
		return anc(x, y) ? y : x;
	}
};

int main() 
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);  
	int n, q;
	cin >> n >> q;
	vvi adj(n + 1);
	for(int i = 2; i <= n; i++) {
		int p;
		cin >> p;
		adj[p].push_back(i);
		adj[i].push_back(p);
	}
	hld H(adj, n);
	H.dfs_sz(1);
	H.dfs_hld(1);
	while(q--) {
		int u, v;
		cin >> u >> v;
		cout << H.lca(u, v) << endl;
	}
	return 0;
}
