#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod = 1e9 + 7;
#define all(c) (c).begin(), (c).end()
typedef vector<int> vi;
typedef vector<vi> vvi;

// Range Max
struct node {
	int x;
};

class SegmentTrees
{
	vector<node> st;
public:
	void init(int n) {
		st.clear();
		st.assign(4*n, {0});
	}
	inline node combine(node a, node b)
	{
		node ret;
		ret.x = max(a.x, b.x);
		return ret;
	}
	void build(vi &arr,int left,int right,int pos=1)
	{
		if(left > right) return;
		if(left == right)
		{
			st[pos] = {arr[left]};
		}
		else
		{
			int mid = (left + right)/2;
			build(arr, left, mid, (pos<<1LL));
			build(arr, mid+1, right, (pos<<1LL)+1);
			st[pos] = combine(st[pos*2], st[pos*2+1]);
		}
	}
	void update(int idx,int val,int left,int right,int pos=1)
	{
		if(left > right) return;
		if(left == right)
		{
			st[pos].x = val;
		}
		else
		{
			int mid = (left + right)/2;
			if(idx <= mid) update(idx, val, left, mid, (pos<<1LL));
			else update(idx, val, mid+1, right, (pos<<1LL) + 1);
			st[pos] = combine(st[pos*2], st[pos*2+1]);
		}
	}
	node query(int l,int r,int left,int right,int pos=1)
	{
		if(l>r) return {0};
		if(l==left && r==right) return st[pos];
		else
		{
			int mid = (left + right)/2;
			return combine(query(l, min(r,mid), left, mid, (pos<<1LL)), query(max(l,mid+1), r, mid+1, right, (pos<<1LL)+1));
		}
	}
};


class hld
{
	SegmentTrees sgt;
	vector<vector<int>> adj;
	vector<int> sz, par, head, sc, st, ed, A, val;
	int t, n;
public:
	hld(vector<vector<int>> &adj1,vector<int> val1,int n1) {
		n = n1;
		sz.resize(n+2);
		par.resize(n+2);
		head.resize(n+2);
		sc.resize(n+2);
		st.resize(n+2);
		ed.resize(n+2);
		A.resize(n+2);
		adj = adj1;
		val = val1;
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
		A[t-1] = val[x];
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
	void build(int base = 1) {
		dfs_sz(base);
		dfs_hld(base);
		sgt.init(t);
		sgt.build(A, 0, t - 1);
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
	void update(int p,int val1) {
		val[p] = val1;
		A[st[p]] = val[p];
		sgt.update(st[p], A[st[p]], 0, t - 1);
	}
	int query_up(int x,int p) {
		int ans = 0;
		while(head[x] != head[p]) {
			ans = max(ans, sgt.query(st[head[x]], st[x], 0, t-1).x);
			x = par[head[x]];
		}
		ans = max(ans, sgt.query(st[p], st[x], 0, t - 1).x);
		return ans;
	}
	int rmax(int u,int v) {
		int l = lca(u, v);
		return max(query_up(u, l), query_up(v, l));
	}
};

int main() 
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);  
	int n, q;
	cin >> n >> q;
	vi val(n + 1);
	for(int i = 1; i <= n; i++) cin >> val[i];
	vvi adj(n + 1);
	for(int i = 2; i <= n; i++) {
		int u, v;
		cin >> u >> v;
		adj[v].push_back(u);
		adj[u].push_back(v);
	}
	hld H(adj, val, n);
	H.build();
	while(q--) {
		int t;
		cin >> t;
		if(t == 1) {
			int x, val1;
			cin >> x >> val1;
			H.update(x, val1);
		} else {
			int u, v;
			cin >> u >> v;
			cout << H.rmax(u, v) << " ";
		}
	}
	cout << endl;
	return 0;
}
