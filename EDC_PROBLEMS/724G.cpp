
//https://codeforces.com/contest/724/problem/G
// Also check mifaovo's soln


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

vector<vector<lii>> adj;
vector<bool> vis;
vector<pair<lii,ll>> edges;
ll ans=0;
ll n,m;
ll zero[62],one[62];
ll pw[200];
ll refff=0;

const ll  LOG_A = 61;
ll basis[LOG_A]; // basis[i] keeps the mask of the vector whose f value is i
ll sz;// Current size of the basis

void insert_vector(ll mask)
{
	refff|=mask;
	for(ll i=0;i<LOG_A;i++)
	{
		if(((1LL<<i)&mask)==0) continue;
		if(!basis[i])
		{
			basis[i]=mask;
			sz++;
		}
		mask^=basis[i];
	}
}
class dsu // spanning tree giving xor between any two elements;
{
	lvi size;
	lvi parent,xor_with_root;
	public:
	dsu(ll N)
	{
		parent.assign(N+2,-1);
		size.assign(N+2,1);
		xor_with_root.resize(N+2,0);
	}
	inline ll getparent(ll x)
	{
		if(parent[x]==-1) return x;
		else 
		{
			ll par=parent[x];
			parent[x]=getparent(parent[x]);
			xor_with_root[x]^=xor_with_root[par];
			return parent[x];
		}
	}
	void union_set(ll x,ll y,ll v)
	{
		ll v1=xor_with_root[x];
		ll v2=xor_with_root[y];
		x=getparent(x);
		y=getparent(y);
		if(x==y) return ;
		if(size[y]>size[x]) swap(x,y);
		parent[y]=x;
		xor_with_root[y]=v1^v2^v;
		size[x]+=size[y];
	}
	bool issameset(ll x,ll y)
	{
		return getparent(x)==getparent(y);
	}
	ll getxor(ll x,ll y)
	{
		getparent(x);getparent(y);
		return xor_with_root[x]^xor_with_root[y];
	}
	ll givexor(ll x) { return xor_with_root[x];}
};


bool mysort(pair<lii,ll> a,pair<lii,ll> b)
{
	return a.ss<b.ss;
}
ll temp_n=0;
void dfs(ll x,ll par=-1,ll xr=0)
{
	temp_n++;
	vis[x]=true;
	for(ll i=0;i<61;i++)
	{
		if((1LL<<i)&xr) one[i]++;
		else zero[i]++;
	}
	for(auto next:adj[x])
	{
		if(!vis[next.ff])
		{
			dfs(next.ff,x,xr^next.ss);
		}
	}
}

void go()
{
	dsu ds(n);
	sort(all(edges),mysort);
	for (int i = 0; i < m; ++i)
	{
		ll x=edges[i].ff.ff,y=edges[i].ff.ss,z=edges[i].ss;
		if(ds.issameset(x,y)) continue;
		ds.union_set(x,y,z);
	}
	lvvi lists(n+2);
	for(int i=0;i<m;i++)
	{
		ll x=edges[i].ff.ff;
		lists[ds.getparent(x)].pb(i);
	}
	for(int i=1;i<=n;i++)
	{
		if(lists[i].size()>0)
		{
			temp_n=0;
			sz=0;
			memset(basis,0,sizeof(basis));
			for(auto idx:lists[i])
			{
				ll x=edges[idx].ff.ff,y=edges[idx].ff.ss,z=edges[idx].ss;
				ll xr=ds.getxor(x,y);
				xr^=z;
				insert_vector(xr);
			}
			memset(zero,0,sizeof(zero));
			memset(one,0,sizeof(one));	
			dfs(edges[lists[i][0]].ff.ff,-1,0);
			for(ll s=0;s<61;s++)
			{
				bool ok=false;
				
				if((1LL<<s)&refff) ok=true;
				if(ok)
				{
					ans=mod_sum(ans,mod_product(pw[s+sz-1],(temp_n*(temp_n-1LL))/2));
				}
				else ans=mod_sum(ans,mod_product(zero[s],one[s],pw[s+sz]));
			}
			refff=0;
		}
	}
}
signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	cin>>n>>m;
	adj.resize(n+2);
	edges.resize(m);
	vis.resize(n+2);
	pw[0]=1;
	for(int i=1;i<200;i++)
	{
		pw[i]=(pw[i-1]*2)%mod;
	}
	for (int i = 0; i < m; ++i)
	{
		ll x,y,z;
		cin>>x>>y>>z;
		adj[x].pb({y,z});
		adj[y].pb({x,z});
		edges[i]={{x,y},z};
	}
	go();
	cout<<ans<<endl;
	return 0;
}	


void dfs(ll x,ll p,ll d=0)
{
	ll la = na[d%a];
	ll lb = nb[d%b];
	na[d%a]++;
	nb[d%b]++;
	for(auto next:adj[x])
	{
		if(next!=p)
		{
			dfs(next,x,d+1);
		}
	}
	ll reqa = na[d%a] - la;
	ll reqb = nb[d%b] - lb;
}