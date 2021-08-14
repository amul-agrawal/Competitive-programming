// Q1: Activate Node
// Q2: Find the closest activated node.
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
#define pb push_back
#define ss second
#define endl "\n"

const int N = 1e5 + 13;
const int logN = 20;
int n, q;
vvi adj(N+1);
vvi dist(N+1, vi(logN, 0));
int nn = 0;
vi sub(n+1), done(n+1, 0), par(n+1), lvl(n+1);

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
void add_edge(int ch,int p) {
	lvl[ch] = lvl[p] + 1;
	done[ch] = 1;
	par[ch] = p;
}

void dfs(int x,int p,int l,int d) {
	dist[x][l] = d;
	for(auto nx : adj[x]) {
		if(!done[nx] and nx != p) {
			dfs(nx, x, l, d + 1);
		}
	}
}

void decompose(int x,int p) {
	nn = 0;
	dfs_size(x, x);
	int ct = find_ct(x, x);
	if(p == 0)
		p = ct;
	add_edge(ct, p);
	dfs(ct, ct, lvl[ct], 0);
	for(auto nx : adj[ct]) {
		if(!done[nx]) {
			decompose(nx, ct);
		}
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	cin>>n>>q;
	for(int i = 1; i<n;i++) {
		int u, v;
		cin>>u>>v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	decompose(1, 0);
	vector<set<int>> my(n+1);
	// activate a node.
	auto addNode = [&](int x) {
		int x1 = x;
		while(true)
		{
			my[x].insert(dist[x1][lvl[x]]);
			if(x == par[x])
				break;
			x = par[x];
		}
	};
	addNode(1);
	// Find the closest activated node.
	auto find = [&](int x) {
		int sm = n, x1 = x;
		while(true) {
			if(!my[x].empty()) {
				sm = min(sm, dist[x1][lvl[x]] + *my[x].begin());
			}
			if(x==par[x])
				break;
			x = par[x];
		}
		return sm;
	};

	while(q--)
	{
		int t;
		cin>>t;
		if(t == 2) {
			int x;
			cin>>x;
			cout<<find(x)<<endl;
		}
		else {
			int x;
			cin>>x;
			addNode(x);
		}
	}
	return 0;
}	
