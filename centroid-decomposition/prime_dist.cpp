
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

const int N = 5e4 + 13, logN = 16;
vi adj[N], sub(N), done(N), primes, cnt(N);
ll nn, ans = 0;

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

void dfs(int x,int p,int d,int add=1) {
	cnt[d] += add;
	for(auto nx : adj[x]) {
		if(nx != p and !done[nx]) {
			dfs(nx, x, d+1, add);
		}
	}
}

void update(int x,int p,int d) {
	for(auto pr : primes) {
		if(pr - d < 0) continue;
		int req = pr - d;
		if(cnt[req] == 0) break;
		ans += cnt[req];
	}
	for(auto nx : adj[x]) {
		if(nx != p and !done[nx])
		{
			update(nx, x, d + 1);
		}
	}
}


void decompose(int root,int p=0) {
	nn = 0;
	dfs_size(root, root);
	int ct = find_ct(root, root);
	cnt[0] = 1;
	for(auto nx : adj[ct]) {
		if(done[nx]) continue;
		update(nx, ct, 1);
		dfs(nx, ct, 1);
	}
	dfs(ct, p, 0, -1);
	done[ct] = 1;
	for(auto nx : adj[ct]) {
		if(!done[nx]) {
			decompose(nx, ct);
		}
	}
}


void getprimes() {
	vi vis(N, 0);
	for(int i=2;i<N;i++) {
		if(!vis[i]) {
			primes.pb(i);
			for(int j=2*i;j<N;j+=i) {
				vis[j] = 1;
			}
		}
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
    getprimes();
	int n;
	cin>>n;
	for(int i = 1; i < n; i++) {
		int u, v;
		cin>>u>>v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	decompose(1, 0);
	ll tot = (1LL * n * (n-1))/2;
	cout<<fixed<<setprecision(9)<<(double)ans/tot<<endl;
	return 0;
}	
