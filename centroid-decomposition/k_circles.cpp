// Given k circles. Find nodes covered by these circles.
#include <bits/stdc++.h>
using namespace std;
typedef vector< int > vi;
typedef vector<pair<int,int>> vii;
typedef vector< vector<int> > vvi;
#define all(c) (c).begin(),(c).end()
#define tc(t) int (t); cin>>(t);while((t)--)
#define pb push_back

const int N = 5e4 + 13, logN = 17;
vi adj[N], sub(N), par(N), lvl(N), done(N), par_adj(N);
vvi dist(N, vi(logN, 0)), anc(N, vi(logN, 0));
int nn = 0, root;

void dfs_size(int x,int p) {
	nn++;
	sub[x] = 1;
	for(auto nx : adj[x]) {
		if(!done[nx] and nx != p) {
			dfs_size(nx, x);
			sub[x] += sub[nx];
		} 
	}
}

int find_ct(int x,int p) {
	for(auto nx : adj[x]) {
		if(!done[nx] and nx != p and sub[nx] > nn/2)
			return find_ct(nx, x);
	}
	return x;
}

void dfs(int x,int p,int ct) {
	anc[x][lvl[ct]] = ct;
	for(auto nx : adj[x]) {
		if(!done[nx] and nx != p) {
			dist[nx][lvl[ct]] = 1 + dist[x][lvl[ct]];
			dfs(nx, x, ct);
		}
	}
}

// par_adj[ct] = adjacent vertex to parent of ct in OT in subtree of ct.
int decompose(int x,int p) {
	nn = 0;
	dfs_size(x, x);
	int ct = find_ct(x, x);
	if(p) lvl[ct] = 1 + lvl[p];
	done[ct] = 1;
	par[ct] = p;
	dfs(ct, ct, ct);
	for(auto nx : adj[ct]) {
		if(!done[nx]) {
			int nct = decompose(nx, ct);
			par_adj[nct] = nx;
		}
	}
	return ct;
}

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	int n;
	cin>>n;
	for(int i=1;i<n;i++) {
		int u, v;
		cin>>u>>v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	root = decompose(1, 0);
	vvi dist_ps(n+2), cntbn_ps(n+2);
	for(int x = 1; x <= n; x++) {
		int y = x;
		while(y > 0) {
			dist_ps[y].pb(dist[x][lvl[y]]);
			if(par[y] > 0) {
				cntbn_ps[y].pb(dist[x][lvl[par[y]]]);
			}
			y = par[y];
		}
	}
	// hashed the distance and made prefix sum array.
	auto make_prefix = [&](vector<int>& ps) {
	  if (ps.empty()) return;
	  vector<int> arr = ps;
	  ps.resize(1 + *max_element(arr.begin(), arr.end()));
	  fill(ps.begin(), ps.end(), 0);
	  for (auto x : arr) ps[x]++;
	  for (int i = 1; i < ps.size(); ++i) {
	    ps[i] += ps[i - 1];
	  }
	};

	for(int x=1;x<=n;x++) {
		make_prefix(dist_ps[x]);
		make_prefix(cntbn_ps[x]);
	}

	// nodes <= idx in d.
	auto count = [&](const vector<int>& d, int idx) {
	  if (idx >= (int)d.size()) idx = (int)d.size() - 1;
	  if (idx < 0) return 0;
	  return d[idx];
	};

	function<int(int,vii)> dfs = [&](int ct,vii query_nodes) {
		int ans =0;
		int max_dist = -1;
		unordered_map<int,unordered_map<int,int>> child_to_query_nodes;
		for(auto& c : query_nodes) {
			auto &x = c.first, &d = c.second;
			max_dist = max(max_dist, d - dist[x][lvl[ct]]);
			auto y = anc[x][lvl[ct] + 1];
			if(y) {
				auto& val = child_to_query_nodes[y][x];
				val = max(val, d);
			}
		}

		if(max_dist > (int)dist_ps[ct].size())
			return dist_ps[ct].back();

		ans += count(dist_ps[ct], max_dist);
		for(auto& it : child_to_query_nodes) {
			auto &y = it.first;
			auto &child_query_nodes = it.second;
			ans -= count(cntbn_ps[y], max_dist); 
			if(max_dist > 0) {
				auto &val = child_query_nodes[par_adj[y]];
				val = max(val, max_dist - 1);
			}
			ans += dfs(y, {child_query_nodes.begin(), child_query_nodes.end()});
		}
		return ans;
	};
	int q;
	cin>>q;
	while(q--)  {
		int k;
		cin>>k;
		vii qrs(k);
		for (int i = 0; i < k; ++i) {
			int x, d;
			cin>>x>>d;
			qrs[i] = {x, d};
		}
		cout<<dfs(root, qrs)<<endl;
	}

	return 0;
}	
