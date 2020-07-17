// https://www.hackerearth.com/challenges/competitive/march-clash-15/algorithm/counting-on-tree-1/
// soln is o(n*k)
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

const ll N = 50000 + 13;
lvvi adj(N);
ll dp[N][105],subtree[N],a[N];
ll n,k;

void dfs(ll x,ll par=-1)
{
	subtree[x]=1;
	if(a[x]>0) dp[x][1]=1;
	else dp[x][0]=1;
	for(auto next:adj[x])
	{
		if(next!=par)
		{
			dfs(next,x);
			lvi tmp(k+2,0);
			for(int i=0;i<=min(k,subtree[x]);i++)
			{
				for(int j=0;j<=subtree[next]&&(i+j)<=k;j++)
				{
					tmp[i+j]=mod_sum(tmp[i+j],mod_product(dp[x][i],dp[next][j]));
				}
			}
			subtree[x]+=subtree[next];
			// adding values if we have taken the subtree of next.
			for(int i=0;i<=min(k,subtree[x]);i++)
			{
				dp[x][i]=mod_sum(dp[x][i],tmp[i]);
			}
		}
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	tc(T)
	{
		cin>>n>>k;
		adj.clear();
		adj.resize(n+2);
		memset(dp,0,sizeof(dp));
		memset(subtree,0,sizeof(subtree));
		for (int i = 0; i < n; ++i)
		{
			cin>>a[i+1];
		}
		for (int i = 0; i < n-1; ++i)
		{
			ll x,y;
			cin>>x>>y;
			adj[x].pb(y);
			adj[y].pb(x);
		}
		dfs(1);
		ll ans=0;
		for(int i=1;i<=n;i++)
		{
			ans=mod_sum(ans,dp[i][k]);
		}
		cout<<ans<<endl;
	}
	return 0;
}	
// so basically tree dp is nothing but
// 1) root karo tree ko 1 pe..
// try to form the answer from root and its subtree(root is must)
// sum over dp of all nodes.

// is question mai
// basically agar a[x]=0 hai to dp[x][0]=1 and dp[x][1]=0...and vice versa.
// ab tume root ko to daal dia...ab uske children par jaao aur unko root se connect karne ka try karo.
// current children ko lekar dp[root] update hoga...
// dp[x][i] hum  assign nayi value nhi kar rahe qki ..we can skip the next node.