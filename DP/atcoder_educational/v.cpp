
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
// #define mod 1000000007
ll mod;
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

ll mod_sum() { return 0LL; }
template<typename T, typename... Args>
T mod_sum(T a, Args... args) { return ((a + mod_sum(args...))%mod + mod)%mod; }

ll mod_product() { return 1LL; }
template<typename T, typename... Args>
T mod_product(T a, Args... args) { return (a*mod_product(args...))%mod; }
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

lvi dp;
lvvi adj;
lvi size;
lvi ans;
vector<bool> visited;

void dfs(ll x,ll par=-1)
{
	dp[x]=1;
	for(auto next:adj[x])
	{
		if(next!=par)
		{
			dfs(next,x);
			dp[x]=mod_product(dp[x],1+dp[next]);
		}
	}
}
void dfs1(ll x,ll par=-1)
{
	ans[x]=dp[x];
	visited[x]=true;
	ll len=adj[x].size();
	lvi prefix_prod(len+2),suffix_prod(len+2);
	for(int i=0;i<len;i++)
	{
		if(i==0) prefix_prod[i]=dp[adj[x][i]]+1;
		else prefix_prod[i]=mod_product(1+dp[adj[x][i]],prefix_prod[i-1]);
	}
	for(int i=len-1;i>=0;i--)
	{
		if(i==(len-1)) suffix_prod[i]=dp[adj[x][i]]+1;
		else suffix_prod[i]=mod_product(1+dp[adj[x][i]],suffix_prod[i+1]);
	}
	suffix_prod[len]=1;
	for (int i = 0; i < len; ++i)
	{
		if(visited[adj[x][i]]) continue;
		ll child=adj[x][i];
		ll save_root=dp[x];
		ll save_child=dp[child];
		if(i==0) dp[x]=suffix_prod[i+1];
		else if(i==len-1) dp[x]=prefix_prod[i-1];
		else dp[x]=mod_product(prefix_prod[i-1],suffix_prod[i+1]);
		dp[child]=mod_product(dp[child],dp[x]+1);
		dfs1(child,x);
		dp[child]=save_child;
		dp[x]=save_root;
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	ll n;
	cin>>n>>mod;
	dp.resize(n+2);
	adj.resize(n+2);
	ans.resize(n+2);
	visited.resize(n+2);
	for(int i=1;i<n;i++)
	{
		ll x,y;
		cin>>x>>y;
		adj[x].pb(y);
		adj[y].pb(x);
	}
	dfs(1);dfs1(1);
	for (int i = 1; i <=n; ++i)
	{
		cout<<ans[i]<<endl;
	}
	return 0;
}