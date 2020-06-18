#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define ll long long int
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
#define sz(a) int((a).size())
#define pb push_back
#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(auto i = (c).begin(); i != (c).end(); i++)//remember i is an iterator
#define present(c,x) ((c).find(x) != (c).end())//for sets,maps,multimaps
#define cpresent(c,x) (find(all(c),x) != (c).end())//for vectors
#define tc(t) int (t); cin>>(t);while((t)--)
#define ff first
#define ss second
#define mp make_pair
#define ld long double
#define ull unsigned long long int
#define mod 1000000007
vector<vector<lii>> adj,rev;
lvi d,p,ans,rd,rp;
struct Edge
{
	ll a,b,cost;
};
int main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	tc(T)
	{
		ll n,m;
		cin>>n>>m;
		vector<Edge> v(m+2);
		adj.clear();
		rev.clear();
		d.clear();
		rd.clear();
		ans.clear();
		adj.resize(n+2);
		rev.resize(n+2);
		rd.assign(n+2,0);
		d.assign(n+2,0);
		ans.assign(n+2,0);
		for (int i = 0; i < m; ++i)
		{
			ll x,y,z;
			cin>>x>>y>>z;
			adj[x].pb({y,z});
			rev[y].pb({x,z});
			v[i].a=x;
			v[i].b=y;
			v[i].cost=z;
		}
		for(int i=0;i<n-1;i++)
		{
			for(auto edge:v)
			{
				if(d[edge.b]>(d[edge.a]+edge.cost))
				{
					d[edge.b]=(d[edge.a]+edge.cost);
				}
			}
		}
		for(int i=0;i<n;i++)
		{
			for(auto edge:v)
			{
				if(d[edge.b]>(d[edge.a]+edge.cost))
				{
					d[edge.b]=(d[edge.a]+edge.cost);
					d[edge.b]=-1e15;
					d[edge.a]=-1e15;
					ans[edge.b]=-1e15;
					ans[edge.a]=-1e15;
					// cout<<edge.a<<" "<<edge.b<<endl;
				}	
			}
		}
		for(int i=0;i<n-1;i++)
		{
			for(auto edge:v)
			{
				if(rd[edge.a]>(rd[edge.b]+edge.cost))
				{
					rd[edge.a]=(rd[edge.b]+edge.cost);
				}
			}
		}
		for(int i=0;i<n;i++)
		{
			for(auto edge:v)
			{
				if(rd[edge.a]>(rd[edge.b]+edge.cost))
				{
					rd[edge.a]=(rd[edge.b]+edge.cost);
					rd[edge.b]=-1e15;
					rd[edge.a]=-1e15;
					ans[edge.b]=-1e15;
					ans[edge.a]=-1e15;
					// cout<<edge.a<<" "<<edge.b<<endl;
				}	
			}
		}
		for(int i=1;i<=n;i++)
		{
			if(ans[i]<=(ll)-1e15) continue;
			ans[i]=d[i]+rd[i];
		}
		for(int i=1;i<=n;i++)
		{
			if(ans[i]<=(ll)-1e15) 
			{
				cout<<"INF\n";
			}
			else
			{
				cout<<ans[i]<<endl;
			}
		}
	}
	return 0;
}