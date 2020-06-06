
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


const ll N= 1e5 + 13, logN= 21;
lvvi adj(N),h(N),par(N,lvi(logN+1,0));

lvi time_in(N),time_out(N),dp(N);
ll ct=0;

void dfs(ll x,ll pr=0,ll depth=0)
{
	dp[x]=depth;
	h[depth].pb(ct);
	time_in[x]=ct++;
	par[x][0]=pr;
	for(int i=1;i<=logN;i++)
	{
		par[x][i]=par[par[x][i-1]][i-1];
	}
	for(auto next:adj[x])
	{
		dfs(next,x,depth+1);
	}
	time_out[x]=ct++;
}

ll kthpar(ll x,ll k)
{
	ll ret=x;
	for(int i=0;i<=logN;i++)
	{
		if(k&(1<<i))
		{
			ret=par[ret][i];
		}
	}
	return ret;
}

ll kthchildren(ll x,ll k)
{
	if(x==0) return 0;
	ll in=time_in[x],out=time_out[x];
	ll ht=k+dp[x];
	//count number of values in (in,out);
	ll up=upper_bound(all(h[ht]),out)-h[ht].begin();
	ll low=lower_bound(all(h[ht]),in) - h[ht].begin();
	ll res=up-low;
	return res-1;
}

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	ll n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		ll x;
		cin>>x;
		adj[x].pb(i);
	}
	dfs(0);
	tc(T)
	{
		ll v,k;
		cin>>v>>k;
		v=kthpar(v,k);
		cout<<kthchildren(v,k)<<endl;
	}
	return 0;
}	


// approach:
// basically you have been given v and k ... 
// which means our basic job is to find the kth parent of v
// let kth parent of v be p
// now we need to count its descendents at a depth of (depht[p]+k)....let D = (depth[p]+k)
// now its easy to store the number of vertices at depth of h1 from a fixed root
// but in this problem there is one issue..the issue is that we don't want all veritces at depth
// of D. we only need those which are descendents of p;
// now how to solve this issue?
// Now one question how do you check that a vertex is a descendent of other vertex ? answer--> using time in and time out.... right?
// a is a descendent of b if time_in[b]<time_in[a] and time_out[b]>time_out[a].
// so how does this help to solve our problem?
// so uptill now everything was trivial ..now comes the slightly non trivial part..
// what we can do is make a array for every depth of the tree(arr[depth][time_ins])...what is this array will store?
// this array will store the time_ins for every index at their depth...
// i.e. suppose we reach a vertex v..so what we will do is arr[depth[v]].pb(time_in[v]).. basically this array stores the time_ins of all the vertices at required depth.
// now using this array and ancestor-descendent relation we can look for answer.
// now we can use this array and apply binary search to look for answer...
