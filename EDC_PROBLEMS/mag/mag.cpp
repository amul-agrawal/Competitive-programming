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
ll mark[200000];
vector<lii> d;
ll n,m,k;
vector<vector<lii>> adj;
void dks()
{
	priority_queue<lii,vector<lii>,greater<lii>> pq;//priority queue is for vertex that can be reached..
	for (int i = 0; i < n; ++i) 
	{
		if(mark[i]==1)
		{
			pq.push({0,i}); //pushing gf vertex in pq as they can be reached...distance = 0
			d[i].ff=0; 
		}
	}
	while(!pq.empty())
	{
		ll cur=pq.top().ss;
		ll dis=pq.top().ff;
		mark[cur]=1; //marking those which have already been visited and have got there answer fixed.
		pq.pop();
		if(dis!=d[cur].ff) continue;
		for(auto next:adj[cur])
		{
			if(mark[next.ff]) continue;
			if(d[next.ff].ss==(ll)1e15)
			{
				d[next.ff].ss=dis+next.ss;
				continue;
			}
			if(d[next.ff].ss!=(ll)1e15)
			{
				lvi v2;
				ll tmp=d[next.ff].ff;
				v2.pb(d[next.ff].ss);
				v2.pb(d[next.ff].ff);
				v2.pb(dis+next.ss);
				sort(all(v2));
				d[next.ff].ss=v2[0];
				d[next.ff].ff=v2[1];
				if(tmp>v2[1])
				pq.push({v2[1],next.ff});
				continue;
			}
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	cin>>n>>m>>k;
	d.assign(n+2,{1e15,1e15});//ff=second smallest distance, ss=smallest distance
	adj.resize(n+2);
	for (int i = 0; i < m; ++i)
	{
		ll x,y,z;
		cin>>x>>y>>z;
		adj[x].pb({y,z});
		adj[y].pb({x,z});
	}
	for (int i = 0; i < k; ++i)
	{
		ll x;
		cin>>x;
		mark[x]=1; //marking those vertex that can be reached...
	}
	dks();
	if(mark[0]==0)
	{
		cout<<"-1\n";
	}
	else
	{
		cout<<d[0].ff<<endl;
	}
	return 0;
}