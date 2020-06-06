
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
const ll N = 1e5 + 13;
const ll logN= 21;

struct node
{
	ll arr[11];
	node()
	{
		// memset(arr,N,sizeof(arr));
		for(int i=0;i<11;i++) arr[i]=N;
	}
	void insert(ll val)
	{
		arr[10]=val;
		sort(arr,arr+11);

	}
};
ll n,m,q;
lvvi adj;

ll depth[N],par[N][logN+2];
vector<vector<node>> data1(N,vector<node>(logN+2));


node merge(node x, node y)
{
	node ans = x;
	for (int i = 0; i < 11; i++)
		ans.insert(y.arr[i]);
	return ans;
}

void dfs(ll x,ll d=0,ll pr=0)
{
	depth[x]=d;
	par[x][0]=pr;
	for(int i=1;i<=logN;i++)
	{
		par[x][i]=par[par[x][i-1]][i-1];
		data1[x][i]=merge(data1[x][i-1],data1[par[x][i-1]][i-1]);
	}
	for(auto next:adj[x])
	{
		if(next!=pr)
		{
			dfs(next,d+1,x);
		}
	}
}

node getresult(ll u,ll v,ll p)
{
	node ret;
	ll dif=depth[u]-depth[p]; //excluding parent;
	for (int i = 0; i <= logN; ++i)
	{
		if((1<<i)&dif)
		{
			ret=merge(ret,data1[u][i]);
			u=par[u][i];
		}
	}
	dif=depth[v]-depth[p]+1; // including parent
	for (int i = 0; i <= logN; ++i)
	{
		if((1<<i)&dif)
		{
			ret=merge(ret,data1[v][i]);
			v=par[v][i];
		}
	}
	return ret;
}

node lcs(ll u,ll v)
{
	if(depth[u]>depth[v]) swap(u,v);
	if(u==v) return data1[u][0];
	ll dif=depth[v]-depth[u];
	ll u1=u,v1=v;
	for(int i=0;i<=logN;i++)
	{
		if((1<<i)&dif)
		{
			v=par[v][i];
		}
	}
	if(u==v) return getresult(u1,v1,u);
	for(int i=logN;i>=0;i--)
	{
		if(par[v][i]!=par[u][i])
		{
			v=par[v][i];
			u=par[u][i];
		}
	}
	return getresult(u1,v1,par[u][0]);
}

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	cin>>n>>m>>q;
	adj.resize(n+2);
	for (int i = 0; i < n-1; ++i)
	{
		ll x,y;
		cin>>x>>y;
		adj[x].pb(y);
		adj[y].pb(x);
	}
	for (int i = 0; i < m; ++i)
	{
		ll x;
		cin>>x;
		data1[x][0].insert(i+1);
	}
	dfs(1);
	while(q--)
	{
		ll u,v,a;
		cin>>u>>v>>a;
		node c=lcs(u,v);
		ll size=0;
		for(int i=0;i<10;i++)
		{
			if(c.arr[i]!=N) size++;
		}
		ll k=min(size,a);
		cout<<k<<" ";
		for (int i = 0; i < k; ++i)
		{
			cout<<c.arr[i]<<" ";
		}
		cout<<endl;
	}
	return 0;
}	



// depth, par, res1 array;