// Each query gives you numbers v, l and you should tell him the number of vertexes like u such that D(v, u) <= l.
// Add parent and remove child contribution method.

#include <bits/stdc++.h>
using namespace std;
#define ll long long int

typedef vector< int > vi;
typedef vector<long long> lvi;
typedef vector< vector<int> > vvi;
typedef vector< vector<long long> > lvvi;
typedef pair< int,int > ii;
typedef pair< long long,long long > lii;
typedef vector<pair<int,int>> vii;
typedef vector<pair<long long,long long>> lvii;
typedef vector<vector<pair<int,int>>> vvii;
typedef vector<vector<pair<long long,long long>>> lvvii;
typedef vector<bool> vb;

#define all(c) (c).begin(),(c).end()
#define tc(t) int (t); cin>>(t);while((t)--)
#define ff first
#define ss second
#define pb push_back

const int N = 2e5 + 13, logN = 25;
vector<pair<int,int>> adj[N];
ll sub[N], lvl[N], nn, par[N], dist[N][logN], done[N];

void dfs_size(int x,int p) {
	sub[x] = 1;
	nn++;
	for(auto next : adj[x]) {
		if(not done[next.ff] and next.ff != p) {
			dfs_size(next.ff, x);
			sub[x] += sub[next.ff];
		}
	}
}

int find_centroid(int x,int p) {
	for(auto next : adj[x]) {
		if(not done[next.ff] and next.ff != p and sub[next.ff] > nn/2) 
			return find_centroid(next.ff, x);
	}
	return x;
}

void add_edge_in_ct(int p,int ch) {
	lvl[ch] = lvl[p] + 1;
	par[ch] = p;
	done[ch] = 1;
}

void dfs(int x,int p,int root_lvl) {
	for(auto next : adj[x]) {
		if(not done[next.ff] and next.ff != p) {
			dist[next.ff][root_lvl] = dist[x][root_lvl] + next.ss;
			dfs(next.ff, x, root_lvl);
		}
	}
}

void decompose(int root,int p=0) {
	nn = 0;
	dfs_size(root, root);
	int ct = find_centroid(root, root);
	add_edge_in_ct(p, ct);
	dfs(ct, ct, lvl[ct]);
	for(auto next : adj[ct]) {
		if(not done[next.ff]) {
			decompose(next.ff, ct);
		}
	}	
}


signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	int n, q;
	cin>>n>>q;
	for(int i=1;i<n;i++) {
		int u, v, w;
		cin>>u>>v>>w;
		adj[u].pb({v, w});
		adj[v].pb({u, w});
	}
	decompose(1);
	lvvi child_cntb(N), my(N);
	for(int x = 1; x <= n; x++) {
		for(int y = x; y > 0; y = par[y]) {
			my[y].pb(dist[x][lvl[y]]);
			child_cntb[y].pb(dist[x][lvl[par[y]]]);
		}
	}

	for(int x = 1; x <= n; x++) {
		sort(all(my[x]));
		sort(all(child_cntb[x]));
	}

	// number of nodes <= k in v.
	auto cnt_k = [&](lvi &v,ll k) {
		int l = upper_bound(all(v), k) - v.begin();
		return l;
	};

	auto k_dists = [&](int x,ll k) {
		int ans = cnt_k(my[x], k);
		int ch = x, q = x;
		x = par[x];
		while(x > 0) {
			ans += (cnt_k(my[x], k - dist[q][lvl[x]]));
			ans -= (cnt_k(child_cntb[ch], k - dist[q][lvl[x]]));
			ch = x;
			x = par[x];
		}
		return ans;
	};	

	while(q--) {
		ll x, d;
		cin>>x>>d;
		cout<<k_dists(x, d)<<endl;
	}
	
	return 0;
}	
