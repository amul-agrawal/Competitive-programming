
// **** WHEN THE GOING GETS TOUGH, THE TOUGH GETS GOING. ****

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define ll long long int
#define ull unsigned long long int
#define ld long double
#define ordered_set tree < ll ,  null_type ,  less<ll> ,  rb_tree_tag ,  tree_order_statistics_node_update >
//added two more functions to set
//(1)*(set.find_by_order(k))[kth element in the sorted set] 
//(2)set.order_of_key(k)[count of elements strictly less than k]

typedef vector< int > vi;
typedef vector< ll > lvi;
typedef vector< vi > vvi;
typedef vector< lvi > lvvi;
typedef pair< int,int > ii;
typedef pair< ll,ll > lii;
typedef vector<ii> vii;
typedef vector<lii> lvii;

#define min_prq(t) priority_queue<t,vector<t>,greater<t>>
#define max_prq(t) priority_queue<t>
#define pb push_back
#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(auto i = (c).begin(); i != (c).end(); i++)//remember i is an iterator
#define present(c,x) ((c).find(x) != (c).end())//for sets,maps,multimaps
#define cpresent(c,x) (find(all(c),x) != (c).end())//for vectors
#define tc(t) int (t); cin>>(t);while((t)--)
#define ff first
#define ss second
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " is " << a << endl;
	err(++it, args...);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
#define mod 1000000007
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

ll mod_sum() { return 0LL; }
template<typename T, typename... Args>
T mod_sum(T a, Args... args) { return ((a + mod_sum(args...))%mod + mod)%mod; }

ll mod_product() { return 1LL; }
template<typename T, typename... Args>
T mod_product(T a, Args... args) { return (a*mod_product(args...))%mod; }
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

const ll N =1e5+13,logN=22;
lvvi adj(N),par(N,lvi(logN,0));
lvi depth(N),dp(N);
lvii edges(N);

void dfs(ll x,ll pr=0,ll d=0)
{
	depth[x]=d;
	par[x][0]=pr;
	for(int i=1;i<logN;i++)
	{
		par[x][i]=par[par[x][i-1]][i-1];
	}
	for(auto next:adj[x])
	{
		if(next!=pr)
		{
			dfs(next,x,d+1);
		}
	}
}
ll lca(ll u,ll v)
{
	if(depth[u]>depth[v]) swap(u,v);
	ll diff=depth[v]-depth[u];
	for(int i=0;i<logN;i++)
	{
		if((1<<i)&diff) v=par[v][i];
	}
	if(u==v) return u;
	for(int i=logN-1;i>=0;i--)
	{
		if(par[u][i]!=par[v][i])
		{
			u=par[u][i];
			v=par[v][i];
		}
	}
	return par[u][0];
}


void dfs1(ll x,ll pr=-1)
{
	for(auto next:adj[x])
	{
		if(next!=pr)
		{
			dfs1(next,x);
			dp[x]+=dp[next];
		}
	}
	// error(x,dp[x]);
}

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	ll n;
	cin>>n;
	for (int i = 0; i < n-1; ++i)
	{
		ll x,y;
		cin>>x>>y;
		edges[i]={x,y};
		adj[x].pb(y);
		adj[y].pb(x);
	}
	dfs(1);
	tc(T)
	{
		ll a,b;
		cin>>a>>b;
		dp[a]++;
		dp[b]++;
		dp[lca(a,b)]-=2;
		// error(a,b,lca(a,b));
	}
	dfs1(1);
	for(int i=0;i<n-1;i++)
	{
		ll a=edges[i].ff,b=edges[i].ss;
		if(depth[b]>depth[a]) swap(a,b);
		cout<<dp[a]<<" ";
	}
	cout<<endl;
	return 0;
}	