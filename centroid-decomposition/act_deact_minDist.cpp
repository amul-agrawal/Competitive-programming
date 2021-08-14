
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define ll long long int
#define ld long double
#define ordered_set tree < ll ,  null_type ,  less<ll> ,  rb_tree_tag ,  tree_order_statistics_node_update >
//added two more functions to set
//(1)*(set.find_by_order(k))[kth element in the sorted set] 
//(2)set.order_of_key(k)[count of elements strictly less than k]

// Uncomment when using kactl templates and change typedef of pair
// #define rep(i, a, b) for(int i = a; i < (b); ++i)
// #define sz(x) (int)(x).size()
// typedef pair<int, int> pii;

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

mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
// usage: x = rng() % k; shuffle(all(v), rng);

#define all(c) (c).begin(),(c).end()
#define tc(t) int (t); cin>>(t);while((t)--)
#define ff first
#define pb push_back
#define ss second
#ifdef ONLINE_JUDGE
	#define error(args...) 0
#else
	#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
#endif
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr <<"[ "<< *it << " = " << a << " ]"<< endl;
	err(++it, args...);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
const long long mod = 1e9 + 7;
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

long long mos() { return 0LL; }
template<typename T, typename... Args>
T mos(T a, Args... args) { return ((a + mos(args...))%mod + mod)%mod; }

long long mop() { return 1LL; }
template<typename T, typename... Args>
T mop(T a, Args... args) { return (a*mop(args...))%mod; }
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

const int logN = 20, N = 1e5 + 13;
vvi dist(N+2, vi(logN, 0));
vvi adj(N+2);
vi par(N), lvl(N), done(N), sub(N);
int nn = 0;

void dfs_size(int x,int p)
{
	nn++;
	sub[x] = 1;
	for(auto nx : adj[x])
	{
		if(!done[nx] and nx != p)
		{
			dfs_size(nx, x);
			sub[x] += sub[nx];
		}
	}
}

int find_ct(int x,int p)
{
	for(auto nx : adj[x])
	{
		if(!done[nx] and nx!=p and sub[nx] > nn/2)
			return find_ct(nx, x);
	}
	return x;
}

void add_edge(int x,int p)
{
	lvl[x] = 1 + lvl[p];
	par[x] = p;
	done[x] = 1;
}

void dfs(int x,int p,int l)
{
	for(auto nx : adj[x])
	{
		if(!done[nx] and nx != p)
		{
			dist[nx][l] = 1 + dist[x][l];
			dfs(nx, x, l);
		}
	}
}

void decompose(int x,int p=0)
{
	nn = 0;
	dfs_size(x,x);
	int ct = find_ct(x,x);
	add_edge(ct, p);
	dfs(ct, ct, lvl[ct]);
	for(auto nx : adj[ct])
	{
		if(!done[nx]) 
		{
			decompose(nx, ct);
		}
	}
}

#define endl "\n"
signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	int n;
	cin>>n;
	for (int i = 0; i < n-1; ++i)
	{
		int u, v;
		cin>>u>>v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	decompose(1, 0);
	vector<multiset<int>> my(n+2);
	auto activate = [&](int x)
	{
		int x1 = x;
		while(x > 0)
		{
			my[x].insert(dist[x1][lvl[x]]);
			x = par[x];
		}
	};
	auto deactivate = [&](int x)
	{
		int x1 = x;
		while(x > 0)
		{
			my[x].erase(my[x].find(dist[x1][lvl[x]]));
			x = par[x];
		}
	};
	vi active(n+2, 0);
	auto flip = [&](int x)
	{
		if(active[x]) {
			deactivate(x);
		} else {
			activate(x);
		}
		active[x] = 1- active[x];
	};
	auto find = [&](int x)
	{
		int x1 = x, min1 = n+2;
		while(x > 0)
		{
			if(my[x].size())
				min1 = min(min1, dist[x1][lvl[x]] + *my[x].begin());
			x = par[x];
		}
		return (min1 > n ? -1 : min1);
	};
	tc(Q)
	{
		int t, x;
		cin>>t>>x;
		if(t == 0) {
			flip(x);
		} else {
			cout<<find(x)<<endl;
		}
	}
	return 0;
}	



// 1. overflow
// 2. re-initialize global variables for every test case.
// 3. edge cases like n=1

// Run time error
// 1. division by zero.
// 2. array bounds.

// TLE
// 1. uncomment that #define endl '\n' line