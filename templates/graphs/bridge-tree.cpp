// source: https://tanujkhattar.wordpress.com/2016/01/10/the-bridge-tree-of-a-graph/
template<class T = int>
class Dsu
{
	int sts;
	vector<T> parent, size;
public:
	void build(T n) {
		sts = n;
		parent.clear(); size.clear();
		parent.assign(n, -1);
		size.assign(n, 1);
	}
	T getparent(T x) {
		if(parent[x] == -1) return x;
		else return parent[x] = getparent(parent[x]);
	}
	bool IsSameSet(T x,T y) {return getparent(x) == getparent(y);}
	void join(T x,T y) {
		x = getparent(x);
		y = getparent(y);
		if(x == y) return;
		if(size[x] < size[y]) swap(x, y);
		parent[y] = x;
		sts--;
		size[x] += size[y];
	}
	int get_sets(){return sts;}
};
 
int n, m, Tin;
vector<vii> adj, adjn;
vi vis, low;
Dsu<int> ds;
vector<array<int, 3>> bridges;
 
void pre() {
	Tin = 0;
	bridges.clear();
	low.clear(); low.resize(n + 2);
	adj.clear(); adj.resize(n + 2);
	adjn.clear(); adjn.resize(n + 2);
	vis.clear(); vis.resize(n + 2);
}
 
int dfs0(int x,int p = -1,int w=0) {
	vis[x] = 1;
	low[x] = Tin++;
	int crl = low[x];
	for(auto nx : adj[x]) {
		if(nx.ff == p) continue;
		else if (vis[nx.ff]) crl = min(crl, low[nx.ff]);
		else crl = min(crl, dfs0(nx.ff, x, nx.ss));
	}
	if(crl == low[x] and p != -1) bridges.pb({x, p, w});
	else if (p != -1) ds.join(x, p);
	return crl;
}
 
void build_bridgetree() {
	ds.build(n + 1);
	for(int i = 1; i <= n; i++) {
		if(!vis[i]) {
			dfs0(i);
		}
	}
	for(auto arr : bridges) {
		int u = ds.getparent(arr[0]);
		int v = ds.getparent(arr[1]);
		int w = arr[2]; 
		if(u != v) {
			adjn[v].pb({u, w});
			adjn[u].pb({v, w});
		}
	}
}