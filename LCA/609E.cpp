
// https://codeforces.com/contest/609/problem/E
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
ll n,m;
vector<pair<ll,lii>> edges,edges1;
vector<vector<lii>> adj;
ll wgt=0;
const ll N = 2e5 + 13;

ll depth[N];
ll par[N][23],max1[N][23];


class Dsu
{
	lvi parent,size;
public:
	Dsu(ll n1)
	{
		parent.assign(n1+2,-1);
		size.assign(n1+2,1);
	}
	ll getparent(ll x)
	{
		if(parent[x]==-1) return x;
		else return parent[x]=getparent(parent[x]);
	}
	void union_set(ll x,ll y)
	{
		x=getparent(x);
		y=getparent(y);
		if(x==y) return ;
		if(size[x]<size[y]) swap(x,y);
		parent[y]=x;
		size[x]+=size[y];
	}
	bool issameset(ll x,ll y) {return getparent(x)==getparent(y);}
};

void mst()
{
	sort(all(edges));
	Dsu ds(n+2);
	for (int i = 0; i < m; ++i)
	{
		ll x=edges[i].ss.ff,y=edges[i].ss.ss,z=edges[i].ff;
		if(ds.issameset(x,y)) continue;
		ds.union_set(x,y);
		wgt+=z;
		adj[x].pb({y,z});
		adj[y].pb({x,z});
	}
}



void dfs(ll x,ll pr,ll d,ll edwgt=0)
{
	depth[x]=d;
	par[x][0]=pr;
	if(pr!=0)
	{
		max1[x][0]=edwgt;
		for(int i=1;i<=21;i++)
		{
			par[x][i]=par[par[x][i-1]][i-1];
			max1[x][i]=max(max1[x][i-1],max1[par[x][i-1]][i-1]);
		}
	}
	for(auto next:adj[x])
	{
		if(next.ff!=pr)
		{
			dfs(next.ff,x,d+1,next.ss);
		}
	}
}

ll getresult(ll x,ll y)
{
	if(depth[x]>depth[y]) swap(x,y);
	ll dif=depth[y]-depth[x];
	ll max_ans=0;
	for(int i=0;i<22;i++)
	{
		if((1<<i)&dif)
		{
			max_ans=max(max_ans,max1[y][i]);
			y=par[y][i];
		}
	}
	if(x==y) return  max_ans; // x was an ancestor of y;
	for(int i=21;i>=0;i--)
	{
		ll p1=par[y][i];
		ll p2=par[x][i];
		if(p1!=p2)
		{
			ll temp=max(max1[x][i],max1[y][i]);
			max_ans=max(temp,max_ans);
			x=p2;y=p1;
		}
	}
	ll temp=max(max1[x][0],max1[y][0]);
	max_ans=max(temp,max_ans);
	return max_ans;
}

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
    cin>>n>>m;
    adj.resize(n+2);
    for (int i = 0; i < m; ++i)
    {
    	ll x,y,z;
    	cin>>x>>y>>z;
    	edges.pb({z,{x,y}});
    }
    edges1=edges;
    mst();
    dfs(1,0,0);
    for (int i = 0; i < m; ++i)
    {
		ll x=edges1[i].ss.ff,y=edges1[i].ss.ss,z=edges1[i].ff;
    	ll res=getresult(x,y);
    	res=wgt - res + z;
    	cout<<res<<endl;
    }
	return 0;
}	


