
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
#define x first
#define h second
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

class SegmentTrees
{
	lvi st;
	lvi lazy;
	ll n;
public:
	SegmentTrees(ll N)
	{
		n=N;
		st.resize(4*n);
		lazy.resize(4*n);
	}
	ll lfc(ll x){ return (x<<1LL);}
	ll rgc(ll x){ return (x<<1LL)+1;}
	void push(ll x)
	{
		if(lazy[x])
		{
			lazy[lfc(x)]+=lazy[x];
			lazy[rgc(x)]+=lazy[x];
			st[lfc(x)]+=lazy[x];
			st[rgc(x)]+=lazy[x];
			lazy[x]=0;
		}
	}
	void update(ll l,ll r,ll val,ll left,ll right,ll pos=1)
	{
		if(l>r) return ;
		if(l==left && r==right) 
		{
			lazy[pos]+=val;
			st[pos]+=val;
		}
		else
		{
			push(pos);
			ll mid=(left+right)/2;
			update(l,min(r,mid),val,left,mid,lfc(pos));
			update(max(l,mid+1),r,val,mid+1,right,rgc(pos));
			st[pos]=max(st[lfc(pos)],st[rgc(pos)]);
		}
	}
	ll get_max(ll l,ll r,ll left,ll right,ll pos=1)
	{
		if(l>r) return 0;
		if(l==left && r==right) return st[pos];
		else 
		{
			push(pos);
			ll mid=(left+right)/2;
			return max(get_max(l,min(r,mid),left,mid,lfc(pos)),
			get_max(max(l,mid+1),r,mid+1,right,rgc(pos)));
		}
	}
};

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	ll n;
	cin>>n;
	vector<lii> qry(n);
	vector<lii> copy_qry(n);
	lvi xis;
	for (int i = 0; i < n; ++i)
	{
		cin>>qry[i].x>>qry[i].h;
		copy_qry[i]=qry[i];
		xis.pb(qry[i].x);
		xis.pb(qry[i].x+qry[i].h-1);
	}
	sort(all(xis));
	ll curr=0;
	map<ll,ll> mp;
	mp[xis[0]]=curr++;
	for (int i = 1; i < xis.size(); ++i)
	{
		if(xis[i]!=xis[i-1])
		{
			mp[xis[i]]=curr++;
		}
	}
	sort(all(copy_qry));
	// error(curr);
	lvi dp(curr+2);
	SegmentTrees sgt(curr);
	for(int i=n-1;i>=0;i--)
	{
		ll x1=mp[copy_qry[i].x],x2=mp[copy_qry[i].x+copy_qry[i].h-1];
		dp[x1]=1+sgt.get_max(x1+1,x2,0,curr);
		// error(x1,x2,dp[x1]);
		sgt.update(x1+1,curr,1,0,curr);
		sgt.update(x1,x1,dp[x1],0,curr);
	}
	for (int i = 0; i < n; ++i)
	{
		ll x=mp[qry[i].x];
		cout<<dp[x]<<" ";
	}
	cout<<endl;
	return 0;
}
