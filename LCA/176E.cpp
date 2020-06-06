
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
vector<vector<lii>> adj(N);
lvvi par(N,lvi(logN,0)),path(N,lvi(logN,0));
lvi time_in(N),depth(N);
ll n,ct=0;

void dfs(ll x,ll pr=0,ll d=0,ll wt=0)
{
	depth[x]=d;
	time_in[x]=ct++;
	par[x][0]=pr;
	path[x][0]=wt;
	for(int i=1;i<logN;i++)
	{
		path[x][i]=path[x][i-1]+path[par[x][i-1]][i-1];
		par[x][i]=par[par[x][i-1]][i-1];
	}
	for(auto next:adj[x])
	{
		if(next.ff!=pr)
		{
			dfs(next.ff,x,d+1,next.ss);
		}
	}
}

ll getpathlength(ll x,ll y)
{
	if(x==y) return 0;
	if(depth[x]>depth[y]) swap(x,y);
	ll diff=depth[y]-depth[x];
	ll ret=0;
	for(int i=0;i<logN;i++)
	{
		if((1<<i)&diff)
		{
			ret+=path[y][i];
			y=par[y][i];
		}
	}	
	if(x==y) return ret;
	for(int i=logN-1;i>=0;i--)
	{
		if(par[y][i]!=par[x][i])
		{
			ret+=path[y][i];
			ret+=path[x][i];
			y=par[y][i];
			x=par[x][i];
		}
	}
	ret+=path[x][0];
	ret+=path[y][0];
	return ret;
}

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	cin>>n;
	for (int i = 0; i < n-1; ++i)
	{
		ll x,y,w;
		cin>>x>>y>>w;
		adj[x].pb({y,w});
		adj[y].pb({x,w});
	}
	dfs(1);
	ll sum1=0;
	set<lii> st;
	tc(T)
	{
		char ch;
		cin>>ch;
		if(ch=='?') cout<<sum1/2<<endl;
		else if(ch=='+')
		{
			ll x;
			cin>>x;
			ll prev=-1,next=-1;
			lii curr={time_in[x],x};
			st.insert(curr);
			if(st.size()==1) continue;
			lii f=*st.begin(),e=*st.rbegin();
			auto it = st.find(curr);
			if(f!=curr)
			{
				it--;
				prev=it->ss;
				it++;
			} 
			else prev=e.ss;
			if(e!=curr)
			{
				it++;
				next=it->ss;
				it--;
			}
			else next=f.ss;
			sum1+=getpathlength(prev,x);
			sum1+=getpathlength(x,next);
			sum1-=getpathlength(prev,next);
		}
		else
		{
			ll x;
			cin>>x;
			ll prev=-1,next=-1;
			lii f=*st.begin(),e=*st.rbegin(),curr={time_in[x],x};
			auto it = st.find(curr);
			if(st.size()==1) 
			{
				st.erase(curr);
				continue;
			}
			if(f!=curr)
			{
				it--;
				prev=it->ss;
				it++;
			} 
			else prev=e.ss;
			if(e!=curr)
			{
				it++;
				next=it->ss;
				it--;
			}
			else next=f.ss;
			sum1-=getpathlength(prev,x);
			sum1-=getpathlength(x,next);
			sum1+=getpathlength(prev,next);
			st.erase(curr);
		}
	}
	return 0;
}	