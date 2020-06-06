
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

const ll N = 1e5 + 13, logN = 22;
lvvi adj(N),par(N,lvi(logN,0));
lvi subtree(N),depth(N);
ll n;

void dfs(ll x,ll pr=0,ll d=0)
{
	depth[x]=d;
	par[x][0]=pr;
	subtree[x]=1;
	for(int i=1;i<logN;i++)
	{
		par[x][i]=par[par[x][i-1]][i-1];
	}
	for(auto next:adj[x])
	{
		if(next!=pr)
		{
			dfs(next,x,d+1);
			subtree[x]+=subtree[next];
		}
	}
}

ll kthpar(ll x,ll k)
{
	for(int i=0;i<logN;i++)
	{
		if(k&(1<<i)) x=par[x][i];
	}
	return x;
}

ll lca(ll x,ll y)
{
	if(x==y) return n;
	if(depth[x]>depth[y]) swap(x,y);
	ll diff=depth[y]-depth[x];
	ll y1=y,x1=x;
	for(int i=0;i<logN;i++)
	{
		if(diff&(1<<i)) y=par[y][i];
	}
	// error(x,y,diff);
	if(y==x) 
	{
		if(diff&1) return 0;
		diff/=2;
		ll diff2=diff-1;
		ll p1=kthpar(y1,diff),p2=kthpar(y1,diff2);		
		return subtree[p1]-subtree[p2];
	}
	for(int i=logN-1;i>=0;i--)
	{
		if(par[y][i]!=par[x][i])
		{
			y=par[y][i];
			x=par[x][i];
		}
	}
	ll la=par[y][0];
	ll cx=depth[x1]-depth[la],cy=depth[y1]-depth[la];
	if(cx==cy) return n-subtree[y]-subtree[x];
	if((cx+cy)&1) return 0;
	if(cx>cy)
	{
		ll k=(cx+cy)/2;
		ll p1=kthpar(x1,k),p2=kthpar(x1,k-1);
		return subtree[p1]-subtree[p2];
	}
	else
	{
		ll k=(cx+cy)/2;
		ll p1=kthpar(y1,k),p2=kthpar(y1,k-1);
		return subtree[p1]-subtree[p2];
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	cin>>n;
	for (int i = 0; i < n-1; ++i)
	{
		ll x,y;
		cin>>x>>y;
		adj[x].pb(y);
		adj[y].pb(x);
	}
	dfs(1);
	tc(T)
	{
		ll x,y;
		cin>>x>>y;
		cout<<lca(x,y)<<endl;
	}
	return 0;
}	