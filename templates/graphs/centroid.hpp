
const int N = 1e5 + 13;
const int logN = 20;

// original tree
vector<int> g[N];
int sub[N], nn, U[N], V[N], W[N], deleted[N];
// centroid tree
int par[N], level[N], dist[N][logN];

int adj(int x,int e) { return U[e] ^ V[e] ^ x; }
void dfs_size(int u,int p) {
	sub[u] = 1;
	nn++;
	for(auto e : g[u]) {
		int v = adj(u, e);
		if(v != p and !deleted[e]) dfs_size(v, u), sub[u] += sub[v];
	}	
}

int find_centroid(int u,int p) {
	for(auto e : g[u]) {
		if(deleted[e]) continue;
		int v = adj(u, e);
		if(v != p and sub[v] > nn/2) return find_centroid(v, u);
	}
	return u;
}

void add_edge_in_centriod_tree(int parent,int child) {
	par[child] = parent;
	level[child] = level[parent] + 1;
}

void dfs(int u,int p,int lvl) {
	for(auto e : g[u]) {
		int v = adj(u, e);
		if(v == p or deleted[e]) continue;
		dist[v][lvl] = dist[u][lvl] + 1;
		dfs(v, u, lvl);
	}
}

void decompose(int root,int p = -1) {
	nn = 0;
	// Compute subtree sizes and number of nodes in this tree.
	dfs_sz(root, root);
	// Find the Centroid of the tree and make it new root;
	int centroid = find_centroid(root, root);
	// Construct the CT
	if( p == -1 ) p = centroid;
	add_edge_in_centriod_tree(p, centroid);
	// Process the O(N) paths from centroid to all nodes in this component
	// Each node will only occur in dfs of its ancestors hence overall(logN * N)
	dfs(centroid, centroid, level[centroid]);

	for(auto e : g[centroid]) {
		if(deleted[e]) continue;
		deleted[e] = 1;
		int v = adj(centroid, e);
		decompose(v, centroid);
	}
}

int lca(int x,int y) {
	while(x != y) {
		if(level[x] > level[y]) swap(x, y);
		y = par[y];
	}
	return x;
}