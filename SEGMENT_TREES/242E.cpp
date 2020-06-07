
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

class SegmentTrees
{
	lvi st,lazy,children;
	ll n;
public:
	SegmentTrees(ll N)
	{
		n=N;
		st.resize(4*n);
		lazy.resize(4*n);
		children.resize(4*n);
	}
	ll lfc(ll x){ return (x<<1LL);}
	ll rgc(ll x){ return (x<<1LL)+1;}
	void build(lvi &arr,ll left,ll right,ll pos=1)
	{
		if(left==right)
		{
			children[pos]=1;
			st[pos]=arr[left];
		}
		else
		{
			ll mid=(left+right)/2;
			build(arr,left,mid,lfc(pos));
			build(arr,mid+1,right,rgc(pos));
			children[pos]=right-left+1;
			st[pos]=st[lfc(pos)]+st[rgc(pos)];
		}
	}
	void push(ll x)
	{
		if(lazy[x])
		{
			lazy[lfc(x)]^=1;
			lazy[rgc(x)]^=1;
			st[lfc(x)]=children[lfc(x)]-st[lfc(x)];
			st[rgc(x)]=children[rgc(x)]-st[rgc(x)];
			lazy[x]=0;
		}
	}
	void flip(ll l,ll r,ll left,ll right,ll pos=1)
	{
		if(l>r) return ;
		if(l==left && r==right)
		{
			lazy[pos]^=1;
			st[pos]=children[pos]-st[pos];
		}
		else
		{
			push(pos);
			ll mid=(left+right)/2;
			flip(l,min(r,mid),left,mid,lfc(pos));
			flip(max(mid+1,l),r,mid+1,right,rgc(pos));
			st[pos]=st[lfc(pos)]+st[rgc(pos)];
		}
	}
	ll getsum(ll l,ll r,ll left,ll right,ll pos=1)
	{
		if(l>r) return 0;
		if(l==left && r==right) return st[pos];
		else
		{
			push(pos);
			ll mid=(left+right)/2;
			return getsum(l,min(r,mid),left,mid,lfc(pos))+getsum(max(l,mid+1),r,mid+1,right,rgc(pos));
		}
	}
};

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
    ll n;
    cin>>n;
	lvvi bits(22,lvi(n,0));
	for (int i = 0; i < n; ++i)
	{
		ll x;
		cin>>x;
		// cout<<bitset<6>(x)<<endl;
		for(int j=0;j<=21;j++)
		{
			if((x&(1<<j))) bits[j][i]=1;
		}
	}
	vector<SegmentTrees> sgt(22,n);
	for (int i = 0; i < 22; ++i)
	{
		sgt[i].build(bits[i],0,n-1);
	}
	tc(T)
	{
		ll ch;
		cin>>ch;
		ll x,y;
		if(ch==1)
		{
			cin>>x>>y;
			x--;y--;
			ll ans=0;
			for(int i=0;i<=21;i++)
			{
				ans+=((1<<i)*sgt[i].getsum(x,y,0,n-1));
				// error(i);
				// sgt[i].getsum(x,y,0,n-1);
			}
			cout<<ans<<endl;
		}
		else
		{
			ll val;
			cin>>x>>y>>val;
			x--;y--;
			for (int i = 0; i < 22; ++i)
			{
				if((val&(1<<i)))
				{
					sgt[i].flip(x,y,0,n-1);
				}
			}
		}
	}
	return 0;
}